// Sumitram Kumar
// 201951156 / CSE

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Rijndael's S-Box source: https://cryptography.fandom.com/wiki/Rijndael_S-box
unsigned char Sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };

// Rijndael's Inverse S-Box source: https://cryptography.fandom.com/wiki/Rijndael_S-box
unsigned char Inverse_Sbox[256] = {
  0X52, 0X09, 0X6A, 0XD5, 0X30, 0X36, 0XA5, 0X38, 0XBF, 0X40, 0XA3, 0X9E, 0X81, 0XF3, 0XD7, 0XFB,
  0X7C, 0XE3, 0X39, 0X82, 0X9B, 0X2F, 0XFF, 0X87, 0X34, 0X8E, 0X43, 0X44, 0XC4, 0XDE, 0XE9, 0XCB,
  0X54, 0X7B, 0X94, 0X32, 0XA6, 0XC2, 0X23, 0X3D, 0XEE, 0X4C, 0X95, 0X0B, 0X42, 0XFA, 0XC3, 0X4E,
  0X08, 0X2E, 0XA1, 0X66, 0X28, 0XD9, 0X24, 0XB2, 0X76, 0X5B, 0XA2, 0X49, 0X6D, 0X8B, 0XD1, 0X25,
  0X72, 0XF8, 0XF6, 0X64, 0X86, 0X68, 0X98, 0X16, 0XD4, 0XA4, 0X5C, 0XCC, 0X5D, 0X65, 0XB6, 0X92,
  0X6C, 0X70, 0X48, 0X50, 0XFD, 0XED, 0XB9, 0XDA, 0X5E, 0X15, 0X46, 0X57, 0XA7, 0X8D, 0X9D, 0X84,
  0X90, 0XD8, 0XAB, 0X00, 0X8C, 0XBC, 0XD3, 0X0A, 0XF7, 0XE4, 0X58, 0X05, 0XB8, 0XB3, 0X45, 0X06,
  0XD0, 0X2C, 0X1E, 0X8F, 0XCA, 0X3F, 0X0F, 0X02, 0XC1, 0XAF, 0XBD, 0X03, 0X01, 0X13, 0X8A, 0X6B,
  0X3A, 0X91, 0X11, 0X41, 0X4F, 0X67, 0XDC, 0XEA, 0X97, 0XF2, 0XCF, 0XCE, 0XF0, 0XB4, 0XE6, 0X73,
  0X96, 0XAC, 0X74, 0X22, 0XE7, 0XAD, 0X35, 0X85, 0XE2, 0XF9, 0X37, 0XE8, 0X1C, 0X75, 0XDF, 0X6E,
  0X47, 0XF1, 0X1A, 0X71, 0X1D, 0X29, 0XC5, 0X89, 0X6F, 0XB7, 0X62, 0X0E, 0XAA, 0X18, 0XBE, 0X1B,
  0XFC, 0X56, 0X3E, 0X4B, 0XC6, 0XD2, 0X79, 0X20, 0X9A, 0XDB, 0XC0, 0XFE, 0X78, 0XCD, 0X5A, 0XF4,
  0X1F, 0XDD, 0XA8, 0X33, 0X88, 0X07, 0XC7, 0X31, 0XB1, 0X12, 0X10, 0X59, 0X27, 0X80, 0XEC, 0X5F,
  0X60, 0X51, 0X7F, 0XA9, 0X19, 0XB5, 0X4A, 0X0D, 0X2D, 0XE5, 0X7A, 0X9F, 0X93, 0XC9, 0X9C, 0XEF,
  0XA0, 0XE0, 0X3B, 0X4D, 0XAE, 0X2A, 0XF5, 0XB0, 0XC8, 0XEB, 0XBB, 0X3C, 0X83, 0X53, 0X99, 0X61,
  0X17, 0X2B, 0X04, 0X7E, 0XBA, 0X77, 0XD6, 0X26, 0XE1, 0X69, 0X14, 0X63, 0X55, 0X21, 0X0C, 0X7D
};

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy2[] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
    0x20, 0x22, 0x24, 0x26, 0x28 ,0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e,
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
    0x80, 0x82, 0x84, 0x86, 0x88 ,0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e,
    0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe,
    0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde,
    0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe,
    0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11, 0x17, 0x15, 0x0b, 0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05,
    0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31, 0x37, 0x35, 0x2b, 0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25,
    0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51, 0x57, 0x55, 0x4b, 0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45,
    0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71, 0x77, 0x75, 0x6b, 0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65,
    0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91, 0x97, 0x95, 0x8b, 0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85,
    0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1, 0xb7, 0xb5, 0xab, 0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5,
    0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1, 0xd7, 0xd5, 0xcb, 0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5,
    0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1, 0xf7, 0xf5, 0xeb, 0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5
};

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy3[] = { 
    0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11,
    0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21,
    0x60, 0x63, 0x66, 0x65, 0x6c, 0x6f, 0x6a, 0x69, 0x78, 0x7b, 0x7e, 0x7d, 0x74, 0x77, 0x72, 0x71,
    0x50, 0x53, 0x56, 0x55, 0x5c, 0x5f, 0x5a, 0x59, 0x48, 0x4b, 0x4e, 0x4d, 0x44, 0x47, 0x42, 0x41,
    0xc0, 0xc3, 0xc6, 0xc5, 0xcc, 0xcf, 0xca, 0xc9, 0xd8, 0xdb, 0xde, 0xdd, 0xd4, 0xd7, 0xd2, 0xd1,
    0xf0, 0xf3, 0xf6, 0xf5, 0xfc, 0xff, 0xfa, 0xf9, 0xe8, 0xeb, 0xee, 0xed, 0xe4, 0xe7, 0xe2, 0xe1,
    0xa0, 0xa3, 0xa6, 0xa5, 0xac, 0xaf, 0xaa, 0xa9, 0xb8, 0xbb, 0xbe, 0xbd, 0xb4, 0xb7, 0xb2, 0xb1,
    0x90, 0x93, 0x96, 0x95, 0x9c, 0x9f, 0x9a, 0x99, 0x88, 0x8b, 0x8e, 0x8d, 0x84, 0x87, 0x82, 0x81,
    0x9b, 0x98, 0x9d, 0x9e, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8f, 0x8c, 0x89, 0x8a,
    0xab, 0xa8, 0xad, 0xae, 0xa7, 0xa4, 0xa1, 0xa2, 0xb3, 0xb0, 0xb5, 0xb6, 0xbf, 0xbc, 0xb9, 0xba,
    0xfb, 0xf8, 0xfd, 0xfe, 0xf7, 0xf4, 0xf1, 0xf2, 0xe3, 0xe0, 0xe5, 0xe6, 0xef, 0xec, 0xe9, 0xea,
    0xcb, 0xc8, 0xcd, 0xce, 0xc7, 0xc4, 0xc1, 0xc2, 0xd3, 0xd0, 0xd5, 0xd6, 0xdf, 0xdc, 0xd9, 0xda,
    0x5b, 0x58, 0x5d, 0x5e, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4f, 0x4c, 0x49, 0x4a,
    0x6b, 0x68, 0x6d, 0x6e, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7f, 0x7c, 0x79, 0x7a,
    0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a,
    0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a
};

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy9[256] = {
    0X00, 0X09, 0X12, 0X1B, 0X24, 0X2D, 0X36, 0X3F, 0X48, 0X41, 0X5A, 0X53, 0X6C, 0X65, 0X7E, 0X77,
    0X90, 0X99, 0X82, 0X8B, 0XB4, 0XBD, 0XA6, 0XAF, 0XD8, 0XD1, 0XCA, 0XC3, 0XFC, 0XF5, 0XEE, 0XE7,
    0X3B, 0X32, 0X29, 0X20, 0X1F, 0X16, 0X0D, 0X04, 0X73, 0X7A, 0X61, 0X68, 0X57, 0X5E, 0X45, 0X4C,
    0XAB, 0XA2, 0XB9, 0XB0, 0X8F, 0X86, 0X9D, 0X94, 0XE3, 0XEA, 0XF1, 0XF8, 0XC7, 0XCE, 0XD5, 0XDC,
    0X76, 0X7F, 0X64, 0X6D, 0X52, 0X5B, 0X40, 0X49, 0X3E, 0X37, 0X2C, 0X25, 0X1A, 0X13, 0X08, 0X01,
    0XE6, 0XEF, 0XF4, 0XFD, 0XC2, 0XCB, 0XD0, 0XD9, 0XAE, 0XA7, 0XBC, 0XB5, 0X8A, 0X83, 0X98, 0X91,
    0X4D, 0X44, 0X5F, 0X56, 0X69, 0X60, 0X7B, 0X72, 0X05, 0X0C, 0X17, 0X1E, 0X21, 0X28, 0X33, 0X3A,
    0XDD, 0XD4, 0XCF, 0XC6, 0XF9, 0XF0, 0XEB, 0XE2, 0X95, 0X9C, 0X87, 0X8E, 0XB1, 0XB8, 0XA3, 0XAA,
    0XEC, 0XE5, 0XFE, 0XF7, 0XC8, 0XC1, 0XDA, 0XD3, 0XA4, 0XAD, 0XB6, 0XBF, 0X80, 0X89, 0X92, 0X9B,
    0X7C, 0X75, 0X6E, 0X67, 0X58, 0X51, 0X4A, 0X43, 0X34, 0X3D, 0X26, 0X2F, 0X10, 0X19, 0X02, 0X0B,
    0XD7, 0XDE, 0XC5, 0XCC, 0XF3, 0XFA, 0XE1, 0XE8, 0X9F, 0X96, 0X8D, 0X84, 0XBB, 0XB2, 0XA9, 0XA0,
    0X47, 0X4E, 0X55, 0X5C, 0X63, 0X6A, 0X71, 0X78, 0X0F, 0X06, 0X1D, 0X14, 0X2B, 0X22, 0X39, 0X30,
    0X9A, 0X93, 0X88, 0X81, 0XBE, 0XB7, 0XAC, 0XA5, 0XD2, 0XDB, 0XC0, 0XC9, 0XF6, 0XFF, 0XE4, 0XED,
    0X0A, 0X03, 0X18, 0X11, 0X2E, 0X27, 0X3C, 0X35, 0X42, 0X4B, 0X50, 0X59, 0X66, 0X6F, 0X74, 0X7D,
    0XA1, 0XA8, 0XB3, 0XBA, 0X85, 0X8C, 0X97, 0X9E, 0XE9, 0XE0, 0XFB, 0XF2, 0XCD, 0XC4, 0XDF, 0XD6,
    0X31, 0X38, 0X23, 0X2A, 0X15, 0X1C, 0X07, 0X0E, 0X79, 0X70, 0X6B, 0X62, 0X5D, 0X54, 0X4F, 0X46
};

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy11[256] = {
    0X00, 0X0B, 0X16, 0X1D, 0X2C, 0X27, 0X3A, 0X31, 0X58, 0X53, 0X4E, 0X45, 0X74, 0X7F, 0X62, 0X69,
    0XB0, 0XBB, 0XA6, 0XAD, 0X9C, 0X97, 0X8A, 0X81, 0XE8, 0XE3, 0XFE, 0XF5, 0XC4, 0XCF, 0XD2, 0XD9,
    0X7B, 0X70, 0X6D, 0X66, 0X57, 0X5C, 0X41, 0X4A, 0X23, 0X28, 0X35, 0X3E, 0X0F, 0X04, 0X19, 0X12,
    0XCB, 0XC0, 0XDD, 0XD6, 0XE7, 0XEC, 0XF1, 0XFA, 0X93, 0X98, 0X85, 0X8E, 0XBF, 0XB4, 0XA9, 0XA2,
    0XF6, 0XFD, 0XE0, 0XEB, 0XDA, 0XD1, 0XCC, 0XC7, 0XAE, 0XA5, 0XB8, 0XB3, 0X82, 0X89, 0X94, 0X9F,
    0X46, 0X4D, 0X50, 0X5B, 0X6A, 0X61, 0X7C, 0X77, 0X1E, 0X15, 0X08, 0X03, 0X32, 0X39, 0X24, 0X2F,
    0X8D, 0X86, 0X9B, 0X90, 0XA1, 0XAA, 0XB7, 0XBC, 0XD5, 0XDE, 0XC3, 0XC8, 0XF9, 0XF2, 0XEF, 0XE4,
    0X3D, 0X36, 0X2B, 0X20, 0X11, 0X1A, 0X07, 0X0C, 0X65, 0X6E, 0X73, 0X78, 0X49, 0X42, 0X5F, 0X54,
    0XF7, 0XFC, 0XE1, 0XEA, 0XDB, 0XD0, 0XCD, 0XC6, 0XAF, 0XA4, 0XB9, 0XB2, 0X83, 0X88, 0X95, 0X9E,
    0X47, 0X4C, 0X51, 0X5A, 0X6B, 0X60, 0X7D, 0X76, 0X1F, 0X14, 0X09, 0X02, 0X33, 0X38, 0X25, 0X2E,
    0X8C, 0X87, 0X9A, 0X91, 0XA0, 0XAB, 0XB6, 0XBD, 0XD4, 0XDF, 0XC2, 0XC9, 0XF8, 0XF3, 0XEE, 0XE5,
    0X3C, 0X37, 0X2A, 0X21, 0X10, 0X1B, 0X06, 0X0D, 0X64, 0X6F, 0X72, 0X79, 0X48, 0X43, 0X5E, 0X55,
    0X01, 0X0A, 0X17, 0X1C, 0X2D, 0X26, 0X3B, 0X30, 0X59, 0X52, 0X4F, 0X44, 0X75, 0X7E, 0X63, 0X68,
    0XB1, 0XBA, 0XA7, 0XAC, 0X9D, 0X96, 0X8B, 0X80, 0XE9, 0XE2, 0XFF, 0XF4, 0XC5, 0XCE, 0XD3, 0XD8,
    0X7A, 0X71, 0X6C, 0X67, 0X56, 0X5D, 0X40, 0X4B, 0X22, 0X29, 0X34, 0X3F, 0X0E, 0X05, 0X18, 0X13,
    0XCA, 0XC1, 0XDC, 0XD7, 0XE6, 0XED, 0XF0, 0XFB, 0X92, 0X99, 0X84, 0X8F, 0XBE, 0XB5, 0XA8, 0XA3
    };

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy13[256] = {
    0X00, 0X0D, 0X1A, 0X17, 0X34, 0X39, 0X2E, 0X23, 0X68, 0X65, 0X72, 0X7F, 0X5C, 0X51, 0X46, 0X4B,
    0XD0, 0XDD, 0XCA, 0XC7, 0XE4, 0XE9, 0XFE, 0XF3, 0XB8, 0XB5, 0XA2, 0XAF, 0X8C, 0X81, 0X96, 0X9B,
    0XBB, 0XB6, 0XA1, 0XAC, 0X8F, 0X82, 0X95, 0X98, 0XD3, 0XDE, 0XC9, 0XC4, 0XE7, 0XEA, 0XFD, 0XF0,
    0X6B, 0X66, 0X71, 0X7C, 0X5F, 0X52, 0X45, 0X48, 0X03, 0X0E, 0X19, 0X14, 0X37, 0X3A, 0X2D, 0X20,
    0X6D, 0X60, 0X77, 0X7A, 0X59, 0X54, 0X43, 0X4E, 0X05, 0X08, 0X1F, 0X12, 0X31, 0X3C, 0X2B, 0X26,
    0XBD, 0XB0, 0XA7, 0XAA, 0X89, 0X84, 0X93, 0X9E, 0XD5, 0XD8, 0XCF, 0XC2, 0XE1, 0XEC, 0XFB, 0XF6,
    0XD6, 0XDB, 0XCC, 0XC1, 0XE2, 0XEF, 0XF8, 0XF5, 0XBE, 0XB3, 0XA4, 0XA9, 0X8A, 0X87, 0X90, 0X9D,
    0X06, 0X0B, 0X1C, 0X11, 0X32, 0X3F, 0X28, 0X25, 0X6E, 0X63, 0X74, 0X79, 0X5A, 0X57, 0X40, 0X4D,
    0XDA, 0XD7, 0XC0, 0XCD, 0XEE, 0XE3, 0XF4, 0XF9, 0XB2, 0XBF, 0XA8, 0XA5, 0X86, 0X8B, 0X9C, 0X91,
    0X0A, 0X07, 0X10, 0X1D, 0X3E, 0X33, 0X24, 0X29, 0X62, 0X6F, 0X78, 0X75, 0X56, 0X5B, 0X4C, 0X41,
    0X61, 0X6C, 0X7B, 0X76, 0X55, 0X58, 0X4F, 0X42, 0X09, 0X04, 0X13, 0X1E, 0X3D, 0X30, 0X27, 0X2A,
    0XB1, 0XBC, 0XAB, 0XA6, 0X85, 0X88, 0X9F, 0X92, 0XD9, 0XD4, 0XC3, 0XCE, 0XED, 0XE0, 0XF7, 0XFA,
    0XB7, 0XBA, 0XAD, 0XA0, 0X83, 0X8E, 0X99, 0X94, 0XDF, 0XD2, 0XC5, 0XC8, 0XEB, 0XE6, 0XF1, 0XFC,
    0X67, 0X6A, 0X7D, 0X70, 0X53, 0X5E, 0X49, 0X44, 0X0F, 0X02, 0X15, 0X18, 0X3B, 0X36, 0X21, 0X2C,
    0X0C, 0X01, 0X16, 0X1B, 0X38, 0X35, 0X22, 0X2F, 0X64, 0X69, 0X7E, 0X73, 0X50, 0X5D, 0X4A, 0X47,
    0XDC, 0XD1, 0XC6, 0XCB, 0XE8, 0XE5, 0XF2, 0XFF, 0XB4, 0XB9, 0XAE, 0XA3, 0X80, 0X8D, 0X9A, 0X97
};

// Rijndael's Mix Columns source: https://en.wikipedia.org/wiki/Rijndael_MixColumns
unsigned char MulBy14[256] = {
    0x00, 0x0e, 0x1c, 0x12, 0x38, 0x36, 0x24, 0x2a, 0x70, 0x7e, 0x6c, 0x62, 0x48, 0x46, 0x54, 0x5a,
    0xe0, 0xee, 0xfc, 0xf2, 0xd8, 0xd6, 0xc4, 0xca, 0x90, 0x9e, 0x8c, 0x82, 0xa8, 0xa6, 0xb4, 0xba,
    0xdb, 0xd5, 0xc7, 0xc9, 0xe3, 0xed, 0xff, 0xf1, 0xab, 0xa5, 0xb7, 0xb9, 0x93, 0x9d, 0x8f, 0x81,
    0x3b, 0x35, 0x27, 0x29, 0x03, 0x0d, 0x1f, 0x11, 0x4b, 0x45, 0x57, 0x59, 0x73, 0x7d, 0x6f, 0x61,
    0xad, 0xa3, 0xb1, 0xbf, 0x95, 0x9b, 0x89, 0x87, 0xdd, 0xd3, 0xc1, 0xcf, 0xe5, 0xeb, 0xf9, 0xf7,
    0x4d, 0x43, 0x51, 0x5f, 0x75, 0x7b, 0x69, 0x67, 0x3d, 0x33, 0x21, 0x2f, 0x05, 0x0b, 0x19, 0x17,
    0x76, 0x78, 0x6a, 0x64, 0x4e, 0x40, 0x52, 0x5c, 0x06, 0x08, 0x1a, 0x14, 0x3e, 0x30, 0x22, 0x2c,
    0x96, 0x98, 0x8a, 0x84, 0xae, 0xa0, 0xb2, 0xbc, 0xe6, 0xe8, 0xfa, 0xf4, 0xde, 0xd0, 0xc2, 0xcc,
    0x41, 0x4f, 0x5d, 0x53, 0x79, 0x77, 0x65, 0x6b, 0x31, 0x3f, 0x2d, 0x23, 0x09, 0x07, 0x15, 0x1b,
    0xa1, 0xaf, 0xbd, 0xb3, 0x99, 0x97, 0x85, 0x8b, 0xd1, 0xdf, 0xcd, 0xc3, 0xe9, 0xe7, 0xf5, 0xfb,
    0x9a, 0x94, 0x86, 0x88, 0xa2, 0xac, 0xbe, 0xb0, 0xea, 0xe4, 0xf6, 0xf8, 0xd2, 0xdc, 0xce, 0xc0,
    0x7a, 0x74, 0x66, 0x68, 0x42, 0x4c, 0x5e, 0x50, 0x0a, 0x04, 0x16, 0x18, 0x32, 0x3c, 0x2e, 0x20,
    0xec, 0xe2, 0xf0, 0xfe, 0xd4, 0xda, 0xc8, 0xc6, 0x9c, 0x92, 0x80, 0x8e, 0xa4, 0xaa, 0xb8, 0xb6,
    0x0c, 0x02, 0x10, 0x1e, 0x34, 0x3a, 0x28, 0x26, 0x7c, 0x72, 0x60, 0x6e, 0x44, 0x4a, 0x58, 0x56,
    0x37, 0x39, 0x2b, 0x25, 0x0f, 0x01, 0x13, 0x1d, 0x47, 0x49, 0x5b, 0x55, 0x7f, 0x71, 0x63, 0x6d,
    0xd7, 0xd9, 0xcb, 0xc5, 0xef, 0xe1, 0xf3, 0xfd, 0xa7, 0xa9, 0xbb, 0xb5, 0x9f, 0x91, 0x83, 0x8d
};

// RCon source: https://cryptography.fandom.com/wiki/Rijndael_key_schedule
unsigned char Rcon[256] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

void Key_Expansion(unsigned char key[16], unsigned char Expanded_Key[176]) {
    
    void Key_Expansion_Core(unsigned char* in, unsigned char i) {

        unsigned int * q = (unsigned int *) in;

        // bytes are rotated left
        *q = (*q >> 8 | ((*q & 0xff) << 24));

        in[0] = Sbox[in[0]]; 
        in[1] = Sbox[in[1]];
        in[2] = Sbox[in[2]]; 
        in[3] = Sbox[in[3]];

        // XOR with RCon
        in[0] ^= Rcon[i];
    }

    // Copying original key
    for (int i = 0; i < 16; ++i) {
        Expanded_Key[i] = key[i];
    }

    // Generation of 16 bytes
    int Bytes_Generated = 16;

    //RCon iteration begins from 1
    int RCon_Iteration = 1;

    // Temprory array to store keys for each step
    unsigned char temp[4];

    // We need 10 + 1 = 11 keys for every round, so, 11 x 4 = 44 bytes = 176 bits
    while (Bytes_Generated < 176) {
        
        // Creating 4 bytes for the round keys
        for (int i = 0; i < 4; ++i) {
            temp[i] = Expanded_Key[i + Bytes_Generated - 4];
        }

        if (Bytes_Generated % 16 == 0) {
            Key_Expansion_Core(temp, RCon_Iteration++);
        }

        // XOR temp with Bytes_Generated - 16, and store in Expanded_Key
        for (unsigned char k = 0; k < 4; ++k) {
            Expanded_Key[Bytes_Generated] = Expanded_Key[Bytes_Generated - 16] ^ temp[k];
            Bytes_Generated++;
        }
    }
}

void Sub_Bytes(unsigned char* state) {

    // Copying each state value with corresponding byte in the Rijndael S-Box
    for (int i = 0; i < 16; ++i) {
        state[i] = Sbox[state[i]];
    }
}

void Inverse_Sub_Bytes(unsigned char* state) {
  
  // Copying each state value with corresponding byte in the Rijndael S-Box
  for (int i = 0; i < 16; ++i)
    state[i] = Inverse_Sbox[state[i]];
}

void Shift_Rows(unsigned char* state) {

    unsigned char temp_state[16];

    //shifting 1 element, 2 elements, 3 elements from right to left of 1st column except first row respectively 
    temp_state[0] = state[0];
    temp_state[1] = state[5];
    temp_state[2] = state[10];
    temp_state[3] = state[15];

    //shifting 1 element, 2 elements, 3 elements from right to left of 2nd column except first row respectively 
    temp_state[4] = state[4];
    temp_state[5] = state[9];
    temp_state[6] = state[14];
    temp_state[7] = state[3];

    //shifting 1 element, 2 elements, 3 elements from right to left of 3rd column except first row respectively 
    temp_state[8] = state[8];
    temp_state[9] = state[13];
    temp_state[10] = state[2];
    temp_state[11] = state[7];

    //shifting 1 element, 2 elements, 3 elements from right to left of 4th column except first row respectively 
    temp_state[12] = state[12];
    temp_state[13] = state[1];
    temp_state[14] = state[6];
    temp_state[15] = state[11];

    for (int i = 0; i < 16; ++i) {
        state[i] = temp_state[i];
    }
}

void Inverse_Shift_Rows(unsigned char* state) {
    
    unsigned char temp_state[16];

    // shifting 1 element, 2 elements, 3 elements from left to right of 1st column except first row respectively 
    temp_state[0] = state[0];
    temp_state[1] = state[13];
    temp_state[2] = state[10];
    temp_state[3] = state[7];

    // shifting 1 element, 2 elements, 3 elements from left to right of 2nd column except first row respectively 
    temp_state[4] = state[4];
    temp_state[5] = state[1];
    temp_state[6] = state[14];
    temp_state[7] = state[11];

    // shifting 1 element, 2 elements, 3 elements from left to right of 3rd column except first row respectively 
    temp_state[8] = state[8]; 
    temp_state[9] = state[5];
    temp_state[10] = state[2];
    temp_state[11] = state[15];


    // shifting 1 element, 2 elements, 3 elements from left to right of 4th column except first row respectively 
    temp_state[12] = state[12];
    temp_state[13] = state[9];
    temp_state[14] = state[6];
    temp_state[15] = state[3];

    for (int i = 0; i < 16; ++i)
        state[i] = temp_state[i];
}

void Mix_Columns(unsigned char* state) {

    unsigned char temp_state[16];

    for (int i = 0; i < 4; ++i) {

        temp_state[(4 * i) + 0] = (unsigned char) (MulBy2[state[(4 * i) + 0]] ^ MulBy3[state[(4 * i) + 1]] ^ state[(4 * i) + 2] ^ state[(4 * i) + 3]);
        temp_state[(4 * i) + 1] = (unsigned char) (state[(4 * i) + 0] ^ MulBy2[state[(4 * i) + 1]] ^ MulBy3[state[(4 * i) + 2]] ^ state[(4 * i) + 3]);
        temp_state[(4 * i) + 2] = (unsigned char) (state[(4 * i) + 0] ^ state[(4 * i) + 1] ^ MulBy2[state[(4 * i) + 2]] ^ MulBy3[state[(4 * i) + 3]]);
        temp_state[(4 * i) + 3] = (unsigned char) (MulBy3[state[(4 * i) + 0]] ^ state[(4 * i) + 1] ^ state[(4 * i) + 2] ^ MulBy2[state[(4 * i) + 3]]);
    }
        
    for (int i = 0; i < 16; ++i) {
        state[i] = temp_state[i];
    }
}

void Inverse_Mix_Columns(unsigned char* state) {
  
    unsigned char temp_state[16];

    for (int i = 0; i < 4; ++i) {

        temp_state[(4 * i) + 0] = (unsigned char) (MulBy14[state[(4 * i) + 0]] ^ MulBy11[state[(4 * i) + 1]] ^ MulBy13[state[(4 * i) + 2]] ^ MulBy9[state[(4 * i) + 3]]);
        temp_state[(4 * i) + 1] = (unsigned char) (MulBy9[state[(4 * i) + 0]] ^ MulBy14[state[(4 * i) + 1]] ^ MulBy11[state[(4 * i) + 2]] ^ MulBy13[state[(4 * i) + 3]]);
        temp_state[(4 * i) + 2] = (unsigned char) (MulBy13[state[(4 * i) + 0]] ^ MulBy9[state[(4 * i) + 1]] ^ MulBy14[state[(4 * i) + 2]] ^ MulBy11[state[(4 * i) + 3]]);
        temp_state[(4 * i) + 3] = (unsigned char) (MulBy11[state[(4 * i) + 0]] ^ MulBy13[state[(4 * i) + 1]] ^ MulBy9[state[(4 * i) + 2]] ^ MulBy14[state[(4 * i) + 3]]);
    }

    for (int i = 0; i < 16; ++i) {
        state[i] = temp_state[i];
    }
}

void Add_Round_Keys(unsigned char* state, unsigned char* Round_Key) {

    // XOR operation of Plain text with Round key generated after key expansion algorithm
    for (int i = 0; i < 16; ++i) {
        state[i] ^= Round_Key[i];
    }
}

void AES_Encryption(unsigned char* Plain_Text, unsigned char* key) {

    unsigned char state[16];

    // Take only the first 16 characters of the Plain_Text
    for (int i = 0; i < 16; ++i) {

        state[i] = Plain_Text[i];
    }

    unsigned char Expanded_Keys[176];

    Key_Expansion(key, Expanded_Keys);

    // Add Round Key for very first initial step 
    Add_Round_Keys(state, Expanded_Keys);


    const int Number_of_Common_Rounds = 9;

    // Rounds to be executed
    for (int i = 0; i < Number_of_Common_Rounds; ++i) {

        Sub_Bytes(state);
        Shift_Rows(state);

        Mix_Columns(state);
        Add_Round_Keys(state, Expanded_Keys + (16 * (i + 1)));
    }

    // Final Round which does NOT involve Mix Colums step
    Sub_Bytes(state);
    Shift_Rows(state);
    Add_Round_Keys(state, Expanded_Keys + 160);

    // Copying encrypted state to the Plain text
    for (int i = 0; i < 16; ++i) {
        Plain_Text[i] = state[i];
    }
}

void AES_Decryption(unsigned char* Plain_Text, unsigned char* Expanded_Key) {
    
    unsigned char state[16];

    // Take only the first 16 characters of the Plain_Text
    for (int i = 0; i < 16; ++i) {
        
        state[i] = Plain_Text[i];
    }

    // Add Round Key for very first initial step 
    Add_Round_Keys(state, Expanded_Key + 160);

    const int Number_of_Common_Rounds = 9;

    // Rounds to be executed
    for (int i = Number_of_Common_Rounds; i > 0; --i) {
        
        Inverse_Shift_Rows(state);
        Inverse_Sub_Bytes(state);
        Add_Round_Keys(state, Expanded_Key + (16 * i));
        Inverse_Mix_Columns(state);
    }

    // Final Round which does NOT involve Mix Colums step
    Inverse_Shift_Rows(state);
    Inverse_Sub_Bytes(state);
    Add_Round_Keys(state, Expanded_Key);

    // Copying decrypted state to the Plain text
    for (int i = 0; i < 16; ++i) {
        Plain_Text[i] = state[i];
    }
}

int main () {

    srand(time(0));

    unsigned char temp;

    unsigned char Plain_Text[16];
    unsigned char Random_Key[16];

    // Substituting randomly generated value in Plain text
    for (int i = 0; i < 32; i++) {
        temp =  rand() % 256;
        if (i < 16) {
            Plain_Text[i] = temp;
        }

        else {
            Random_Key[i] = temp;
        }
    }

    // Printing Plain text, random keys, Encrypted text, decrypted text at every step for convinience & acccording to notations in given assignment
    for (int i = 0; i < 32; i++) {

        if (i == 0) {
            printf ("\n(m1 || m2) = (");
        }

        if (i < 16) {
            printf ("%x ", Plain_Text[i]);
        }

        else {
            printf (" %x", Plain_Text[i]);;
        }
    }
    printf (")\n\n");

// Question 1 // Using a random Plain text and random Key /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AES_Encryption (Plain_Text, Random_Key);
    printf ("h(m1 || m2) = C = ");

    for (int i = 0; i < 16; ++i) {
        printf (" %x ", Plain_Text[i]);;
    }
    printf ("\n\n");

    // Generating second random key
    for (int i = 0; i < 16; ++i) {
        temp =  rand() % 256;
        Random_Key[i] = temp;
    }

    unsigned char Expanded_Key[176];

    Key_Expansion (Random_Key, Expanded_Key);

    printf ("Random key: ");
    for (int i = 0; i < 16; ++i) {
        printf (" %x", Random_Key[i]);;
    }
    printf ("\n\n");

// Question 2 // Using Encypted Plain_Text (Cypher text) from question 1 here as text input and second random key as key /////////////////////////////////////////////////////////////
    AES_Decryption (Plain_Text, Expanded_Key);

    printf ("Decrypted text: ");

    for (int i = 0; i < 16; ++i) {
        printf (" %x ", Plain_Text[i]);;
    }

    printf ("\n\n(m1' || m2') = (");

    for (int i = 0; i < 16; ++i) {
        printf ("%x ", Plain_Text[i]);;
    }

    for (int i = 0; i < 16; ++i) {
        printf (" %x", Random_Key[i]);;
    }
    printf (")");
    printf ("\n\n");

// Question 3 // Using Decrypted Cypher Text from question 2 as text input here and the key is same as that of question 2. Encrypted text should be same as in queation 1 input //////
    AES_Encryption (Plain_Text, Expanded_Key);
    printf ("h(m1' || m2') = ");

    for (int i = 0; i < 16; ++i) {
        printf (" %x ", Plain_Text[i]);;
    }
    printf (" = C\n\n");
    printf ("\n");

    return 0;
}