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

int MainController(void) {
  return 0;
}

static void set_message(uint8_t command, uint8_t direction, uint8_t speed, uint8_t duration) {
  // message[COMMAND] = command;
  // message[DIRECTION] = direction;
  // message[SPEED] = speed;
  // message[DURATION] = duration;
}

static void read_response(void) {
  // printf("Reading response: ");
  // set_message(IDLE, response[DIRECTION], response[SPEED], response[DURATION]);
  // SpiWriteAndRead();
  // printBuffer(response);
}

static void send_command(uint8_t command, uint8_t direction, uint8_t speed, uint8_t duration) {
  // printf("Sending command: ");
  // set_message(command, direction, speed, duration);
  // printBuffer(message);
  // SpiWriteAndRead();
}

void MainController_Run(void) {

  uint8_t spd;

  while(1) {
    printf("Enter movement speed command:");
    scanf("%d", &spd);
    // send_command(MOVE, FORWARD, spd, 2);
    // read_response();

  }
}