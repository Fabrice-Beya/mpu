
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

static int i2c_init(void);
static int get_bus(void);
static void reset(void);
static void set_sleep_config(uint8_t enable);
static void set_clock_source(uint8_t source);
static void set_gyro_range(uint8_t range);
static void set_accel_range(uint8_t range);
static int test_connnection(void);
static void get_raw_motion(void);
static uint8_t read_register(uint8_t reg, uint8_t *data);
static uint8_t write_register(uint8_t reg, uint8_t *data);
static uint8_t read_bytes(uint8_t reg, uint8_t *buffer, int length);
static uint8_t set_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t data);
static void read_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t *data);
static void print_imu_data(imu_type *imu_data);

int i2c_device;
uint8_t motion_buffer[16];
mpu6050_config_t mpu6050_config;
imu_type raw_data;

/*
* Initialise MPU6050 component
*/
int MPU6050(void) {
    printf("Initializing mpu6050....\n");

    i2c_init();
    reset();
    set_sleep_config(false);
    set_clock_source(MPU6050_CLOCK_PLL_XGYRO);
    set_gyro_range(MPU6050_GYRO_FS_250);
    set_accel_range(MPU6050_ACCEL_FS_2);    
    test_connnection();
    get_raw_motion();

    return 0;
}

/*
* MPU6050 main loop
*/
void MPU6050_Run(imu_type *imu_data) {
    while(1) {
        print_imu_data(imu_data);
        sleep(1);       
    }
}

/*
* Initialise linux i2c instance
*/
static int i2c_init(void) {

    int ret = -1;
    i2c_device = open(I2C_DEVICE, O_RDWR);

	if (i2c_device < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return -1;
	}
	
    get_bus();

    return 0;
}

/*
* Get access to i2c buss
*/
static int get_bus(void) {
    int ret = -1;
     ret = ioctl(i2c_device, I2C_SLAVE, DEV_ADR) < 0;
	if (ret < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		exit(1);
        return ret;
	}

    return ret;
}

/*
* Set bit 7 of Power Management 1 register
*/
static void reset(void) {
    uint8_t temp;
    read_register(PWR_MGT_1, &temp);
    mpu6050_config.pwr_mgt_1 = temp | (1 << MPU6050_PWR1_DEVICE_RESET_BIT);
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1); 
}

/*
* Set sleep enable/disabled
*/
static void set_sleep_config(uint8_t enable) {
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    
    if (enable) {
        mpu6050_config.pwr_mgt_1 |= (1 << MPU6050_PWR1_SLEEP_BIT);
    } else {
        mpu6050_config.pwr_mgt_1 &= ~(1 << MPU6050_PWR1_SLEEP_BIT);
    }
   
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
}

/*
* Set clock source
*/
static void set_clock_source(uint8_t source) {
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    mpu6050_config.pwr_mgt_1 = set_bits(mpu6050_config.pwr_mgt_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
    write_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
    sleep(0.1);
    read_register(PWR_MGT_1, &mpu6050_config.pwr_mgt_1);
}

/*
* Set gyro range
*/
static void set_gyro_range(uint8_t range) {
    read_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.gyro_config);
    mpu6050_config.gyro_config = set_bits(mpu6050_config.gyro_config, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
    write_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.gyro_config);
    sleep(0.1);
    read_register(MPU6050_RA_GYRO_CONFIG, &mpu6050_config.gyro_config);
}

/*
* Set accelerometer range
*/
static void set_accel_range(uint8_t range) {
    uint8_t temp;
    read_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
    mpu6050_config.accel_config = set_bits(mpu6050_config.accel_config, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
    write_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
    sleep(0.1);
    read_register(MPU6050_RA_ACCEL_CONFIG, &mpu6050_config.accel_config);
}

/*
* Get device id
*/
static uint8_t get_device_id(void) {
    read_register(MPU6050_RA_WHO_AM_I, &mpu6050_config.device_id);
    // read_bits(device_id, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &device_id);
    return mpu6050_config.device_id;
}

/*
* Test connection by geting device id
*/
int test_connnection(void) {
    uint8_t temp = get_device_id();

    if (temp == DEFAULT_ID) {
        return true;
    }

    return false;
}

/*
* Get raw motion data
*/
static void get_raw_motion(void) {
    read_bytes(MPU6050_RA_ACCEL_XOUT_H, motion_buffer, 14);
   
    raw_data.accel[0] = (((int16_t)motion_buffer[0]) << 8) | motion_buffer[1];
    raw_data.accel[1] = (((int16_t)motion_buffer[2]) << 8) | motion_buffer[3];
    raw_data.accel[2] = (((int16_t)motion_buffer[4]) << 8) | motion_buffer[5];
    raw_data.gyro[0] = (((int16_t)motion_buffer[8]) << 8) | motion_buffer[9];
    raw_data.gyro[1] = (((int16_t)motion_buffer[10]) << 8) | motion_buffer[11];
    raw_data.gyro[2] = (((int16_t)motion_buffer[12]) << 8) | motion_buffer[13];
}

/*
* print imu data
*/
static void print_imu_data(imu_type *imu_data) {
    printf("Acceleration data is: x: %f, y:%f, z:%f\n", imu_data->accel[0], imu_data->accel[1], imu_data->accel[2]);
    printf("Gyro data is: x: %f, y:%f, z:%f\n", imu_data->gyro[0], imu_data->gyro[1], imu_data->gyro[2]);
    printf("Temperature data is: %f\n", imu_data->temp);
}

/*
* Read mpu6050 register
*/
uint8_t read_register(uint8_t reg, uint8_t *data) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = read(i2c_device, data, 1);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 1)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Write to mpu6050 register
*/
uint8_t write_register(uint8_t reg, uint8_t *data) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = write(i2c_device, data, 1);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != 2)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write from the i2c bus.\n");
        return -1;
	}

	return ret;
}

/*
* Read multiple bytes from mpu6050 registers
*/
uint8_t read_bytes(uint8_t reg, uint8_t *buffer, int length) {
    int ret = -1;

    ret = write(i2c_device, &reg, 1);
    ret = read(i2c_device, buffer, length);

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    if (ret != length)		
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

	return *buffer;
}

/*
* Set specific register bits
*/
static uint8_t set_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t data) {
    uint8_t mask = ((1 << bits_length) - 1) << (start_bit - bits_length + 1);
    data <<= (start_bit - bits_length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    reg &= ~(mask); // zero all important bits in existing byte
    reg |= data; // combine data with existing byte

    return reg;
}

/*
* Read specific register bits
*/
static void read_bits(uint8_t reg, uint8_t start_bit, uint8_t bits_length, uint8_t *data) {
    uint8_t mask = ((1 << bits_length) - 1) << (start_bit - bits_length + 1);
    reg &= mask;
    reg >>= (start_bit - bits_length + 1);
    *data = reg;
}

