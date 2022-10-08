
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

int i2c_device;
uint8_t accel_config;

static int i2c_init(void) {

    int ret = -1;
    i2c_device = open(I2C_DEVICE, O_RDWR);

	if (i2c_device < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return -1;
	}
	
    ret = ioctl(i2c_device, I2C_SLAVE, DEV_ADR) < 0;
	if (ret < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		exit(1);
        return ret;
	}

    return 0;
}

int read_data(uint8_t *buffer, int length) {
    int ret = -1;
    ret = read(i2c_device, buffer, length);
	if (ret != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return 0;
}

int write_data(uint8_t *buffer, int length) {
    int ret = -1;
   
    ret = write(i2c_device, buffer, length);
	if (ret != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
        return ret;
	}

    return 0;
}

void reset(void) {
    uint8_t buf[] = {RST_ADR, 0x00};
    write_data(buf, 2);
}

int test_connnection(void)
{
    uint8_t buffer[1];
    uint8_t reg = WHO_AM_I;
    write_data(&reg, 1); 
    read_data(buffer, 1);

    if (buffer[0] == DEFAULT_ID) {
        printf("MPU6050 connection is good with device ID: %d\n", buffer[0]);
        return 0;
    }

    printf("Bad connection...");
    exit(1);

    return -1;
}

u_int8_t read_accel_range(void) {
    uint8_t buffer[1];
    uint8_t reg = ACCEL_CONFIG;
    write_data(&reg, 1); 
    read_data(buffer, 1);
    uint8_t val;

    val = buffer[0];
    accel_config = val;

    return buffer[0];

}

void read_acc(imu_type *imu_data) {
    uint8_t buffer[6];
    uint8_t reg = ACC_ADR;

    write_data(&reg, 1); 
    read_data(buffer, 6);

    for (int i = 0; i < 3; i++) {
        int16_t raw_val = (int16_t)(buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
        if (accel_config == 0) {
            imu_data->accel[i] = (float)(raw_val / MPU6050_RANGE_2_G_SCALE);
        }
        
    }
}

void read_gyro(imu_type *imu_data) {
    uint8_t buffer[6];
    uint8_t reg = GYRO_ADR;

    write_data(&reg, 1); 
    read_data(buffer, 6);

    for (int i = 0; i < 3; i++) {
        int16_t raw_val = (int16_t)(buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
        imu_data->gyro[i] = (float)(raw_val / MPU6050_RANGE_2000_DEG_SCALE);
    }
}

static void read_temp(imu_type *imu_data) {
    uint8_t buffer[2];
    uint8_t reg = TEMP_ADR;

    write_data(&reg, 1); 
    read_data(buffer, 2);

    int16_t raw_temp = buffer[0] << 8 | buffer[1];

    imu_data->temp = (raw_temp/340.0) + 36.53;
}

void PrintImuData(imu_type *imu_data) {
    printf("Acceleration data is: x: %f, y:%f, z:%f\n", imu_data->accel[0], imu_data->accel[1], imu_data->accel[2]);
    printf("Gyro data is: x: %f, y:%f, z:%f\n", imu_data->gyro[0], imu_data->gyro[1], imu_data->gyro[2]);
    printf("Temperature data is: %f\n", imu_data->temp);
}

void ReadIMU(imu_type *imu_data) {
    read_acc(imu_data);
    read_gyro(imu_data);
    read_temp(imu_data);
}

int MPU6050(void) {
    printf("Initializing mpu60503333....\n");
    i2c_init();
    reset();
    test_connnection();
    read_accel_range();

    return 0;
}

void MPU6050_Run(imu_type *imu_data) {

    while(1) {
        ReadIMU(imu_data);
        PrintImuData(imu_data);
        sleep(1);       
    }
    
}

