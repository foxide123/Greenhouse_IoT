#ifndef TEMP_H
#define TEMP_H

#define SCL 
#define SDA 
//logical state of SCL and SDA
#define SCL_IN 
#define SDA_IN

#define BBB_I2C_0 "/dev/i2c-0"
#define BBB_I2C_1 "/dev/i2c-1"
#define BBB_I2C_2 "/dev/i2c-2"

int open_bus();
void initiate_communication();
void get_temp_readings(int file, float *temp, float *humidity);
void temp_init(float *temperature, float *humidity);

#endif