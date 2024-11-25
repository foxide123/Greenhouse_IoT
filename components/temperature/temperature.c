#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "temperature.h"
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>

//SCL - clock line. Used to synchronize data transfers
//SDA - data line. 
// master - the device that drives the SCL clock line. 
// slave - device that responds to the master
// slave never initiates a transfer

// start and stop sequences mark the beginning and end of a transaction with the slave device

// For every 8 bits transferred, the device receiving the data sends back an acknowledge bit
// If the receiving device sends back a low ACK bit, then it has received the data
//      and is ready to accept another byte.
//      Otherwise it cannot accept and master should send stop sequence


// READ:
// Before reading data from the salve device, you must tell it which of its
// internal addresses you want to read. 



int open_bus()
{
    int file;
    char *filename = BBB_I2C_2;
    if ((file = open(filename, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        exit(1);
    }

    return file;
}

void initiate_communication(int file)
{
    //addr - 0x27
    int addr = 0b00011011;
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave. %s\n", strerror(errno));
        exit(1);
    }
}

//obtain data from I2C peripheral. 
char* get_temp_readings(int file)
{
    uint8_t input[4] = {0};
    float data;
    if(read(file, input, 4) != 4) {
        printf("Failed to read from the i2c bus.\n");
        printf("\n\n");
    }

    // isolate first 2 bits which are status bits
    // if input[0] = 1011 0110 then 1011 0110 & 1100 0000 -> 1000 0000. After shifting: 00000010
    uint32_t status = input[0] & 0b11000000 >> 6;
    // masking lower 6 bits of input[0] ignoring 2bits for status
    // (if input[0] = 1011 0110): 1011 0110 & 0011 1111 = 0011 0110. Shifted to the left by 8: 0011 0110 0000 0000
    // (if input[1] = 0010 1010): 0011 0110 0000 0000 | 0000 0000 0010 1010 -> 0011 0110 0010 1010
    uint32_t humidity = ((input[0] & 0b00111111) << 8) | input[1];
    // (if input[2] = 1110 0011): 1110 0011 << 6 -> 0011 1000 1100 0000
    // (if input[3] = 0011 0101): 0011 1000 1100 0000 | 0000 0000 0011 0100 -> 0011 100 1111 0100
    uint32_t temperature = (input[2] << 6) | (input[3] & 0b11111100);

    printf("%.1f,", roundf((humidity / (float) 16382 * 100) * 2.0f) / 2.0f);
    printf("%.1f\n", roundf(((temperature / (float) 16382) * 165 - 40) * 2.0f) / 2.0f);

    // Create JSON
    char* json_data = malloc(256);
    snprintf(json_data, 256, "{\"temperature\": %.2f, \"humidity\": %.2f}", temperature, humidity);

    return json_data;
}

void temp_init(void)
{
    int file = open_bus();
    initiate_communication(file);
    read_from_sensor(file);
}