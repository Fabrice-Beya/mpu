/*****************************************************************************
* | File      	:   MPU6050.h
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

#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>

#define I2C_DEVICE          "/dev/i2c-1"
#define I2C_SPEED           100000

/**
 * @brief PCA9685 Regsiters
 * 
 */
#define DEV_ADR                         0x68
#define ACC_ADR                         0x3B
#define GYRO_ADR                        0x43
#define TEMP_ADR                        0x41
#define RST_ADR                         0x6B
#define WHO_AM_I                        0x75
#define DEFAULT_ID                      0x68

#define ACCEL_CONFIG                    0x1C
#define MPU6050_RANGE_2_G_SCALE         16384
#define MPU6050_RANGE_2000_DEG_SCALE    16.4

typedef struct {
    float accel[3];
    float gyro[3];
    float temp;
} imu_type;

int MPU6050(void);
void ReadIMU(imu_type *imu_data);
void PrintImuData(imu_type *imu_data);
void MPU6050_Run(imu_type *imu_data);

#endif