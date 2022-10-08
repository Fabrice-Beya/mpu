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

#include "utils.h"
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

int SlaveSpi(void);
void SlaveSpi_Run(void);

#endif