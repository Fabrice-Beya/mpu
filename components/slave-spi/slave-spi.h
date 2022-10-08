/*****************************************************************************
* | File      	:   slave-spi.h
* | Author      :   Fabrice Beya
* | Function    :   Driver to communicate with slave mcu's over spi
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-01
* | Info        :   
#
# Summary
******************************************************************************/


#ifndef _SLAVE_SPI_H_
#define _SLAVE_SPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE          "/dev/spidev0.0"
#define SPI_SPEED           1000000
#define BITS_PER_WORD       8
#define BUF_LEN             4

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

int SlaveSpiInit(void);
void Monitor(void);
int SpiOpenPort (void);
int SpiClosePort (void);

#endif