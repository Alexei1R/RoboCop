#pragma once
#include <Arduino.h>
#include <Wire.h>

namespace Robot
{

#define MPU6050_ADDR 0x68
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1a
#define MPU6050_GYRO_CONFIG 0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6b
#define MPU6050_TEMP_H 0x41
#define MPU6050_TEMP_L 0x42

    class Gyroscope
    {
    public:
        void Update();
        void Begin();

        float GetAccX() { return m_AngleAccX; };
        float GetAccY() { return m_AngleAccY; };
        float GetAccZ() { return m_AngleAccZ; };

        float GetGyroX() { return m_AngleGyroX; };
        float GetGyroY() { return m_AngleGyroY; };
        float GetGyroZ() { return m_AngleGyroZ; };

        
        float GetPITCH() { return m_AngleY; };
        float GetROLL() { return m_AngleX; };
        float GetYAW() { return m_AngleZ; };

        float GetAngleX() { return m_AngleX; };
        float GetAngleY() { return m_AngleY; };
        float GetAngleZ() { return m_AngleZ; };

        float GetTemperature() { return m_AngleZ; };

    private:
        void writeGyroscope(byte reg, byte data);
        byte readGyroscope(byte reg);

    private:
        int16_t m_RawAccX, m_RawAccY, m_RawAccZ;
        int16_t m_RawGyroX, m_RawGyroY, m_RawGyroZ;
        int16_t m_RawTemperature;

        float m_Temperature;
        float m_AngleAccX, m_AngleAccY, m_AngleAccZ;
        float m_AngleGyroX, m_AngleGyroY, m_AngleGyroZ;

        float m_AngleX, m_AngleY, m_AngleZ;

        float m_Time;
        float m_DeltaTime;

        float GyroCoef  = 0.5;
        float AccCoef  = 1.0 - GyroCoef;
    };
}