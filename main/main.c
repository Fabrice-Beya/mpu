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
#include <pthread.h>

#include "mpu6050.h"
#include "slave-spi.h"

void *Thread_MPU6050(void *vargp) {
    long tid;
    tid = (long)vargp;

    imu_type imu_data;
    MPU6050Init();

    printf("MPU6050 task is running with id: %ld", tid);
    // MPU6050_Run(&imu_data);

    pthread_exit(NULL);
}

void *Thread_SLAVE_SPI(void *vargp) {
    long tid;
    tid = (long)vargp;

    printf("Slave spi task is running with id: %ld", tid);
    SlaveSpiInit();
    Monitor();

    pthread_exit(NULL);
}

void create_threads(void) {
  pthread_t vThread_MPU6050, vThread_SLAVE_SPI;

  int ret;

  // ret = pthread_create(&vThread_MPU6050, NULL, Thread_MPU6050, &vThread_MPU6050); 

  // if (ret) {
  //   printf("Error - Unable to create mpu6050 thread");
  // }

  ret = pthread_create(&vThread_SLAVE_SPI, NULL, Thread_SLAVE_SPI, &vThread_SLAVE_SPI); 

  if (ret) {
    printf("Error - Unable to create slave spi thread");
  } 

  // pthread_join(vThread_MPU6050, NULL);
  pthread_join(vThread_SLAVE_SPI, NULL);

}

int main(void) {

  create_threads();

  exit(EXIT_SUCCESS);
  return 0;
  
}