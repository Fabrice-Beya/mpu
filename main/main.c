#include "main.h"

void *Thread_Main_Controller(void *vargp) {
  long tid;
  tid = (long)vargp;
  int ret = -1;

  ret = MainController();
  if (ret) {
    printf("Failed to initialize main controller.");
    pthread_exit(NULL);
  }

  printf("Main Controller task is running with id: %ld", tid);

  MainController_Run();

  pthread_exit(NULL);
}

void *Thread_MPU6050(void *vargp) {
  long tid;
  tid = (long)vargp;

  imu_type imu_data;
  int ret = -1;

  ret = MPU6050();
  if (ret) {
    printf("Failed to initialize MPU6050\n");
    pthread_exit(NULL);
  } 

  printf("MPU6050 task is running with id: %ld", tid);
  
  MPU6050_Run(&imu_data);

  pthread_exit(NULL);
}

void *Thread_SLAVE_SPI(void *vargp) {
  long tid;
  tid = (long)vargp;
  int ret = -1;

  ret = SlaveSpi();
  if (ret) {
    printf("Failed to initialize Slave SPI\n");
    pthread_exit(NULL);
  } 

  printf("Slave spi task is running with id: %ld", tid);

  SlaveSpi_Run();

  pthread_exit(NULL);
}

void create_threads(void) {
  pthread_t vThread_MPU6050, vThread_SLAVE_SPI, vMain_Controller;

  int ret = -1;

  ret = pthread_create(&vMain_Controller, NULL, Thread_Main_Controller, &vMain_Controller); 

  if (ret) {
    printf("Error - Unable to create main conroller thread");
  }

  ret = pthread_create(&vThread_MPU6050, NULL, Thread_MPU6050, &vThread_MPU6050); 

  if (ret) {
    printf("Error - Unable to create mpu6050 thread");
  }

  ret = pthread_create(&vThread_SLAVE_SPI, NULL, Thread_SLAVE_SPI, &vThread_SLAVE_SPI); 

  if (ret) {
    printf("Error - Unable to create slave spi thread");
  } 

  pthread_join(vMain_Controller, NULL);
  pthread_join(vThread_MPU6050, NULL);
  pthread_join(vThread_SLAVE_SPI, NULL);
}

int main(void) {
  create_threads();

  exit(EXIT_SUCCESS);
  return 0;
  
}