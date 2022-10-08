/*****************************************************************************
* | File      	:   main-controller.c
* | Author      :   Fabrice Beya
* | Function    :   Main controller ochestrating the robot car
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-08
* | Info        :   
#
# Summary
******************************************************************************/


#ifndef _MAIN_CONTROLLER_H_
#define _MAIN_CONTROLLER_H_

#include "utils.h"
#include "slave-spi.h"
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

int MainController(spi_slave_config_t *_spi_slave_config);
void MainController_Run(void);

#endif