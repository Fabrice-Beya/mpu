
/*****************************************************************************
* | File      	:   MPU6050.c
* | Author      :   Fabrice Beya
* | Function    :   Driver accelerometer
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-01
* | Info        :   
#
# Summary
******************************************************************************/

#include "mpu6050.h"

const unsigned char dmp_memory[MPU6050_DMP_CODE_SIZE] PROGMEM = {
/* bank # 0 */
0x00, 0xF8, 0xF6, 0x2A, 0x3F, 0x68, 0xF5, 0x7A, 0x00, 0x06, 0xFF, 0xFE, 0x00, 0x03, 0x00, 0x00,
0x00, 0x65, 0x00, 0x54, 0xFF, 0xEF, 0x00, 0x00, 0xFA, 0x80, 0x00, 0x0B, 0x12, 0x82, 0x00, 0x01,
0x03, 0x0C, 0x30, 0xC3, 0x0A, 0x74, 0x56, 0x2D, 0x0D, 0x62, 0xDB, 0xC7, 0x16, 0xF4, 0xBA, 0x02,
0x38, 0x83, 0xF8, 0x83, 0x30, 0x00, 0xF8, 0x83, 0x25, 0x8E, 0xF8, 0x83, 0x30, 0x00, 0xF8, 0x83,
0xFF, 0xFF, 0xFF, 0xFF, 0x0C, 0xBD, 0xD8, 0x11, 0x24, 0x00, 0x04, 0x00, 0x1A, 0x82, 0x79, 0xA1,
0x00, 0x36, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x83, 0x6F, 0xA2,
0x00, 0x3E, 0x03, 0x30, 0x40, 0x00, 0x00, 0x00, 0x02, 0xCA, 0xE3, 0x09, 0x3E, 0x80, 0x00, 0x00,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
0x1F, 0xA4, 0xE8, 0xE4, 0xFF, 0xF5, 0xDC, 0xB9, 0x00, 0x5B, 0x79, 0xCF, 0x1F, 0x3F, 0x78, 0x76,
0x00, 0x86, 0x7C, 0x5A, 0x00, 0x86, 0x23, 0x47, 0xFA, 0xB9, 0x86, 0x31, 0x00, 0x74, 0x87, 0x8A,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0xFF, 0xFF, 0xE9, 0xA8, 0x00, 0x00, 0x21, 0x82,
0xFA, 0xB8, 0x4D, 0x46, 0xFF, 0xFA, 0xDF, 0x3D, 0xFF, 0xFF, 0xB2, 0xB3, 0x00, 0x00, 0x00, 0x00,
0x3F, 0xFF, 0xBA, 0x98, 0x00, 0x5D, 0xAC, 0x08, 0x00, 0x0A, 0x63, 0x78, 0x00, 0x01, 0x46, 0x21,
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x42, 0xB5, 0x00, 0x06, 0x00, 0x64, 0x00, 0x64, 0x00, 0x06,
0x14, 0x06, 0x02, 0x9F, 0x0F, 0x47, 0x91, 0x32, 0xD9, 0x0E, 0x9F, 0xC9, 0x1D, 0xCF, 0x4C, 0x34,
0x3B, 0xB6, 0x7A, 0xE8, 0x00, 0x64, 0x00, 0x06, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE,
/* bank # 1 */
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0x00, 0x00, 0xFF, 0xF1, 0x00, 0x00, 0xFA, 0x46, 0x00, 0x00, 0xA2, 0xB8, 0x00, 0x00,
0x10, 0x00, 0x00, 0x00, 0x04, 0xD6, 0x00, 0x00, 0x04, 0xCC, 0x00, 0x00, 0x04, 0xCC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x06, 0x00, 0x02, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x05, 0x00, 0x64, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00,
0x00, 0x00, 0x00, 0x32, 0xF8, 0x98, 0x00, 0x00, 0xFF, 0x65, 0x00, 0x00, 0x83, 0x0F, 0x00, 0x00,
0x00, 0x06, 0x00, 0x00, 0xFF, 0xF1, 0x00, 0x00, 0xFA, 0x46, 0x00, 0x00, 0xA2, 0xB8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0xB2, 0x6A, 0x00, 0x02, 0x00, 0x00,
0x00, 0x01, 0xFB, 0x83, 0x00, 0x7C, 0x00, 0x00, 0xFB, 0x15, 0xFC, 0x00, 0x1F, 0xB4, 0xFF, 0x83,
0x00, 0x00, 0x00, 0x01, 0x00, 0x65, 0x00, 0x07, 0x00, 0x64, 0x03, 0xE8, 0x00, 0x64, 0x00, 0x28,
0x00, 0x00, 0xFF, 0xFD, 0x00, 0x00, 0x00, 0x00, 0x16, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF4, 0x00, 0x00, 0x10, 0x00,
/* bank # 2 */
0x00, 0x28, 0x00, 0x00, 0xFF, 0xFF, 0x45, 0x81, 0xFF, 0xFF, 0xFA, 0x72, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x01, 0x00, 0x05, 0xBA, 0xC6, 0x00, 0x47, 0x78, 0xA2,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x14,
0x00, 0x00, 0x23, 0xBB, 0x00, 0x2E, 0xA2, 0x5B, 0x00, 0x00, 0x05, 0x68, 0x00, 0x0B, 0xCF, 0x49,
0x00, 0x04, 0xFF, 0xFD, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x64, 0x00, 0x07, 0x00, 0x08, 0x00, 0x06, 0x00, 0x06, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x2E, 0xA2, 0x5B, 0x00, 0x00, 0x05, 0x68, 0x00, 0x0B, 0xCF, 0x49, 0x00, 0x00, 0x00, 0x00,
0x00, 0xF8, 0xF6, 0x2A, 0x3F, 0x68, 0xF5, 0x7A, 0x00, 0x04, 0xFF, 0xFD, 0x00, 0x02, 0x00, 0x00,
0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E,
0xFF, 0xFF, 0xFF, 0xCF, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0xFF, 0xFF, 0xFF, 0x9C,
0x00, 0x00, 0x43, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64,
0xFF, 0xE5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* bank # 3 */
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x24, 0x26, 0xD3,
0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x96, 0x00, 0x3C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x9E, 0x65, 0x5D,
0x0C, 0x0A, 0x4E, 0x68, 0xCD, 0xCF, 0x77, 0x09, 0x50, 0x16, 0x67, 0x59, 0xC6, 0x19, 0xCE, 0x82,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x71, 0x1C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xD7, 0x84, 0x00, 0x03, 0x00, 0x00, 0x00,
0x00, 0x11, 0xDC, 0x47, 0x03, 0x00, 0x00, 0x00, 0xC7, 0x93, 0x8F, 0x9D, 0x1E, 0x1B, 0x1C, 0x19,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0E, 0xDF, 0xA4, 0x38, 0x1F, 0x9E, 0x65, 0x5D,
0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x71, 0x1C, 0x02, 0x03, 0x18, 0x85, 0x00, 0x00, 0x40, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x3F, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xF4, 0xC9, 0xFF, 0xFF, 0xBC, 0xF0, 0x00, 0x01, 0x0C, 0x0F,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xF5, 0xB7, 0xBA, 0xB3, 0x67, 0x7D, 0xDF, 0x7E, 0x72, 0x90, 0x2E, 0x55, 0x4C, 0xF6, 0xE6, 0x88,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* bank # 4 */
0xD8, 0xDC, 0xB4, 0xB8, 0xB0, 0xD8, 0xB9, 0xAB, 0xF3, 0xF8, 0xFA, 0xB3, 0xB7, 0xBB, 0x8E, 0x9E,
0xAE, 0xF1, 0x32, 0xF5, 0x1B, 0xF1, 0xB4, 0xB8, 0xB0, 0x80, 0x97, 0xF1, 0xA9, 0xDF, 0xDF, 0xDF,
0xAA, 0xDF, 0xDF, 0xDF, 0xF2, 0xAA, 0x4C, 0xCD, 0x6C, 0xA9, 0x0C, 0xC9, 0x2C, 0x97, 0xF1, 0xA9,
0x89, 0x26, 0x46, 0x66, 0xB2, 0x89, 0x99, 0xA9, 0x2D, 0x55, 0x7D, 0xB0, 0xB0, 0x8A, 0xA8, 0x96,
0x36, 0x56, 0x76, 0xF1, 0xBA, 0xA3, 0xB4, 0xB2, 0x80, 0xC0, 0xB8, 0xA8, 0x97, 0x11, 0xB2, 0x83,
0x98, 0xBA, 0xA3, 0xF0, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0xB2, 0xB9, 0xB4, 0x98, 0x83, 0xF1,
0xA3, 0x29, 0x55, 0x7D, 0xBA, 0xB5, 0xB1, 0xA3, 0x83, 0x93, 0xF0, 0x00, 0x28, 0x50, 0xF5, 0xB2,
0xB6, 0xAA, 0x83, 0x93, 0x28, 0x54, 0x7C, 0xF1, 0xB9, 0xA3, 0x82, 0x93, 0x61, 0xBA, 0xA2, 0xDA,
0xDE, 0xDF, 0xDB, 0x81, 0x9A, 0xB9, 0xAE, 0xF5, 0x60, 0x68, 0x70, 0xF1, 0xDA, 0xBA, 0xA2, 0xDF,
0xD9, 0xBA, 0xA2, 0xFA, 0xB9, 0xA3, 0x82, 0x92, 0xDB, 0x31, 0xBA, 0xA2, 0xD9, 0xBA, 0xA2, 0xF8,
0xDF, 0x85, 0xA4, 0xD0, 0xC1, 0xBB, 0xAD, 0x83, 0xC2, 0xC5, 0xC7, 0xB8, 0xA2, 0xDF, 0xDF, 0xDF,
0xBA, 0xA0, 0xDF, 0xDF, 0xDF, 0xD8, 0xD8, 0xF1, 0xB8, 0xAA, 0xB3, 0x8D, 0xB4, 0x98, 0x0D, 0x35,
0x5D, 0xB2, 0xB6, 0xBA, 0xAF, 0x8C, 0x96, 0x19, 0x8F, 0x9F, 0xA7, 0x0E, 0x16, 0x1E, 0xB4, 0x9A,
0xB8, 0xAA, 0x87, 0x2C, 0x54, 0x7C, 0xBA, 0xA4, 0xB0, 0x8A, 0xB6, 0x91, 0x32, 0x56, 0x76, 0xB2,
0x84, 0x94, 0xA4, 0xC8, 0x08, 0xCD, 0xD8, 0xB8, 0xB4, 0xB0, 0xF1, 0x99, 0x82, 0xA8, 0x2D, 0x55,
0x7D, 0x98, 0xA8, 0x0E, 0x16, 0x1E, 0xA2, 0x2C, 0x54, 0x7C, 0x92, 0xA4, 0xF0, 0x2C, 0x50, 0x78,
/* bank # 5 */
0xF1, 0x84, 0xA8, 0x98, 0xC4, 0xCD, 0xFC, 0xD8, 0x0D, 0xDB, 0xA8, 0xFC, 0x2D, 0xF3, 0xD9, 0xBA,
0xA6, 0xF8, 0xDA, 0xBA, 0xA6, 0xDE, 0xD8, 0xBA, 0xB2, 0xB6, 0x86, 0x96, 0xA6, 0xD0, 0xF3, 0xC8,
0x41, 0xDA, 0xA6, 0xC8, 0xF8, 0xD8, 0xB0, 0xB4, 0xB8, 0x82, 0xA8, 0x92, 0xF5, 0x2C, 0x54, 0x88,
0x98, 0xF1, 0x35, 0xD9, 0xF4, 0x18, 0xD8, 0xF1, 0xA2, 0xD0, 0xF8, 0xF9, 0xA8, 0x84, 0xD9, 0xC7,
0xDF, 0xF8, 0xF8, 0x83, 0xC5, 0xDA, 0xDF, 0x69, 0xDF, 0x83, 0xC1, 0xD8, 0xF4, 0x01, 0x14, 0xF1,
0xA8, 0x82, 0x4E, 0xA8, 0x84, 0xF3, 0x11, 0xD1, 0x82, 0xF5, 0xD9, 0x92, 0x28, 0x97, 0x88, 0xF1,
0x09, 0xF4, 0x1C, 0x1C, 0xD8, 0x84, 0xA8, 0xF3, 0xC0, 0xF9, 0xD1, 0xD9, 0x97, 0x82, 0xF1, 0x29,
0xF4, 0x0D, 0xD8, 0xF3, 0xF9, 0xF9, 0xD1, 0xD9, 0x82, 0xF4, 0xC2, 0x03, 0xD8, 0xDE, 0xDF, 0x1A,
0xD8, 0xF1, 0xA2, 0xFA, 0xF9, 0xA8, 0x84, 0x98, 0xD9, 0xC7, 0xDF, 0xF8, 0xF8, 0xF8, 0x83, 0xC7,
0xDA, 0xDF, 0x69, 0xDF, 0xF8, 0x83, 0xC3, 0xD8, 0xF4, 0x01, 0x14, 0xF1, 0x98, 0xA8, 0x82, 0x2E,
0xA8, 0x84, 0xF3, 0x11, 0xD1, 0x82, 0xF5, 0xD9, 0x92, 0x50, 0x97, 0x88, 0xF1, 0x09, 0xF4, 0x1C,
0xD8, 0x84, 0xA8, 0xF3, 0xC0, 0xF8, 0xF9, 0xD1, 0xD9, 0x97, 0x82, 0xF1, 0x49, 0xF4, 0x0D, 0xD8,
0xF3, 0xF9, 0xF9, 0xD1, 0xD9, 0x82, 0xF4, 0xC4, 0x03, 0xD8, 0xDE, 0xDF, 0xD8, 0xF1, 0xAD, 0x88,
0x98, 0xCC, 0xA8, 0x09, 0xF9, 0xD9, 0x82, 0x92, 0xA8, 0xF5, 0x7C, 0xF1, 0x88, 0x3A, 0xCF, 0x94,
0x4A, 0x6E, 0x98, 0xDB, 0x69, 0x31, 0xDA, 0xAD, 0xF2, 0xDE, 0xF9, 0xD8, 0x87, 0x95, 0xA8, 0xF2,
0x21, 0xD1, 0xDA, 0xA5, 0xF9, 0xF4, 0x17, 0xD9, 0xF1, 0xAE, 0x8E, 0xD0, 0xC0, 0xC3, 0xAE, 0x82,
/* bank # 6 */
0xC6, 0x84, 0xC3, 0xA8, 0x85, 0x95, 0xC8, 0xA5, 0x88, 0xF2, 0xC0, 0xF1, 0xF4, 0x01, 0x0E, 0xF1,
0x8E, 0x9E, 0xA8, 0xC6, 0x3E, 0x56, 0xF5, 0x54, 0xF1, 0x88, 0x72, 0xF4, 0x01, 0x15, 0xF1, 0x98,
0x45, 0x85, 0x6E, 0xF5, 0x8E, 0x9E, 0x04, 0x88, 0xF1, 0x42, 0x98, 0x5A, 0x8E, 0x9E, 0x06, 0x88,
0x69, 0xF4, 0x01, 0x1C, 0xF1, 0x98, 0x1E, 0x11, 0x08, 0xD0, 0xF5, 0x04, 0xF1, 0x1E, 0x97, 0x02,
0x02, 0x98, 0x36, 0x25, 0xDB, 0xF9, 0xD9, 0x85, 0xA5, 0xF3, 0xC1, 0xDA, 0x85, 0xA5, 0xF3, 0xDF,
0xD8, 0x85, 0x95, 0xA8, 0xF3, 0x09, 0xDA, 0xA5, 0xFA, 0xD8, 0x82, 0x92, 0xA8, 0xF5, 0x78, 0xF1,
0x88, 0x1A, 0x84, 0x9F, 0x26, 0x88, 0x98, 0x21, 0xDA, 0xF4, 0x1D, 0xF3, 0xD8, 0x87, 0x9F, 0x39,
0xD1, 0xAF, 0xD9, 0xDF, 0xDF, 0xFB, 0xF9, 0xF4, 0x0C, 0xF3, 0xD8, 0xFA, 0xD0, 0xF8, 0xDA, 0xF9,
0xF9, 0xD0, 0xDF, 0xD9, 0xF9, 0xD8, 0xF4, 0x0B, 0xD8, 0xF3, 0x87, 0x9F, 0x39, 0xD1, 0xAF, 0xD9,
0xDF, 0xDF, 0xF4, 0x1D, 0xF3, 0xD8, 0xFA, 0xFC, 0xA8, 0x69, 0xF9, 0xF9, 0xAF, 0xD0, 0xDA, 0xDE,
0xFA, 0xD9, 0xF8, 0x8F, 0x9F, 0xA8, 0xF1, 0xCC, 0xF3, 0x98, 0xDB, 0x45, 0xD9, 0xAF, 0xDF, 0xD0,
0xF8, 0xD8, 0xF1, 0x8F, 0x9F, 0xA8, 0xCA, 0xF3, 0x88, 0x09, 0xDA, 0xAF, 0x8F, 0xCB, 0xF8, 0xD8,
0xF2, 0xAD, 0x97, 0x8D, 0x0C, 0xD9, 0xA5, 0xDF, 0xF9, 0xBA, 0xA6, 0xF3, 0xFA, 0xF4, 0x12, 0xF2,
0xD8, 0x95, 0x0D, 0xD1, 0xD9, 0xBA, 0xA6, 0xF3, 0xFA, 0xDA, 0xA5, 0xF2, 0xC1, 0xBA, 0xA6, 0xF3,
0xDF, 0xD8, 0xF1, 0xBA, 0xB2, 0xB6, 0x86, 0x96, 0xA6, 0xD0, 0xCA, 0xF3, 0x49, 0xDA, 0xA6, 0xCB,
0xF8, 0xD8, 0xB0, 0xB4, 0xB8, 0xD8, 0xAD, 0x84, 0xF2, 0xC0, 0xDF, 0xF1, 0x8F, 0xCB, 0xC3, 0xA8,
/* bank # 7 */
0xB2, 0xB6, 0x86, 0x96, 0xC8, 0xC1, 0xCB, 0xC3, 0xF3, 0xB0, 0xB4, 0x88, 0x98, 0xA8, 0x21, 0xDB,
0x71, 0x8D, 0x9D, 0x71, 0x85, 0x95, 0x21, 0xD9, 0xAD, 0xF2, 0xFA, 0xD8, 0x85, 0x97, 0xA8, 0x28,
0xD9, 0xF4, 0x08, 0xD8, 0xF2, 0x8D, 0x29, 0xDA, 0xF4, 0x05, 0xD9, 0xF2, 0x85, 0xA4, 0xC2, 0xF2,
0xD8, 0xA8, 0x8D, 0x94, 0x01, 0xD1, 0xD9, 0xF4, 0x11, 0xF2, 0xD8, 0x87, 0x21, 0xD8, 0xF4, 0x0A,
0xD8, 0xF2, 0x84, 0x98, 0xA8, 0xC8, 0x01, 0xD1, 0xD9, 0xF4, 0x11, 0xD8, 0xF3, 0xA4, 0xC8, 0xBB,
0xAF, 0xD0, 0xF2, 0xDE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xD8, 0xF1, 0xB8, 0xF6,
0xB5, 0xB9, 0xB0, 0x8A, 0x95, 0xA3, 0xDE, 0x3C, 0xA3, 0xD9, 0xF8, 0xD8, 0x5C, 0xA3, 0xD9, 0xF8,
0xD8, 0x7C, 0xA3, 0xD9, 0xF8, 0xD8, 0xF8, 0xF9, 0xD1, 0xA5, 0xD9, 0xDF, 0xDA, 0xFA, 0xD8, 0xB1,
0x85, 0x30, 0xF7, 0xD9, 0xDE, 0xD8, 0xF8, 0x30, 0xAD, 0xDA, 0xDE, 0xD8, 0xF2, 0xB4, 0x8C, 0x99,
0xA3, 0x2D, 0x55, 0x7D, 0xA0, 0x83, 0xDF, 0xDF, 0xDF, 0xB5, 0x91, 0xA0, 0xF6, 0x29, 0xD9, 0xFB,
0xD8, 0xA0, 0xFC, 0x29, 0xD9, 0xFA, 0xD8, 0xA0, 0xD0, 0x51, 0xD9, 0xF8, 0xD8, 0xFC, 0x51, 0xD9,
0xF9, 0xD8, 0x79, 0xD9, 0xFB, 0xD8, 0xA0, 0xD0, 0xFC, 0x79, 0xD9, 0xFA, 0xD8, 0xA1, 0xF9, 0xF9,
0xF9, 0xF9, 0xF9, 0xA0, 0xDA, 0xDF, 0xDF, 0xDF, 0xD8, 0xA1, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xAC,
0xDE, 0xF8, 0xAD, 0xDE, 0x83, 0x93, 0xAC, 0x2C, 0x54, 0x7C, 0xF1, 0xA8, 0xDF, 0xDF, 0xDF, 0xF6,
0x9D, 0x2C, 0xDA, 0xA0, 0xDF, 0xD9, 0xFA, 0xDB, 0x2D, 0xF8, 0xD8, 0xA8, 0x50, 0xDA, 0xA0, 0xD0,
0xDE, 0xD9, 0xD0, 0xF8, 0xF8, 0xF8, 0xDB, 0x55, 0xF8, 0xD8, 0xA8, 0x78, 0xDA, 0xA0, 0xD0, 0xDF,
/* bank # 8 */
0xD9, 0xD0, 0xFA, 0xF8, 0xF8, 0xF8, 0xF8, 0xDB, 0x7D, 0xF8, 0xD8, 0x9C, 0xA8, 0x8C, 0xF5, 0x30,
0xDB, 0x38, 0xD9, 0xD0, 0xDE, 0xDF, 0xA0, 0xD0, 0xDE, 0xDF, 0xD8, 0xA8, 0x48, 0xDB, 0x58, 0xD9,
0xDF, 0xD0, 0xDE, 0xA0, 0xDF, 0xD0, 0xDE, 0xD8, 0xA8, 0x68, 0xDB, 0x70, 0xD9, 0xDF, 0xDF, 0xA0,
0xDF, 0xDF, 0xD8, 0xF1, 0xA8, 0x88, 0x90, 0x2C, 0x54, 0x7C, 0x98, 0xA8, 0xD0, 0x5C, 0x38, 0xD1,
0xDA, 0xF2, 0xAE, 0x8C, 0xDF, 0xF9, 0xD8, 0xB0, 0x87, 0xA8, 0xC1, 0xC1, 0xB1, 0x88, 0xA8, 0xC6,
0xF9, 0xF9, 0xDA, 0x36, 0xD8, 0xA8, 0xF9, 0xDA, 0x36, 0xD8, 0xA8, 0xF9, 0xDA, 0x36, 0xD8, 0xA8,
0xF9, 0xDA, 0x36, 0xD8, 0xA8, 0xF9, 0xDA, 0x36, 0xD8, 0xF7, 0x8D, 0x9D, 0xAD, 0xF8, 0x18, 0xDA,
0xF2, 0xAE, 0xDF, 0xD8, 0xF7, 0xAD, 0xFA, 0x30, 0xD9, 0xA4, 0xDE, 0xF9, 0xD8, 0xF2, 0xAE, 0xDE,
0xFA, 0xF9, 0x83, 0xA7, 0xD9, 0xC3, 0xC5, 0xC7, 0xF1, 0x88, 0x9B, 0xA7, 0x7A, 0xAD, 0xF7, 0xDE,
0xDF, 0xA4, 0xF8, 0x84, 0x94, 0x08, 0xA7, 0x97, 0xF3, 0x00, 0xAE, 0xF2, 0x98, 0x19, 0xA4, 0x88,
0xC6, 0xA3, 0x94, 0x88, 0xF6, 0x32, 0xDF, 0xF2, 0x83, 0x93, 0xDB, 0x09, 0xD9, 0xF2, 0xAA, 0xDF,
0xD8, 0xD8, 0xAE, 0xF8, 0xF9, 0xD1, 0xDA, 0xF3, 0xA4, 0xDE, 0xA7, 0xF1, 0x88, 0x9B, 0x7A, 0xD8,
0xF3, 0x84, 0x94, 0xAE, 0x19, 0xF9, 0xDA, 0xAA, 0xF1, 0xDF, 0xD8, 0xA8, 0x81, 0xC0, 0xC3, 0xC5,
0xC7, 0xA3, 0x92, 0x83, 0xF6, 0x28, 0xAD, 0xDE, 0xD9, 0xF8, 0xD8, 0xA3, 0x50, 0xAD, 0xD9, 0xF8,
0xD8, 0xA3, 0x78, 0xAD, 0xD9, 0xF8, 0xD8, 0xF8, 0xF9, 0xD1, 0xA1, 0xDA, 0xDE, 0xC3, 0xC5, 0xC7,
0xD8, 0xA1, 0x81, 0x94, 0xF8, 0x18, 0xF2, 0xB0, 0x89, 0xAC, 0xC3, 0xC5, 0xC7, 0xF1, 0xD8, 0xB8,
/* bank # 9 */
0xB4, 0xB0, 0x97, 0x86, 0xA8, 0x31, 0x9B, 0x06, 0x99, 0x07, 0xAB, 0x97, 0x28, 0x88, 0x9B, 0xF0,
0x0C, 0x20, 0x14, 0x40, 0xB0, 0xB4, 0xB8, 0xF0, 0xA8, 0x8A, 0x9A, 0x28, 0x50, 0x78, 0xB7, 0x9B,
0xA8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xF1, 0xBB, 0xAB,
0x88, 0x00, 0x2C, 0x54, 0x7C, 0xF0, 0xB3, 0x8B, 0xB8, 0xA8, 0x04, 0x28, 0x50, 0x78, 0xF1, 0xB0,
0x88, 0xB4, 0x97, 0x26, 0xA8, 0x59, 0x98, 0xBB, 0xAB, 0xB3, 0x8B, 0x02, 0x26, 0x46, 0x66, 0xB0,
0xB8, 0xF0, 0x8A, 0x9C, 0xA8, 0x29, 0x51, 0x79, 0x8B, 0x29, 0x51, 0x79, 0x8A, 0x24, 0x70, 0x59,
0x8B, 0x20, 0x58, 0x71, 0x8A, 0x44, 0x69, 0x38, 0x8B, 0x39, 0x40, 0x68, 0x8A, 0x64, 0x48, 0x31,
0x8B, 0x30, 0x49, 0x60, 0x88, 0xF1, 0xAC, 0x00, 0x2C, 0x54, 0x7C, 0xF0, 0x8C, 0xA8, 0x04, 0x28,
0x50, 0x78, 0xF1, 0x88, 0x97, 0x26, 0xA8, 0x59, 0x98, 0xAC, 0x8C, 0x02, 0x26, 0x46, 0x66, 0xF0,
0x89, 0x9C, 0xA8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xA9,
0x88, 0x09, 0x20, 0x59, 0x70, 0xAB, 0x11, 0x38, 0x40, 0x69, 0xA8, 0x19, 0x31, 0x48, 0x60, 0x8C,
0xA8, 0x3C, 0x41, 0x5C, 0x20, 0x7C, 0x00, 0xF1, 0x87, 0x98, 0x19, 0x86, 0xA8, 0x6E, 0x76, 0x7E,
0xA9, 0x99, 0x88, 0x2D, 0x55, 0x7D, 0xD8, 0xB1, 0xB5, 0xB9, 0xA3, 0xDF, 0xDF, 0xDF, 0xAE, 0xD0,
0xDF, 0xAA, 0xD0, 0xDE, 0xF2, 0xAB, 0xF8, 0xF9, 0xD9, 0xB0, 0x87, 0xC4, 0xAA, 0xF1, 0xDF, 0xDF,
0xBB, 0xAF, 0xDF, 0xDF, 0xB9, 0xD8, 0xB1, 0xF1, 0xA3, 0x97, 0x8E, 0x60, 0xDF, 0xB0, 0x84, 0xF2,
0xC8, 0xF8, 0xF9, 0xD9, 0xDE, 0xD8, 0x93, 0x85, 0xF1, 0x4A, 0xB1, 0x83, 0xA3, 0x08, 0xB5, 0x83,
/* bank # 10 */
0x9A, 0x08, 0x10, 0xB7, 0x9F, 0x10, 0xD8, 0xF1, 0xB0, 0xBA, 0xAE, 0xB0, 0x8A, 0xC2, 0xB2, 0xB6,
0x8E, 0x9E, 0xF1, 0xFB, 0xD9, 0xF4, 0x1D, 0xD8, 0xF9, 0xD9, 0x0C, 0xF1, 0xD8, 0xF8, 0xF8, 0xAD,
0x61, 0xD9, 0xAE, 0xFB, 0xD8, 0xF4, 0x0C, 0xF1, 0xD8, 0xF8, 0xF8, 0xAD, 0x19, 0xD9, 0xAE, 0xFB,
0xDF, 0xD8, 0xF4, 0x16, 0xF1, 0xD8, 0xF8, 0xAD, 0x8D, 0x61, 0xD9, 0xF4, 0xF4, 0xAC, 0xF5, 0x9C,
0x9C, 0x8D, 0xDF, 0x2B, 0xBA, 0xB6, 0xAE, 0xFA, 0xF8, 0xF4, 0x0B, 0xD8, 0xF1, 0xAE, 0xD0, 0xF8,
0xAD, 0x51, 0xDA, 0xAE, 0xFA, 0xF8, 0xF1, 0xD8, 0xB9, 0xB1, 0xB6, 0xA3, 0x83, 0x9C, 0x08, 0xB9,
0xB1, 0x83, 0x9A, 0xB5, 0xAA, 0xC0, 0xFD, 0x30, 0x83, 0xB7, 0x9F, 0x10, 0xB5, 0x8B, 0x93, 0xF2,
0x02, 0x02, 0xD1, 0xAB, 0xDA, 0xDE, 0xD8, 0xF1, 0xB0, 0x80, 0xBA, 0xAB, 0xC0, 0xC3, 0xB2, 0x84,
0xC1, 0xC3, 0xD8, 0xB1, 0xB9, 0xF3, 0x8B, 0xA3, 0x91, 0xB6, 0x09, 0xB4, 0xD9, 0xAB, 0xDE, 0xB0,
0x87, 0x9C, 0xB9, 0xA3, 0xDD, 0xF1, 0xB3, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0xB0, 0x87, 0x20, 0x28,
0x30, 0x38, 0xB2, 0x8B, 0xB6, 0x9B, 0xF2, 0xA3, 0xC0, 0xC8, 0xC2, 0xC4, 0xCC, 0xC6, 0xA3, 0xA3,
0xA3, 0xF1, 0xB0, 0x87, 0xB5, 0x9A, 0xD8, 0xF3, 0x9B, 0xA3, 0xA3, 0xDC, 0xBA, 0xAC, 0xDF, 0xB9, //Reverted back as packet size changes causing isues... TODO:change 2742 from 0xD8 to 0x20 Including the DMP_FEATURE_TAP -- known issue in which if you do not enable DMP_FEATURE_TAP then the interrupts will be at 200Hz even if fifo rate
0xA3, 0xFE, 0xF2, 0xAB, 0xC4, 0xAA, 0xF1, 0xDF, 0xDF, 0xBB, 0xAF, 0xDF, 0xDF, 0xA3, 0xA3, 0xA3,
0xD8, 0xD8, 0xD8, 0xBB, 0xB3, 0xB7, 0xF1, 0xAA, 0xF9, 0xDA, 0xFF, 0xD9, 0x80, 0x9A, 0xAA, 0x28,
0xB4, 0x80, 0x98, 0xA7, 0x20, 0xB7, 0x97, 0x87, 0xA8, 0x66, 0x88, 0xF0, 0x79, 0x51, 0xF1, 0x90,
0x2C, 0x87, 0x0C, 0xA7, 0x81, 0x97, 0x62, 0x93, 0xF0, 0x71, 0x71, 0x60, 0x85, 0x94, 0x01, 0x29,
/* bank # 11 */
0x51, 0x79, 0x90, 0xA5, 0xF1, 0x28, 0x4C, 0x6C, 0x87, 0x0C, 0x95, 0x18, 0x85, 0x78, 0xA3, 0x83,
0x90, 0x28, 0x4C, 0x6C, 0x88, 0x6C, 0xD8, 0xF3, 0xA2, 0x82, 0x00, 0xF2, 0x10, 0xA8, 0x92, 0x19,
0x80, 0xA2, 0xF2, 0xD9, 0x26, 0xD8, 0xF1, 0x88, 0xA8, 0x4D, 0xD9, 0x48, 0xD8, 0x96, 0xA8, 0x39,
0x80, 0xD9, 0x3C, 0xD8, 0x95, 0x80, 0xA8, 0x39, 0xA6, 0x86, 0x98, 0xD9, 0x2C, 0xDA, 0x87, 0xA7,
0x2C, 0xD8, 0xA8, 0x89, 0x95, 0x19, 0xA9, 0x80, 0xD9, 0x38, 0xD8, 0xA8, 0x89, 0x39, 0xA9, 0x80,
0xDA, 0x3C, 0xD8, 0xA8, 0x2E, 0xA8, 0x39, 0x90, 0xD9, 0x0C, 0xD8, 0xA8, 0x95, 0x31, 0x98, 0xD9,
0x0C, 0xD8, 0xA8, 0x09, 0xD9, 0xFF, 0xD8, 0x01, 0xDA, 0xFF, 0xD8, 0x95, 0x39, 0xA9, 0xDA, 0x26,
0xFF, 0xD8, 0x90, 0xA8, 0x0D, 0x89, 0x99, 0xA8, 0x10, 0x80, 0x98, 0x21, 0xDA, 0x2E, 0xD8, 0x89,
0x99, 0xA8, 0x31, 0x80, 0xDA, 0x2E, 0xD8, 0xA8, 0x86, 0x96, 0x31, 0x80, 0xDA, 0x2E, 0xD8, 0xA8,
0x87, 0x31, 0x80, 0xDA, 0x2E, 0xD8, 0xA8, 0x82, 0x92, 0xF3, 0x41, 0x80, 0xF1, 0xD9, 0x2E, 0xD8,
0xA8, 0x82, 0xF3, 0x19, 0x80, 0xF1, 0xD9, 0x2E, 0xD8, 0x82, 0xAC, 0xF3, 0xC0, 0xA2, 0x80, 0x22,
0xF1, 0xA6, 0x2E, 0xA7, 0x2E, 0xA9, 0x22, 0x98, 0xA8, 0x29, 0xDA, 0xAC, 0xDE, 0xFF, 0xD8, 0xA2,
0xF2, 0x2A, 0xF1, 0xA9, 0x2E, 0x82, 0x92, 0xA8, 0xF2, 0x31, 0x80, 0xA6, 0x96, 0xF1, 0xD9, 0x00,
0xAC, 0x8C, 0x9C, 0x0C, 0x30, 0xAC, 0xDE, 0xD0, 0xDE, 0xFF, 0xD8, 0x8C, 0x9C, 0xAC, 0xD0, 0x10,
0xAC, 0xDE, 0x80, 0x92, 0xA2, 0xF2, 0x4C, 0x82, 0xA8, 0xF1, 0xCA, 0xF2, 0x35, 0xF1, 0x96, 0x88,
0xA6, 0xD9, 0x00, 0xD8, 0xF1, 0xFF,
};

static int i2c_init(void);
static int init_dmp(void);
static int init_mpu6050(void);
static int get_bus(void);
static void reset(void);
static void set_sleep_config(uint8_t enable);
static void set_clock_source(uint8_t source);
static void set_rot_range(uint8_t range);
static void set_accel_range(uint8_t range);
static int test_connnection(void);
static void get_raw_motion(void);
static uint8_t read_register(uint8_t reg, uint8_t *data);
static uint8_t write_register(uint8_t reg, uint8_t *data);
static int write_bytes(uint8_t reg, uint8_t *data, int length);
static int write_word(uint8_t reg, uint16_t *data);
static uint8_t read_bytes(uint8_t reg, uint8_t *buffer, int length);
static uint8_t read_word(uint8_t reg, uint16_t *buffer);
static uint8_t set_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t data);
static void read_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t *data);
static void print_imu_data(imu_type *imu_data);
static void get_raw_accel(void);
static void get_raw_rot(void);
static void get_temperature(void);
static int get_dmp_status(void);
static void set_dmp_enable(int enable);
static void reset_dmp(void);
static void reset_signal_path(void);
static void enable_mpu_fifo(void);
static void disable_all_int(void);
static void set_sample_rate(void);
static void configure_dlpf(void);
static void enable_fifo(void);
static void reset_fifo(void);
static void enable_dpm_int(void);
static void get_dmp_accel(void);
static int write_memory_block(const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, int verify, int useProgMem);
static int write_program_block(const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, int verify);
static void set_memory_start_address(uint8_t address);
static void set_memory_bank(uint8_t bank, int prefetchEnabled, int userBank);
static int set_dmp_start_address(void);
static int get_dmp_fifo(uint8_t numPackets, uint8_t *processed);
static void read_fifo(uint8_t *buffer, int length);
static uint8_t process_dmp_fifo(const unsigned char *dmpData);


int i2c_device;
uint8_t motion_buffer[14];
mpu6050_config_t mpu6050_config;
imu_type raw_data;
uint8_t user_ctrl;
uint8_t *dmpPacketBuffer;
uint16_t dmpPacketSize;

/*
* Initialise MPU6050 component
*/
int MPU6050(void) {
    printf("Initializing mpu6050....\n");

    i2c_init();
    if(init_mpu6050() == SUCCESS) {
        printf("Mpu6050 initialised successfully.\n");
    } else {
         printf("Mpu6050 failed to initialise.\n");
    }

    if(init_dmp() == SUCCESS) {
        printf("DMP initialised successfully.\n");
    } else {
         printf("DMP failed to initialise.\n");
    }

    // Set up interupts pins

    // Set offest for gyro and accel

    // Calibrate 

    // Enable dmp

    // Get dmp packet to process

    return 0;
}

/*
* Initialise MPU6050 component
*/
static int init_mpu6050(void) {
    reset();
    set_sleep_config(false);
    set_clock_source(MPU6050_CLOCK_PLL_XGYRO);
    set_rot_range(MPU6050_GYRO_FS_250);
    set_accel_range(MPU6050_ACCEL_FS_2);    
    test_connnection();

    return 0;
}

/*
* Initialise Digital Motion Processor
* Based on Jeff Rowberg library
*/
static int init_dmp(void) {
    reset();
    sleep(0.1);
    reset_signal_path();
    sleep(0.1);
    set_clock_source(MPU6050_CLOCK_PLL_XGYRO);
    disable_all_int();
    enable_mpu_fifo();
    set_accel_range(MPU6050_ACCEL_FS_2);  
    set_clock_source(MPU6050_CLOCK_PLL_XGYRO); 
    set_sample_rate();
    configure_dlpf();
    write_program_block(dmp_memory, MPU6050_DMP_CODE_SIZE, 0, 0, true);
    set_dmp_start_address();
    set_rot_range(MPU6050_GYRO_FS_250);
    enable_fifo();
    reset_fifo();
    enable_dpm_int();
    reset_fifo();
    set_dmp_enable(false);
    dmpPacketSize = 28;

    return 0;
}
/*
* MPU6050 main loop
*/
void MPU6050_Run(imu_type *imu_data) {
    while(1) {
        print_imu_data(imu_data);
        sleep(1);       
    }
}

/*
* Initialise linux i2c instance
*/
static int i2c_init(void) {

    int ret = -1;
    i2c_device = open(I2C_DEVICE, O_RDWR);

	if (i2c_device < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return -1;
	}
	
    get_bus();

    return 0;
}

/*
* Get access to i2c buss
*/
static int get_bus(void) {
    int ret = -1;
     ret = ioctl(i2c_device, I2C_SLAVE, DEV_ADR) < 0;
	if (ret < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		exit(1);
        return ret;
	}

    return ret;
}

/*
* Set bit 7 of Power Management 1 register
*/
static void reset(void) {
    uint8_t temp;
    read_register(PWR_MGT_1, &temp);
    mpu6050_config.pwr_mgt_1 = temp | (1 << MPU6050_PWR1_DEVICE_RESET_BIT);
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1); 
}

/*
* Set sleep enable/disabled
*/
static void set_sleep_config(uint8_t enable) {
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    
    if (enable) {
        mpu6050_config.pwr_mgt_1 |= (1 << MPU6050_PWR1_SLEEP_BIT);
    } else {
        mpu6050_config.pwr_mgt_1 &= ~(1 << MPU6050_PWR1_SLEEP_BIT);
    }
   
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
}

/*
* Set clock source
*/
static void set_clock_source(uint8_t source) {
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    mpu6050_config.pwr_mgt_1 = set_bits(mpu6050_config.pwr_mgt_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
}

/*
* Set rotation range
*/
static void set_rot_range(uint8_t range) {
    read_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.rot_config);
    mpu6050_config.rot_config = set_bits(mpu6050_config.rot_config, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
    write_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.rot_config);
    sleep(0.1);
    read_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.rot_config);
}

/*
* Set accelerometer range
*/
static void set_accel_range(uint8_t range) {
    uint8_t temp;
    read_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
    mpu6050_config.accel_config = set_bits(mpu6050_config.accel_config, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
    write_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
    sleep(0.1);
    read_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
}

/*
* Get device id
*/
static uint8_t get_device_id(void) {
    read_register(MPU6050_RA_WHO_AM_I, &mpu6050_config.device_id);
    // read_bits(device_id, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &device_id);
    return mpu6050_config.device_id;
}

/*
* Test connection by geting device id
*/
int test_connnection(void) {
    uint8_t temp = get_device_id();

    if (temp == DEFAULT_ID) {
        return true;
    }

    return false;
}

/*
* Get raw motion data
*/
static void get_raw_motion(void) {
    read_bytes(MPU6050_RA_ACCEL_XOUT_H, motion_buffer, 14);
   
    raw_data.accel[0] = (((int16_t)motion_buffer[0]) << 8) | motion_buffer[1];
    raw_data.accel[1] = (((int16_t)motion_buffer[2]) << 8) | motion_buffer[3];
    raw_data.accel[2] = (((int16_t)motion_buffer[4]) << 8) | motion_buffer[5];
    raw_data.rot[0] = (((int16_t)motion_buffer[8]) << 8) | motion_buffer[9];
    raw_data.rot[1] = (((int16_t)motion_buffer[10]) << 8) | motion_buffer[11];
    raw_data.rot[2] = (((int16_t)motion_buffer[12]) << 8) | motion_buffer[13];
}

/*
* Get raw acceleration
*/
static void get_raw_accel(void) {
    read_bytes(MPU6050_RA_ACCEL_XOUT_H, motion_buffer, 6);
   
    raw_data.accel[0] = (((int16_t)motion_buffer[0]) << 8) | motion_buffer[1];
    raw_data.accel[1] = (((int16_t)motion_buffer[2]) << 8) | motion_buffer[3];
    raw_data.accel[2] = (((int16_t)motion_buffer[4]) << 8) | motion_buffer[5];
}

/*
* Get raw rotation
*/
static void get_raw_rot(void) {
    read_bytes(MPU6050_RA_GYRO_XOUT_H, motion_buffer, 2);
   
    raw_data.accel[0] = (((int16_t)motion_buffer[0]) << 8) | motion_buffer[1];
    raw_data.accel[1] = (((int16_t)motion_buffer[2]) << 8) | motion_buffer[3];
    raw_data.accel[2] = (((int16_t)motion_buffer[4]) << 8) | motion_buffer[5];
}

/*
* Get temperature
*/
static void get_temperature(void) {
    read_bytes(MPU6050_RA_TEMP_OUT_H, motion_buffer, 6);
   
    raw_data.temp = (((int16_t)motion_buffer[0]) << 8) | motion_buffer[1];
}

/*
* print imu data
*/
static void print_imu_data(imu_type *imu_data) {
    printf("Acceleration data is: x: %f, y:%f, z:%f\n", imu_data->accel[0], imu_data->accel[1], imu_data->accel[2]);
    printf("Rotation data is: x: %f, y:%f, z:%f\n", imu_data->rot[0], imu_data->rot[1], imu_data->rot[2]);
    printf("Temperature data is: %f\n", imu_data->temp);
}

/*
* Read mpu6050 register
*/
uint8_t read_register(uint8_t reg, uint8_t *data) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = read(i2c_device, data, 1);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 1)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Write to mpu6050 register
*/
uint8_t write_register(uint8_t reg, uint8_t *data) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = write(i2c_device, data, 1);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 2)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Write bytes to mpu6050 register
*/
static int write_bytes(uint8_t reg, uint8_t *data, int length) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = write(i2c_device, data, length);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != length)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Write word(2 bytes) to mpu6050 register
*/
static int write_word(uint8_t reg, uint16_t *data) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = write(i2c_device, data, 2);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 2)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Read multiple bytes from mpu6050 registers
*/
uint8_t read_bytes(uint8_t reg, uint8_t *buffer, int length) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = read(i2c_device, buffer, length);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != length)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return *buffer;
}

/*
* Read word(2 bytes) from mpu6050 registers
*/
uint8_t read_word(uint8_t reg, uint16_t *buffer) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = read(i2c_device, buffer, 2);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 2)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return *buffer;
}

/*
* Set specific register bits
*/
static uint8_t set_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t data) {
    uint8_t mask = ((1 << bits_length) - 1) << (start_bit - bits_length + 1);
    data <<= (start_bit - bits_length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    reg &= ~(mask); // zero all important bits in existing byte
    reg |= data; // combine data with existing byte

    return reg;
}

/*
* Read specific register bits
*/
static void read_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t *data) {
    uint8_t mask = ((1 << bits_length) - 1) << (start_bit - bits_length + 1);
    reg &= mask;
    reg >>= (start_bit - bits_length + 1);
    *data = reg;
}

/*
* Get DMP enable/disable
*/
static int get_dmp_status(void) {
    uint8_t temp, read_bit;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    read_bits(temp, MPU6050_USERCTRL_DMP_EN_BIT, 1, &read_bit);
    return read_bit;
}

/*
* Enable DMP
*/
static void set_dmp_enable(int enable) {
    uint8_t temp;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    if (enable) {
        temp |= (1 << MPU6050_USERCTRL_DMP_EN_BIT);
    } else {
         temp &= ~(1 << MPU6050_USERCTRL_DMP_EN_BIT);
    }
   
    write_register(MPU6050_RA_USER_CTRL, &temp);
    read_register(MPU6050_RA_USER_CTRL, &user_ctrl);
}

/*
* Reset DMP
*/
static void reset_dmp(void) {
    uint8_t temp;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    temp |= (1 << MPU6050_USERCTRL_DMP_RESET_BIT);
    write_register(MPU6050_RA_USER_CTRL, &temp);
    read_register(MPU6050_RA_USER_CTRL, &user_ctrl);
}

/*
* Reset signal path
*/
static void reset_signal_path(void) {
    uint8_t temp;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    temp |= (1 << MPU6050_USERCTRL_SIG_COND_RESET_BIT);
    write_register(MPU6050_RA_USER_CTRL, &temp);
    read_register(MPU6050_RA_USER_CTRL, &user_ctrl);
}

/*
* Disable all interupts FIFO
*/
static void disable_all_int(void) {
    uint8_t temp;
    read_register(MPU6050_RA_INT_ENABLE, &temp);
    temp = 0x00;
    write_register(MPU6050_RA_INT_ENABLE, &temp);
    read_register(MPU6050_RA_USER_CTRL, &temp);
}

/*
* Enable FIFO
*/
static void enable_mpu_fifo(void) {
    uint8_t temp;
    read_register(MPU6050_RA_FIFO_EN, &temp);
    temp = 0x00;
    write_register(MPU6050_RA_FIFO_EN, &temp);
    read_register(MPU6050_RA_FIFO_EN, &temp);
}

/*
* Set sample rate
*/
static void set_sample_rate(void) {
    uint8_t temp;
    read_register(MPU6050_RA_SMPLRT_DIV, &temp);
    temp = 0x04; // 400khz
    write_register(MPU6050_RA_SMPLRT_DIV, &temp);
    read_register(MPU6050_RA_SMPLRT_DIV, &temp);
}

/*
* Configure digital low pass filter
*/
static void configure_dlpf(void) {
    uint8_t temp;
    read_register(MPU6050_RA_CONFIG, &temp);
    temp = 0x01; // 188Hz
    write_register(MPU6050_RA_CONFIG, &temp);
    read_register(MPU6050_RA_CONFIG, &temp);
}

static void set_memory_bank(uint8_t bank, int prefetchEnabled, int userBank) {
    bank &= 0x1F;
    if (userBank) bank |= 0x20;
    if (prefetchEnabled) bank |= 0x40;
    write_bytes(MPU6050_RA_BANK_SEL, &bank, 1);
}

static void set_memory_start_address(uint8_t address) {
    write_bytes(MPU6050_RA_MEM_START_ADDR, &address, 1);
}

static int write_program_block(const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, int verify) {
    return write_memory_block(data, MPU6050_DMP_CODE_SIZE, bank, address, verify, true);
}

/*
* Load DMP program
*/
static int write_memory_block(const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, int verify, int useProgMem) {
    set_memory_bank(bank, 0, 0);
    set_memory_start_address(address);
    uint8_t chunkSize;
    uint8_t *verifyBuffer=0;
    uint8_t *progBuffer=0;
    uint16_t i;
    uint8_t j;
    if (verify) verifyBuffer = (uint8_t *)malloc(MPU6050_DMP_MEMORY_CHUNK_SIZE);
    if (useProgMem) progBuffer = (uint8_t *)malloc(MPU6050_DMP_MEMORY_CHUNK_SIZE);
    for (i = 0; i < dataSize;) {
        // determine correct chunk size according to bank position and data size
        chunkSize = MPU6050_DMP_MEMORY_CHUNK_SIZE;

        // make sure we don't go past the data size
        if (i + chunkSize > dataSize) chunkSize = dataSize - i;

        // make sure this chunk doesn't go past the bank boundary (256 bytes)
        if (chunkSize > 256 - address) chunkSize = 256 - address;
        
        if (useProgMem) {
            // write the chunk of data as specified
            for (j = 0; j < chunkSize; j++) progBuffer[j] = pgm_read_byte(data + i + j);
        } else {
            // write the chunk of data as specified
            progBuffer = (uint8_t *)data + i;
        }

        write_bytes(MPU6050_RA_MEM_R_W, progBuffer, chunkSize);

        // verify data if needed
        if (verify && verifyBuffer) {
            set_memory_bank(bank, 0, 0);
            set_memory_start_address(address);
            read_bytes(MPU6050_RA_MEM_R_W, verifyBuffer, chunkSize);
           
            if (memcmp(progBuffer, verifyBuffer, chunkSize) != 0) {
                printf("Block write verification error, bank ");
                printf("%d", bank);
                printf(", address ");
                printf("%d", address);
                printf("!\nExpected:");

                for (j = 0; j < chunkSize; j++) {
                    printf(" 0x");
                    if (progBuffer[j] < 16) printf("0");
                    printf("%d", progBuffer[j]);
                }
                printf("\nReceived:");
                for (uint8_t j = 0; j < chunkSize; j++) {
                    printf(" 0x");
                    if (verifyBuffer[i + j] < 16) printf("0");
                    printf("%d", verifyBuffer[i + j]);
                }
                printf("\n");
                free(verifyBuffer);
                if (useProgMem) free(progBuffer);
                return false; // uh oh.
            }
        }

        // increase byte index by [chunkSize]
        i += chunkSize;

        // uint8_t automatically wraps to 0 at 256
        address += chunkSize;

        // if we aren't done, update bank (if necessary) and address
        if (i < dataSize) {
            if (address == 0) bank++;
            set_memory_bank(bank, 0, 0);
            set_memory_start_address(address);
        }
    }
    if (verify) free(verifyBuffer);
    if (useProgMem) free(progBuffer);
    return true;
}

/*
* Set DMP start address
*/
static int set_dmp_start_address(void) {
    uint16_t temp;
    read_word(MPU6050_RA_DMP_CFG_1, &temp);
    temp = 0x0400; 
    write_word(MPU6050_RA_DMP_CFG_1, &temp);
    read_word(MPU6050_RA_DMP_CFG_1, &temp);
}

/*
* Enable dmp fifo
*/
static void enable_fifo(void) {
    uint8_t temp;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    temp |= (1 << MPU6050_USERCTRL_FIFO_EN_BIT);
    write_register(MPU6050_RA_USER_CTRL, &temp);
    read_register(MPU6050_RA_USER_CTRL, &user_ctrl);
}

/*
* reset fifo
*/
static void reset_fifo(void) {
    uint8_t temp;
    read_register(MPU6050_RA_USER_CTRL, &temp);
    temp |= (1 << MPU6050_USERCTRL_FIFO_RESET_BIT);
    write_register(MPU6050_RA_USER_CTRL, &temp);
    read_register(MPU6050_RA_USER_CTRL, &user_ctrl);
}

/*
* Enable dmp int
*/
static void enable_dpm_int(void) {
    uint8_t temp;
    read_register(MPU6050_RA_INT_ENABLE, &temp);
    temp |= (1 << 6) ;
    write_register(MPU6050_RA_INT_ENABLE, &temp);
    read_register(MPU6050_RA_USER_CTRL, &temp);
}

/*
* Get dmp accelleration from fifo
*/
static void get_dmp_accel(void) {

}

/*
* Read fifo values
*/
static void read_fifo(uint8_t *buffer, int length) {
    read_bytes(MPU6050_RA_FIFO_R_W, buffer, length);
}

static uint8_t process_dmp_fifo(const unsigned char *dmpData) {
    (void)dmpData; // unused parameter
    /*for (uint8_t k = 0; k < dmpPacketSize; k++) {
        if (dmpData[k] < 0x10) printf("0");
        printf(dmpData[k], HEX);
        printf(" ");
    }
    printf("\n");*/
    //printfln((uint16_t)dmpPacketBuffer);
    return 0;
}

/*
* Read fifo values
*/
static int get_dmp_fifo(uint8_t numPackets, uint8_t *processed) {
    uint8_t status;
    uint8_t buf[dmpPacketSize];
    for (uint8_t i = 0; i < numPackets; i++) {
        // read packet from FIFO
        read_fifo(buf, dmpPacketSize);

        // process packet
        if ((status = process_dmp_fifo(buf)) > 0) return status;
        
    }
    return SUCCESS;
}




