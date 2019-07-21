#ifndef MPU6050_H
#define MPU6050_H

#include "../interface/mpu6050_interface.h"
#include "../namespace/mpu6050_space.h"

using namespace mpu6050_space;

class MPU6050 {
    public:
        bool start();
        void stop();
        void print() const;
        data_t data;
        MPU6050();
        ~MPU6050();

    private:
        MPU6050_Interface* interface;
        void getData();
};

#endif