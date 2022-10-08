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
spi_slave_config_t *sl_spi_slave_config;

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

int SlaveSpi(spi_slave_config_t *sl_spi_slave_config) {
  sl_spi_slave_config = sl_spi_slave_config;
  int ret = -1;
  ret = spi_open_port();

  return ret;
}

static void set_message(uint8_t command, uint8_t direction, uint8_t speed, uint8_t runetime) {
  message[COMMAND] = command;
  message[DIRECTION] = direction;
  message[SPEED] = speed;
  message[RUNETIME] = RUNETIME;
}

static void read_response(void) {
  while (pthread_mutex_lock(&(*(sl_spi_slave_config)->spi_slave_response_lock)) != 0) {
    printf("\n Waiting for spi slave response lock\n");
  }

  printf("Reading spi response: ");
  set_message(IDLE, 0, 0, 0);
  spi_write_read();

  sl_spi_slave_config->spi_slave_response->command = response[COMMAND];
  sl_spi_slave_config->spi_slave_response->direction = response[DIRECTION];
  sl_spi_slave_config->spi_slave_response->speed = response[SPEED];
  sl_spi_slave_config->spi_slave_response->runetime = response[RUNETIME];

  pthread_mutex_unlock(&(*(sl_spi_slave_config)->spi_slave_message_lock));

  printBuffer(response);
}

static void send_command(void) {
  while (pthread_mutex_lock(&(*(sl_spi_slave_config)->spi_slave_message_lock)) != 0) {
    printf("\n Waiting for spi slave message lock\n");
  }

  printf("Sending spi command: ");
  set_message(sl_spi_slave_config->spi_slave_message->command, 
              sl_spi_slave_config->spi_slave_message->direction, 
              sl_spi_slave_config->spi_slave_message->speed, 
              sl_spi_slave_config->spi_slave_message->runetime);
  // printBuffer(message);
  spi_write_read();
}

void SlaveSpi_Run(void) {
  while(1) {
    send_command();
    read_response();
  }
}