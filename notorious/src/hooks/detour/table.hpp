/*
 * Hacker Disassembler Engine 32 C
 * Copyright (c) 2008-2009, Vyacheslav Patkov.
 * All rights reserved.
 *
 */

#define C_NONE    0x00
#define C_MODRM   0x01
#define C_IMM8    0x02
#define C_IMM16   0x04
#define C_IMM_P66 0x10
#define C_REL8    0x20
#define C_REL32   0x40
#define C_GROUP   0x80
#define C_ERROR   0xff

#define PRE_ANY  0x00
#define PRE_NONE 0x01
#define PRE_F2   0x02
#define PRE_F3   0x04
#define PRE_66   0x08
#define PRE_67   0x10
#define PRE_LOCK 0x20
#define PRE_SEG  0x40
#define PRE_ALL  0xff

#define DELTA_OPCODES      0x4a
#define DELTA_FPU_REG      0xf1
#define DELTA_FPU_MODRM    0xf8
#define DELTA_PREFIXES     0x130
#define DELTA_OP_LOCK_OK   0x1a1
#define DELTA_OP2_LOCK_OK  0x1b9
#define DELTA_OP_ONLY_MEM  0x1cb
#define DELTA_OP2_ONLY_MEM 0x1da

unsigned char hde32_table[] = {
  0xa3,0xa8,0xa3,0xa8,0xa3,0xa8,0xa3,0xa8,0xa3,0xa8,0xa3,0xa8,0xa3,0xa8,0xa3,
  0xa8,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xac,0xaa,0xb2,0xaa,0x9f,0x9f,
  0x9f,0x9f,0xb5,0xa3,0xa3,0xa4,0xaa,0xaa,0xba,0xaa,0x96,0xaa,0xa8,0xaa,0xc3,
  0xc3,0x96,0x96,0xb7,0xae,0xd6,0xbd,0xa3,0xc5,0xa3,0xa3,0x9f,0xc3,0x9c,0xaa,
  0xaa,0xac,0xaa,0xbf,0x03,0x7f,0x11,0x7f,0x01,0x7f,0x01,0x3f,0x01,0x01,0x90,
  0x82,0x7d,0x97,0x59,0x59,0x59,0x59,0x59,0x7f,0x59,0x59,0x60,0x7d,0x7f,0x7f,
  0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x9a,0x88,0x7d,
  0x59,0x50,0x50,0x50,0x50,0x59,0x59,0x59,0x59,0x61,0x94,0x61,0x9e,0x59,0x59,
  0x85,0x59,0x92,0xa3,0x60,0x60,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,0x59,
  0x59,0x59,0x9f,0x01,0x03,0x01,0x04,0x03,0xd5,0x03,0xcc,0x01,0xbc,0x03,0xf0,
  0x10,0x10,0x10,0x10,0x50,0x50,0x50,0x50,0x14,0x20,0x20,0x20,0x20,0x01,0x01,
  0x01,0x01,0xc4,0x02,0x10,0x00,0x00,0x00,0x00,0x01,0x01,0xc0,0xc2,0x10,0x11,
  0x02,0x03,0x11,0x03,0x03,0x04,0x00,0x00,0x14,0x00,0x02,0x00,0x00,0xc6,0xc8,
  0x02,0x02,0x02,0x02,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xca,
  0x01,0x01,0x01,0x00,0x06,0x00,0x04,0x00,0xc0,0xc2,0x01,0x01,0x03,0x01,0xff,
  0xff,0x01,0x00,0x03,0xc4,0xc4,0xc6,0x03,0x01,0x01,0x01,0xff,0x03,0x03,0x03,
  0xc8,0x40,0x00,0x0a,0x00,0x04,0x00,0x00,0x00,0x00,0x7f,0x00,0x33,0x01,0x00,
  0x00,0x00,0x00,0x00,0x00,0xff,0xbf,0xff,0xff,0x00,0x00,0x00,0x00,0x07,0x00,
  0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0xff,0xff,0x00,0x00,0x00,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x7f,0x00,0x00,0xff,0x4a,0x4a,0x4a,0x4a,0x4b,0x52,0x4a,0x4a,0x4a,0x4a,0x4f,
  0x4c,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x55,0x45,0x40,0x4a,0x4a,0x4a,
  0x45,0x59,0x4d,0x46,0x4a,0x5d,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,0x4a,
  0x4a,0x4a,0x4a,0x4a,0x4a,0x61,0x63,0x67,0x4e,0x4a,0x4a,0x6b,0x6d,0x4a,0x4a,
  0x45,0x6d,0x4a,0x4a,0x44,0x45,0x4a,0x4a,0x00,0x00,0x00,0x02,0x0d,0x06,0x06,
  0x06,0x06,0x0e,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x02,0x06,
  0x00,0x0a,0x0a,0x07,0x07,0x06,0x02,0x05,0x05,0x02,0x02,0x00,0x00,0x04,0x04,
  0x04,0x04,0x00,0x00,0x00,0x0e,0x05,0x06,0x06,0x06,0x01,0x06,0x00,0x00,0x08,
  0x00,0x10,0x00,0x18,0x00,0x20,0x00,0x28,0x00,0x30,0x00,0x80,0x01,0x82,0x01,
  0x86,0x00,0xf6,0xcf,0xfe,0x3f,0xab,0x00,0xb0,0x00,0xb1,0x00,0xb3,0x00,0xba,
  0xf8,0xbb,0x00,0xc0,0x00,0xc1,0x00,0xc7,0xbf,0x62,0xff,0x00,0x8d,0xff,0x00,
  0xc4,0xff,0x00,0xc5,0xff,0x00,0xff,0xff,0xeb,0x01,0xff,0x0e,0x12,0x08,0x00,
  0x13,0x09,0x00,0x16,0x08,0x00,0x17,0x09,0x00,0x2b,0x09,0x00,0xae,0xff,0x07,
  0xb2,0xff,0x00,0xb4,0xff,0x00,0xb5,0xff,0x00,0xc3,0x01,0x00,0xc7,0xff,0xbf,
  0xe7,0x08,0x00,0xf0,0x02,0x00
};