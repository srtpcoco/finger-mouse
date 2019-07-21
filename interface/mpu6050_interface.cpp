#include "mpu6050_interface.h"

using namespace mpu6050_space;

MPU6050_Interface::MPU6050_Interface(MPU6050_config_t config) {
    device = new MPU6050_Device(config);
}

MPU6050_Interface::~MPU6050_Interface() {
    delete device;
    return;
}

bool MPU6050_Interface::init() {
    return device->init(connect);
}

data_t MPU6050_Interface::getData() {
    return device->getData(connect);
}