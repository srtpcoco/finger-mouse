#ifndef MPU6050_SPACE_H
#define MPU6050_SPACE_H
#include "../mathtools/mathtools.hpp"
namespace mpu6050_space {
    enum gyro_range_t{
        GYRO_2000DEG = 0x18,
        GYRO_1000DEG = 0x10,
        GYRO_500DEG = 0x08,
        GYRO_250DEG = 0x01
    };

    enum accel_range_t{
        ACCEL_16G = 0x18,
        ACCEL_8G = 0x10,
        ACCEL_4G = 0x08,
        ACCEL_2G = 0x01
    };

    struct MPU6050_config_t {
        gyro_range_t gyro_range_cfg;
        accel_range_t accel_range_cfg;
    };

    struct data_t {
         vector3D gyro_data;
         vector3D accel_data;
    };
};

#endif