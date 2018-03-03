#ifndef _IMU2_H_
#define _IMU2_H_

#include "I2Cdev.h"
#include "imu_config.h"

#include <Wire.h>
#include "geometry_msgs/Vector3.h"

bool initIMU()
{
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    accelerometer.initialize();
    gyroscope.initialize();
    magnetometer.initialize();

    return true;
}

geometry_msgs::Vector3 readAccelerometer()
{
    geometry_msgs::Vector3 accel;
    int16_t ax, ay, az;
    
    accelerometer.getAcceleration(&ax, &ay, &az);

    accel.x = ax * ACCEL_SCALE * G_TO_ACCEL;
    accel.y = ay * ACCEL_SCALE * G_TO_ACCEL;
    accel.z = az * ACCEL_SCALE * G_TO_ACCEL;

    return accel;
}

geometry_msgs::Vector3 readGyroscope()
{
    geometry_msgs::Vector3 gyro;
    int16_t gx, gy, gz;

    gyroscope.getRotation(&gx, &gy, &gz);

    gyro.x = gx * GYRO_SCALE * DEG_TO_RAD;
    gyro.y = gy * GYRO_SCALE * DEG_TO_RAD;
    gyro.z = gz * GYRO_SCALE * DEG_TO_RAD;

    return gyro;
}

geometry_msgs::Vector3 readMagnetometer()
{
    geometry_msgs::Vector3 mag;
    int16_t mx, my, mz;

    magnetometer.getHeading(&mx, &my, &mz);

    mag.x = mx;
    mag.y = my;
    mag.z = mz;

    return mag;
}

#endif