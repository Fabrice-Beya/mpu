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

spi_slave_bus_t *mc_spi_slave_bus;

static void lock_spi_bus() {
  pthread_mutex_lock(mc_spi_slave_bus->spi_slave_message_lock);
  pthread_mutex_lock(mc_spi_slave_bus->spi_slave_response_lock);
}

static void unlock_spi_bus(void) {
  pthread_mutex_unlock(mc_spi_slave_bus->spi_slave_message_lock);
  pthread_mutex_unlock(mc_spi_slave_bus->spi_slave_response_lock);
}

static void init_spi_message(void) {
  lock_spi_bus();
  mc_spi_slave_bus->spi_slave_message->command = IDLE;
  mc_spi_slave_bus->spi_slave_message->direction = FORWARD;
  mc_spi_slave_bus->spi_slave_message->speed = 0;
  mc_spi_slave_bus->spi_slave_message->runetime = 0;
  unlock_spi_bus();
}

static void init_spi_config(spi_slave_bus_t *spi_slave_bus_t) {
  mc_spi_slave_bus = spi_slave_bus_t;
  init_spi_message();
  
}

int MainController(spi_slave_bus_t *spi_slave_bus_t) {
  init_spi_config(spi_slave_bus_t);
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
  print_spi_slave_message(mc_spi_slave_bus->spi_slave_message);
  return 0;
}

static int read_response(void) {
  int ret = -1;
  printf("Reading response: ");
  while (pthread_mutex_trylock(mc_spi_slave_bus->spi_slave_response_lock) != 0)
  {
    printf("\n Waiting for spi slave response lock\n");
  }

  ret = ReadSpiResponse(mc_spi_slave_bus->spi_slave_response);
  if(ret) {
    printf("\n Failed to read spi response.\n");
  }

  if(process_slave_response() == 0) {
    pthread_mutex_unlock(mc_spi_slave_bus->spi_slave_response_lock);
  }

  return ret;
}

static int send_command(uint8_t command, uint8_t direction, uint8_t speed, uint8_t runetime) {
  int ret = -1;
  printf("Sending command: ");

  while (pthread_mutex_trylock(mc_spi_slave_bus->spi_slave_message_lock) != 0)
  {
    // printf("\n Waiting for spi slave message lock\n");
  }

  mc_spi_slave_bus->spi_slave_message->command = command;
  mc_spi_slave_bus->spi_slave_message->direction = direction;
  mc_spi_slave_bus->spi_slave_message->speed = speed;
  mc_spi_slave_bus->spi_slave_message->runetime = runetime;

  ret = SendSpiMessage(mc_spi_slave_bus->spi_slave_message);
  if(ret) {
    printf("\n Failed to send spi message.\n");
  }

  pthread_mutex_unlock(mc_spi_slave_bus->spi_slave_message_lock);
  print_spi_slave_message(mc_spi_slave_bus->spi_slave_message);

  return ret;
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