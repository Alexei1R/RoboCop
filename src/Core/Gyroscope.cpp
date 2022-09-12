#include "Gyroscope.h"

namespace Robot
{

    
    void Gyroscope::Begin()
    {
        writeGyroscope(MPU6050_SMPLRT_DIV, 0x00);
        writeGyroscope(MPU6050_CONFIG, 0x00);
        writeGyroscope(MPU6050_GYRO_CONFIG, 0x08);
        writeGyroscope(MPU6050_ACCEL_CONFIG, 0x00);
        writeGyroscope(MPU6050_PWR_MGMT_1, 0x01);
        this->Update();
        m_AngleGyroX = 0;
        m_AngleGyroY = 0;
        m_AngleX = this->GetAccX();
        m_AngleY = this->GetAccY();
        m_Time = millis();
    };

    void Gyroscope::writeGyroscope(byte reg, byte data)
    {
        Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(reg);
        Wire.write(data);
        Wire.endTransmission();
    }

    byte Gyroscope::readGyroscope(byte reg)
    {
        Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(reg);
        Wire.endTransmission(true);
        Wire.requestFrom(MPU6050_ADDR, 1);
        byte data = Wire.read();
        return data;
    }


    void Gyroscope::Update(){

Wire.beginTransmission(MPU6050_ADDR);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom((int)MPU6050_ADDR, 14);

        m_RawAccX = Wire.read() << 8 | Wire.read();
        m_RawAccY = Wire.read() << 8 | Wire.read();
        m_RawAccZ = Wire.read() << 8 | Wire.read();
        m_RawTemperature = Wire.read() << 8 | Wire.read();
        m_RawGyroX = Wire.read() << 8 | Wire.read();
        m_RawGyroY = Wire.read() << 8 | Wire.read();
        m_RawGyroZ = Wire.read() << 8 | Wire.read();

        m_Temperature = (m_RawTemperature + 12412.0) / 340.0;

        float accX = ((float)m_RawAccX) / 16384.0;
        float accY = ((float)m_RawAccY) / 16384.0;
        float accZ = ((float)m_RawAccZ) / 16384.0;

        m_AngleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 180 / PI;
        m_AngleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 180 / PI;

        float gyroX = ((float)m_RawGyroX) / 65.5;
        float gyroY = ((float)m_RawGyroY) / 65.5;
        float gyroZ = ((float)m_RawGyroZ) / 65.5;

        //gyroX -= gyroXoffset;
        //gyroY -= gyroYoffset;
        //gyroZ -= gyroZoffset;

        m_DeltaTime = (millis() - m_Time) * 0.001;

        m_AngleGyroX += gyroX * m_DeltaTime;
        m_AngleGyroY += gyroY * m_DeltaTime;
        m_AngleGyroZ += gyroZ * m_DeltaTime;

        m_AngleX = (GyroCoef * (m_AngleX + gyroX * m_DeltaTime)) + (AccCoef * m_AngleAccX);
        m_AngleY = (GyroCoef * (m_AngleY + gyroY * m_DeltaTime)) + (AccCoef * m_AngleAccY);
        m_AngleZ = m_AngleGyroZ* m_DeltaTime;

        m_Time = millis();


    };

}