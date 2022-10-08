/*****************************************************************************
* | File      	:   utils.h
* | Author      :   Fabrice Beya
* | Function    :   Utility definitions used across the app
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-08
* | Info        :   
#
# Summary
******************************************************************************/


#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

// Commands
#define MOVE                0x20
#define SLEEP               0x21
#define REBOOT              0x22
#define STATUS              0x23
#define IDLE                0x24

#define FORWARD             1
#define BACKWARD            0

/**
 * @brief 
 * 4 byte message protocol
 * Command, Forward, Speed, Duration
 */

// Commands
#define COMMAND             0
#define DIRECTION           1
#define SPEED               2
#define DURATION            3

int MainController(void);
void Run(void);

#endif