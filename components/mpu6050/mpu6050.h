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
// #include <bcm2835.h>

#define I2C_DEVICE          "/dev/i2c-1"
#define I2C_SPEED           100000

#define set_I2C_pins  true

/**
 * @brief PCA9685 Regsiters
 * 
 */
#define DEV_ADR                         0x68
#define ACC_ADR                         0x3B
#define GYRO_ADR                        0x43
#define TEMP_ADR                        0x41
#define MPU6050_WRITE_ADDR 	            0xD0    // 8-Bit Write address //
#define MPU6050_READ_ADDR 	            0xD1  

// Power Management 1 Register
#define PWR_MGT_1                       0x6B
#define MPU6050_PWR1_DEVICE_RESET_BIT   7
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CYCLE_BIT          5
#define MPU6050_PWR1_TEMP_DIS_BIT       3
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03
#define MPU6050_CLOCK_PLL_EXT32K        0x04
#define MPU6050_CLOCK_PLL_EXT19M        0x05
#define MPU6050_CLOCK_KEEP_RESET        0x07

// Gyroscope Configuration
#define MPU6050_RA_GYRO_CONFIG          0x1B
#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2
#define MPU6050_GYRO_FS_250             0x00
#define MPU6050_GYRO_FS_500             0x01
#define MPU6050_GYRO_FS_1000            0x02
#define MPU6050_GYRO_FS_2000            0x03

// Accelerometer Configurations
#define MPU6050_RA_ACCEL_CONFIG         0x1C
#define MPU6050_ACONFIG_XA_ST_BIT           7
#define MPU6050_ACONFIG_YA_ST_BIT           6
#define MPU6050_ACONFIG_ZA_ST_BIT           5
#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU6050_ACCEL_FS_2              0x00
#define MPU6050_ACCEL_FS_4              0x01
#define MPU6050_ACCEL_FS_8              0x02
#define MPU6050_ACCEL_FS_16             0x03

// Device Id i.e WHO_AM_I 
#define MPU6050_RA_WHO_AM_I             0x75
#define MPU6050_WHO_AM_I_BIT            1
#define MPU6050_WHO_AM_I_LENGTH         6
#define DEFAULT_ID                      0x68

// 
#define MPU6050_RA_ACCEL_XOUT_H         0x3B

#define ACCEL_CONFIG                    0x1C
#define MPU6050_RANGE_2_G_SCALE         16384
#define MPU6050_RANGE_2000_DEG_SCALE    16.4

typedef struct {
    float accel[3];
    float gyro[3];
    float temp;
} imu_type;

typedef struct {
    uint8_t pwr_mgt_1;
    uint8_t gyro_config;
    uint8_t accel_config;
    uint8_t device_id;
} mpu6050_config_t;



int MPU6050(void);
void ReadIMU(imu_type *imu_data);
void PrintImuData(imu_type *imu_data);
void MPU6050_Run(imu_type *imu_data);

#endif