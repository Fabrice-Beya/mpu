/*****************************************************************************
* | File      	:   slave-spi.c
* | Author      :   Fabrice Beya
* | Function    :   Driver to communicate with slave mcu's over spi
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-01
* | Info        :   
#
# Summary
******************************************************************************/

#include "slave-spi.h"

uint8_t response[BUF_LEN];
uint8_t message[BUF_LEN];

struct spi_ioc_transfer t;
int spi_device;				//file descriptor for the SPI0 device

static void init_buffers(void) {
    t.tx_buf = (unsigned long)message;		
    t.rx_buf = (unsigned long)response;		
    t.len = BUF_LEN;
    t.delay_usecs = 0;
    t.speed_hz = SPI_SPEED;
    t.bits_per_word = BITS_PER_WORD;
    t.cs_change = 1;   
}

static void printBuffer(const uint8_t *buf) {
  printf("\n");
  printf("COMMAND: %d\n", buf[COMMAND]);
  printf("DIRECTION: %d\n", buf[DIRECTION]);
  printf("SPEED: %d\n", buf[SPEED]);
  printf("RUNETIME: %d\n", buf[RUNETIME]);
  printf("\n");
}

int spi_open_port (void)
{
	int status_value = -1;
  uint32_t temp;

  spi_device = open(SPI_DEVICE, O_RDWR);
  if (spi_device < 0)
  {
      perror("Error - Could not open SPI device");
      exit(1);
  }

  status_value = ioctl(spi_device, SPI_IOC_RD_MODE32, &temp);
    if(status_value != 0) {
        printf("Could not read SPI mode...\r\n");
        close(spi_device);
        exit(EXIT_FAILURE);
    }

    temp |= SPI_MODE_3;

    status_value = ioctl(spi_device, SPI_IOC_WR_MODE32, &temp);
    if(status_value != 0) {
        printf("Could not write SPI mode...\r\n");
        close(spi_device);
        exit(EXIT_FAILURE);
    }

   status_value = ioctl(spi_device, SPI_IOC_RD_MAX_SPEED_HZ, &temp);
    if(status_value != 0) {
        printf("Could not read the SPI max speed...\r\n");
        close(spi_device);
        exit(EXIT_FAILURE);
    }

    temp = SPI_SPEED;

    status_value = ioctl(spi_device, SPI_IOC_WR_MAX_SPEED_HZ, &temp);
    if(status_value != 0) {
        printf("Could not write the SPI max speed...\r\n");
        close(spi_device);
        exit(EXIT_FAILURE);
    }

  return(status_value);
}

static int spi_close_port (void)
{
	int status_value = -1;
  
  status_value = close(spi_device);
  if(status_value < 0)
  {
    perror("Error - Could not close SPI device\n");
    exit(1);
  }
  return(status_value);
}

static int spi_write_read(void)
{
	int retVal = -1;

	t.tx_buf = (unsigned long)message;		
	t.rx_buf = (unsigned long)response;		

	retVal = ioctl(spi_device, SPI_IOC_MESSAGE(1), &t);

	if(retVal < 0)
	{
		perror("Error - Problem transmitting spi data..ioctl");
		exit(1);
	}

	return retVal;
}

int SlaveSpi(void) {
  int ret = -1;
  init_buffers();
  ret = spi_open_port();

  return ret;
}

static void set_message(uint8_t command, uint8_t direction, uint8_t speed, uint8_t runetime) {
  message[COMMAND] = command;
  message[DIRECTION] = direction;
  message[SPEED] = speed;
  message[RUNETIME] = runetime;
}

int ReadSpiResponse(spi_slave_message_t *spi_slave_response) {
  int ret = -1;
  printf("Reading spi response: ");
  set_message(IDLE, 0, 0, 0);
  ret = spi_write_read();

  spi_slave_response->command = response[COMMAND];
  spi_slave_response->direction = response[DIRECTION];
  spi_slave_response->speed = response[SPEED];
  spi_slave_response->runetime = response[RUNETIME];

  // printBuffer(response);


  return ret;
}

int SendSpiMessage(spi_slave_message_t *spi_slave_message) {
  int ret = -1;

  printf("Sending spi command: ");
  set_message(spi_slave_message->command, 
              spi_slave_message->direction, 
              spi_slave_message->speed, 
              spi_slave_message->runetime);
  // printBuffer(message);

  ret = spi_write_read();

  return ret;
}

void SlaveSpi_Run(void) {
  while(1) {
    // send_command();
    // read_response();
  }
}