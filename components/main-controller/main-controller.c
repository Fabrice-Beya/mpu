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
  int ret = -1;
  init_spi_config(spi_slave_bus_t);
  ret = SlaveSpi();
  if (ret) {
    printf("Failed to initialize Slave SPI\n");
    pthread_exit(NULL);
  } 

  return ret;
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
  print_spi_slave_message(mc_spi_slave_bus->spi_slave_response);
  return 0;
}

static int read_response(void) {
  int ret = -1;
  printf("Reading response: ");
  
  pthread_mutex_trylock(mc_spi_slave_bus->spi_slave_response_lock);

  ret = ReadSpiResponse(mc_spi_slave_bus->spi_slave_response);
  if(ret < 0) {
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

  pthread_mutex_lock(mc_spi_slave_bus->spi_slave_message_lock);

  spi_slave_message_t spi_slave_message;

  spi_slave_message.command = command;
  spi_slave_message.direction = direction;
  spi_slave_message.speed = speed;
  spi_slave_message.runetime = runetime;

  ret = SendSpiMessage(&spi_slave_message);
  if(ret < 0) {
    printf("\n Failed to send spi message.\n");
  }

  pthread_mutex_unlock(mc_spi_slave_bus->spi_slave_message_lock);
  print_spi_slave_message(&spi_slave_message);

  return ret;
}

static void cli_interface(void) {
  int direction, speed, runetime;

  printf("\nEnter direction code command: 1-Forward 2-Backward 3-Foward-Left 4-Forward-Right 5-Backward-Left 6-Backward_right: ");
  scanf("%u", &direction);
  printf("\nEnter speed in range of: 0 - 100: ");
  scanf("%u", &speed);
  printf("\nEnter rune time in seconds: ");
  scanf("%u", &runetime);

  printf("values read: direction - %u speed - %u runetime %u", direction, speed, runetime);

  send_command(MOVE, (uint8_t)direction, (uint8_t)speed, (uint8_t)runetime);
  sleep(0.5);
  read_response();

}

void MainController_Run(void) {
  while(1) {
    cli_interface();
  }
}