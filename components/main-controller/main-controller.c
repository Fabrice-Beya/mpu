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

#include "main-controller.h"
#include "utils.h"

spi_slave_config_t *mc_spi_slave_config;

static void init_spi_message(void) {
  mc_spi_slave_config->spi_slave_message->command = IDLE;
  mc_spi_slave_config->spi_slave_message->direction = FORWARD;
  mc_spi_slave_config->spi_slave_message->speed = 0;
  mc_spi_slave_config->spi_slave_message->runetime = 0;
}

static void init_spi_config(spi_slave_config_t *_spi_slave_config) {
  mc_spi_slave_config = _spi_slave_config;
  init_spi_message();
  pthread_mutex_lock(&(*(mc_spi_slave_config)->spi_slave_message_lock));
  pthread_mutex_lock(&(*(mc_spi_slave_config)->spi_slave_response_lock));
}

int MainController(spi_slave_config_t *_spi_slave_config) {
  init_spi_config(_spi_slave_config);
  return 0;
}

static void print_spi_slave_message(const spi_slave_message_t *message) {
  printf("\n");
  printf("COMMAND: %d\n", message->command);
  printf("DIRECTION: %d\n", message->direction);
  printf("SPEED: %d\n", message->speed);
  printf("RUNETIME: %d\n", message->runetime);
  printf("\n");
}

static int process_slave_response(void) {
  print_spi_slave_message(&(*(mc_spi_slave_config)->spi_slave_message));
  return 0;
}

static void read_response(void) {
  while (pthread_mutex_lock(&(*(mc_spi_slave_config)->spi_slave_response_lock)) != 0)
  {
    printf("\n Waiting for spi slave response lock\n");
  }

  if(process_slave_response() == 0) {
    pthread_mutex_unlock(&(*(mc_spi_slave_config)->spi_slave_response_lock));
  }
}

static void send_command(uint8_t command, uint8_t direction, uint8_t speed, uint8_t runetime) {
  printf("Sending command: ");

  while (pthread_mutex_lock(&(*(mc_spi_slave_config)->spi_slave_message_lock)) != 0)
  {
    printf("\n Waiting for spi slave message lock\n");
  }

  mc_spi_slave_config->spi_slave_message->command = command;
  mc_spi_slave_config->spi_slave_message->direction = direction;
  mc_spi_slave_config->spi_slave_message->speed = speed;
  mc_spi_slave_config->spi_slave_message->runetime = runetime;

  pthread_mutex_unlock(&(*(mc_spi_slave_config)->spi_slave_message_lock));
  print_spi_slave_message(&(*(mc_spi_slave_config)->spi_slave_message));
}

void MainController_Run(void) {

  uint8_t spd;

  while(1) {
    printf("Enter movement speed command:");
    scanf("%d", &spd);
    send_command(MOVE, FORWARD, spd, 2);
    read_response();
  }
}