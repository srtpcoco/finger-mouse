#include "mpu6050.h"
#include <cstdio>

using namespace mpu6050_space;

MPU6050::MPU6050() {
   // interface = new MPU6050_Interface( );
}

bool MPU6050::start() {
    if (!interface->init()) return false;
    while (1) {
        getData();
        print();
    }
    return true;
}

void MPU6050::stop() {
    delete interface;
}

void MPU6050::getData() {
    data = interface->getData();
}

void MPU6050::print() const {
    printf("Gyro: (%.2f, %.2f, %.2f)    Accel: (%.2f, %.2f, %.2f)", 
            data.gyro_data.x_, data.gyro_data.y_, data.gyro_data.z_,
            data.accel_data.x_, data.accel_data.y_, data.accel_data.z_);
}

MPU6050::~MPU6050() {
    stop();
    return;
}