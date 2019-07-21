#ifndef MPU6050_INTERFACE_H
#define MPU6050_INTERFACE_H

#include "../device/mpu6050_device.h"
#include "../namespace/mpu6050_space.h"

using namespace mpu6050_space;

class MPU6050_Interface {
    public:
        MPU6050_Interface(MPU6050_config_t config);
        ~MPU6050_Interface();
        bool init();
        data_t getData();
    private:
        MPU6050_Device* device;
        int connect;
};

#endif