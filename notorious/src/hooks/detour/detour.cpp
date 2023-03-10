#include <Windows.h>
#include "detour.hpp"
#include "hde.hpp"

namespace util {

    constexpr uint8_t target_shellcode[] = {
        // 0x0F, 0x1F, 0x04, 0x94 // nop    DWORD PTR [esp+edx*4]
        0x90, 0x68, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3 // nop push imm32 ret
    };

    constexpr uint8_t tramp_shellcode[] = {
        0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 // push imm32 ret
    };

    bool Hook::enable(uintptr_t target, uintptr_t detour) {
        hde32s hde_state;

        while (_bytes < sizeof(target_shellcode)) {
            _bytes += hde32_disasm((const void*)(target + _bytes), &hde_state);

            if (hde_state.opcode == 0xC3) {
                _bytes = 0;
                return false;
            }
        }

        auto tramp = VirtualAlloc(nullptr, _bytes + sizeof(tramp_shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if (!tramp) {
            _bytes = 0;
            return false;
        }

        unsigned long old_prot;

        VirtualProtect((void*)target, _bytes, PAGE_EXECUTE_READWRITE, &old_prot);

        _target = target;
        _detour = detour;
        _tramp = (uintptr_t)tramp;

        memcpy((uint8_t*)_tramp, (const uint8_t*)_target, _bytes);
        memcpy((uint8_t*)_tramp + _bytes, tramp_shellcode, sizeof(tramp_shellcode));
        memcpy((uint8_t*)_target, target_shellcode, sizeof(target_shellcode));

        *(uintptr_t*)(_target + 2) = _detour;
        *(uintptr_t*)(_tramp + _bytes + 1) = _target + _bytes;

        VirtualProtect((void*)target, _bytes, old_prot, &old_prot);

        return true;
    }

    void Hook::disable() {
        if (!_bytes)
            return;

        unsigned long old_prot;

        VirtualProtect((void*)_target, _bytes, PAGE_EXECUTE_READWRITE, &old_prot);

        memcpy((uint8_t*)_target, (const uint8_t*)_tramp + _bytes, _bytes);

        VirtualFree((void*)_tramp, 0, MEM_RELEASE);
        VirtualProtect((void*)_target, _bytes, old_prot, &old_prot);

        _bytes = 0;
        _target = 0;
        _detour = 0;
        _tramp = 0;
    }

} // namespace util