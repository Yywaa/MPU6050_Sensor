/*
 * MPU6050_Read.c
 *
 *  Created on: 2024-12-9
 *      Author: Yongwei Yuan
 */

#include "MPU6050.h"

int main()
{
	short acc_value[3],gyro_value[3], temp[1];
	double accx,accy,accz,gyrox,gyroy,gyroz,Temp;

	 /*first lets open the I2C device file */
	if ((fd = open(I2C_DEVICE_FILE,O_RDWR)) < 0) {
		perror("Failed to open I2C device file.\n");
		return -1;
	}

	/*set the I2C slave address using ioctl I2C_SLAVE command */
	if (ioctl(fd,I2C_SLAVE,MPU6050_SLAVE_ADDR) < 0) {
			perror("Failed to set I2C slave address.\n");
			close(fd);
			return -1;
	}

	mpu6050_init();


	while(1)
	{
		mpu6050_read_acc(acc_value);
		mpu6050_read_gyro(gyro_value);
		mpu6050_read_temp(temp);

		/*Convert acc raw values in to 'g' values*/
		accx = (double) acc_value[0]/ACC_FS_SENSITIVITY_3;
		accy = (double) acc_value[1]/ACC_FS_SENSITIVITY_3;
		accz = (double) acc_value[2]/ACC_FS_SENSITIVITY_3;

		/* Convert gyro raw values in to  "бу/s" (deg/seconds) */
		gyrox = (double) gyro_value[0]/GYR_FS_SENSITIVITY_3;
		gyroy = (double) gyro_value[1]/GYR_FS_SENSITIVITY_3;
		gyroz = (double) gyro_value[2]/GYR_FS_SENSITIVITY_3;

		/*Convert temp raw value to values in degrees */
		Temp = (temp[0])/340+36.53;

	#if PRINT_RAW_DATA
		/* print just the raw values read */
	   printf("Acc(raw)=> X:%d Y:%d Z:%d gyro(raw)=> X:%d Y:%d Z:%d; Temp(raw): %d \n",
				   acc_value[0],acc_value[1],acc_value[2],gyro_value[0],gyro_value[1],gyro_value[2],temp[0]);

	   /* print the 'g' and 'бу/s' values */
	   printf("Acc(g)=> X:%.2f Y:%.2f Z:%.2f gyro(dps)=> X:%.2f Y:%.2f Z:%.2f, Temp: %.2f \n",
			   accx,accy,accz,gyrox,gyroy,gyroz,Temp);
	#endif

	#if NON_RAW_DATA
	   printf("%0.2f	%0.2f	%0.2f,  %0.2f\n",accx,accy,accz,Temp);
	#endif

	  /*wait for 250000 micro seconds, thats 250ms before going for another round */
	   usleep(50 * 1000);
	}

}
