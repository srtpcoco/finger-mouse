#include "mpu6050_device.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>

using namespace mpu6050_space;

MPU6050_Device::MPU6050_Device( mpu6050_space::MPU6050_config_t mpu_cfg) {
    config = mpu_cfg;
    switch (config.gyro_range_cfg) {
        case GYRO_2000DEG:
            gyro_coefficient = 16.4;
            break;
        case GYRO_1000DEG:
            gyro_coefficient = 32.8;
            break;
        case GYRO_500DEG:
            gyro_coefficient = 65.5;
            break;
        default:
            gyro_coefficient = 131;
            break;
    }
    switch (config.accel_range_cfg) {
        case ACCEL_16G:
            accel_coefficient = 2048;
            break;
        case ACCEL_8G:
            accel_coefficient = 4096;
            break;
        case ACCEL_4G:
            accel_coefficient = 8192;
            break;
        default:
            accel_coefficient = 16384;
            break;
    }
}

bool MPU6050_Device::init(int& connect) {
    wiringPiSetup();
    if (connect=wiringPiI2CSetup(SlaveAddress) < 0) {
        printf("Connect failed!");
        return false;
    }
    wiringPiI2CWriteReg8(connect, PWR_MGMT_1, 0x00);
	wiringPiI2CWriteReg8(connect, SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8(connect, CONFIG, 0x06);
	wiringPiI2CWriteReg8(connect, GYRO_CONFIG, config.gyro_range_cfg);
	wiringPiI2CWriteReg8(connect, ACCEL_CONFIG, config.accel_range_cfg);
    return true;
}

int16_t MPU6050_Device::getRawData(int& connect, uint8_t reg_address) {
    return wiringPiI2CReadReg8(connect, reg_address) << 8 + 
	       wiringPiI2CReadReg8(connect, reg_address + 1 );
}

mpu6050_space::data_t MPU6050_Device::getData(int& connect) {
    vector3D g (
        1.0f * getRawData(connect, GYRO_XOUT_H) / gyro_coefficient,
        1.0f * getRawData(connect, GYRO_YOUT_H) / gyro_coefficient,
        1.0f * getRawData(connect, GYRO_ZOUT_H) / gyro_coefficient) ;
    vector3D a (
        1.0f * getRawData(connect, ACCEL_XOUT_H) / accel_coefficient,
        1.0f * getRawData(connect, ACCEL_YOUT_H) / accel_coefficient,
        1.0f * getRawData(connect, ACCEL_ZOUT_H) / accel_coefficient) ;
    return {g, a};
}

