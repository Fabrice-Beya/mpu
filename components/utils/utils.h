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
#include <pthread.h>

#define true                 1
#define false                0
#define SUCCESS              0
#define FAILURE              1

// Commands
#define MOVE                1
#define SLEEP               2
#define REBOOT              3
#define STATUS              4
#define IDLE                5

#define FORWARD             1
#define BACKWARD            2
#define FORWARD_LEFT        3
#define FORWARD_RIGHT       4
#define BACKWARD_LEFT       5
#define BACKWARD_RIGHT      6

/**
 * @brief 
 * 4 byte message protocol
 * Command, Forward, Speed, Duration
 */

// Commands
#define COMMAND             0
#define DIRECTION           1
#define SPEED               2
#define RUNETIME            3

typedef struct spi_slave_message_t {
    uint8_t command;
    uint8_t direction;
    uint8_t speed;
    uint8_t runetime;
}spi_slave_message_t;

typedef struct spi_slave_config_t {
    spi_slave_message_t *spi_slave_message;
    spi_slave_message_t *spi_slave_response;
    pthread_mutex_t *spi_slave_message_lock;
    pthread_mutex_t *spi_slave_response_lock;
}spi_slave_bus_t;

#endif