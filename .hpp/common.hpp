/*
 * This header file defines some commom use key words and libraries.
 * 
 */ 

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <assert.h>

typedef unsigned char                           uint8_t
typedef unsigned short int                      uint16_t
typedef unsigned int                            uint32_t
typedef char                                    int8_t
typedef short int                               int16_t
typedef int                                     int32_t

#define ENABLE                                  0x55
#define DISABLE                                 0x00

#define ACTIVE                                  0x55
#define INACTIVE                                0x00

#define WORKING                                 0x55
#define HALTING                                 0x00

#define SUCCESS                                 0x55
#define FAILED                                  0x00

#define MTRUE                                   0x55
#define MFAILED                                 0x00


#endif

