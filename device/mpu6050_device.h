#ifndef MPU6050_DEVICE_H
#define MPU6050_DEVICE_H

#include <cstdint>
#include <cstdio>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../namespace/mpu6050_space.h"

using namespace mpu6050_space;

#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define GYRO_CONFIG_2000DEG  0x18
#define	ACCEL_CONFIG	0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_CONFIG_2G 0x01
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define SlaveAddress     0x68

class MPU6050_Device {
	public:
		MPU6050_Device(MPU6050_config_t mpu_cfg);

		bool init(int& connect);

		data_t getData(int& connect);

	private:
		float gyro_coefficient;
		float accel_coefficient;
		MPU6050_config_t config;

		int16_t getRawData(int& connect, uint8_t reg_address);
};

#endif

