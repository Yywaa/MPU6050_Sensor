/*
 * MPU6050.c
 *
 *  Created on: 2024-12-10
 *      Author: yywvi
 */

#include "../../../MPU6050_Read/MPU6050_Dev/Inc/MPU6050.h"

/***************************************************************
 * @fn               - mpu6050_init
 *
 * @brief            - This function initializes mpu6050 sensor
 *
 * @param            - none
 * @param
 *
 * @return           - none
 *
 * @note             - none
 */
void mpu6050_init()
{
    // 1. disable sleep mode£¬could be modified
    mpu6050_write(MPU6050_REG_POWER, 0x00);
    usleep(500);

    // Adjust full scale values for gyro and acc
    mpu6050_write(MPU6050_REG_ACCEL_CONFIG, 0x18);//0x18 could be macro
    usleep(500);
    mpu6050_write(MPU6050_REG_GYRO_CONFIG, 0x18);
    usleep(500);

}

/************************************************************
 * @fn               - mpu6050_write
 *
 * @brief            - This function writes  value to  mpu6050 sensor specific address
 *
 * @param            - address of specific register
 * @param			 - value
 *
 * @return           - -1 or 0
 *
 * @note             - -1 denotes writing failure , 0 denotes success
 */
int mpu6050_write(uint8_t addr, uint8_t data)
{

	int ret;
	char buf[2];
	buf[0]=addr;
	buf[1]=data;
	ret = write(fd,buf,2);
	if (ret <= 0)
	{
	  perror("write failed\n");
	  return -1;
	}
	return 0;

}

/************************************************************
 * @fn               - mpu6050_read
 *
 * @brief            - This function reads  value from  mpu6050 sensor specific address and store it in the buffer
 *
 * @param            - address of specific register
 * @param			 - length of the data
 * @param	         - addree of the buffer
 *
 * @return           - -1 or 0
 *
 * @note             - -1 denotes writing failure , 0 denotes success
 */
int mpu6050_read(uint8_t base_addr, char *pBuffer,uint32_t len)
{
	int ret;
	char buf[2];
	buf[0]=base_addr;
	ret = write(fd,buf,1);
	if (ret <= 0)
	{
	  perror("write address failed\n");
	  return -1;
	}

	ret = read(fd,pBuffer,len);
	if(ret <= 0)
	{
	  perror("read failed\n");
	}
	return 0;

}

/************************************************************
 * @fn               - mpu6050_read_acc
 *
 * @brief            - This function reads  accelerometer values from  mpu6050 sensor specific address and stores them in the buffer
 *
 * @param            - address of buffer
 *
 * @return           -
 *
 * @note             -
 */
void mpu6050_read_acc(short int *pBuffer)
{
	//each axis value is of 2byte, so we need a buffer of 6bytes.
	char acc_buffer[6];

	//start reading from the base address of accelerometer values i.e MPU6050_REG_ACC_X_HIGH
	mpu6050_read(MPU6050_REG_ACC_X_HIGH,acc_buffer,6);

	/* pBuffer[0]= acc x axis value , pBuffer[1]= acc y axis value , pBuffer[2]= acc z axis value  */
	pBuffer[0] = (int) ( (acc_buffer[0] << 8) |  acc_buffer[1] );
	pBuffer[1] = (int) ( (acc_buffer[2] << 8) |  acc_buffer[3] );
	pBuffer[2] = (int) ( (acc_buffer[4] << 8) |  acc_buffer[5] );


}

/************************************************************
 * @fn               - mpu6050_read_gyro
 *
 * @brief            - This function reads  gyro values from  mpu6050 sensor specific address and stores them in the buffer
 *
 * @param            - address of buffer
 *
 * @return           -
 *
 * @note             -
 */
void mpu6050_read_gyro(short *pBuffer)
{
	char gyro_buffer[6];

	//start reading from the base address of gyro values i.e MPU6050_REG_GYRO_X_HIGH
	mpu6050_read(MPU6050_REG_GYRO_X_HIGH,gyro_buffer,6);

	pBuffer[0] =  ( (gyro_buffer[0] << 8) +  gyro_buffer[1] );
	pBuffer[1] =  ( (gyro_buffer[2] << 8) +  gyro_buffer[3] );
	pBuffer[2] =  ( (gyro_buffer[4] << 8) +  gyro_buffer[5] );

}


/************************************************************
 * @fn               - mpu6050_read_temp
 *
 * @brief            - This function reads  temperature values from  mpu6050 sensor specific address and stores them in the buffer
 *
 * @param            - address of buffer
 *
 * @return           -
 *
 * @note             -
 */
void mpu6050_read_temp(short *pBuffer)
{
	char temp_buffer[2];

	//start reading from the base address of gyro values i.e MPU6050_REG_GYRO_X_HIGH
	mpu6050_read(MPU6050_REG_TEMP_HIGH,temp_buffer,2);

	pBuffer[0] =  ( (temp_buffer[0] << 8) +  temp_buffer[1] );

}
