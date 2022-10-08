#ifndef MAIN_H
#define MAIN_H

#include "utils.h"
#include "main-controller.h"
#include "mpu6050.h"
#include "slave-spi.h"

spi_slave_message_t spi_slave_message;
spi_slave_message_t spi_slave_response;
pthread_mutex_t spi_slave_message_lock;
pthread_mutex_t spi_slave_response_lock;
spi_slave_bus_t spi_slave_config;

#endif