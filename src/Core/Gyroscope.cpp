#include "Gyroscope.h"
#include "platform.h"

#include <Arduino.h>
#include <Wire.h>
namespace Robot
{

    Gyroscope *Gyroscope::Create()
    {

        switch (Platform::GetApi())
        {
        case PlatformApi::Arduino:
            return new Abstraction::Arduino_MPU();
        case PlatformApi::Raspberry:
            return new Abstraction::Arduino_MPU();

        default:
            return new Abstraction::Arduino_MPU();
        }
    }

    namespace Abstraction
    {

        // arduino implementation

        Arduino_MPU::Arduino_MPU()
        {
            Wire.beginTransmission(0b1101000); // This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
            Wire.write(0x6B);                  // Accessing the register 6B - Power Management (Sec. 4.28)
            Wire.write(0b00000000);            // Setting SLEEP register to 0. (Required; see Note on p. 9)
            Wire.endTransmission();
            Wire.beginTransmission(0b1101000); // I2C address of the MPU
            Wire.write(0x1B);                  // Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
            Wire.write(0x00000000);            // Setting the gyro to full scale +/- 250deg./s
            Wire.endTransmission();
            Wire.beginTransmission(0b1101000); // I2C address of the MPU
            Wire.write(0x1C);                  // Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
            Wire.write(0b00000000);            // Setting the accel to +/- 2g
            Wire.endTransmission();
        };
        Arduino_MPU::~Arduino_MPU(){};

        void Arduino_MPU::Update()
        {
            // Accelerometer Data
            float m_accelX, m_accelY, m_accelZ;
            // gyro data
            float m_gyroX, m_gyroY, m_gyroZ;

            //=========================
            //=read accelerometer data
            //=========================
            Wire.beginTransmission(0b1101000); // I2C address of the MPU
            Wire.write(0x3B);                  // Starting register for Accel Readings
            Wire.endTransmission();
            Wire.requestFrom(0b1101000, 6); // Request Accel Registers (3B - 40)
            while (Wire.available() < 6)
                ;
            m_accelX = Wire.read() << 8 | Wire.read(); // Store first two bytes into accelX
            m_accelY = Wire.read() << 8 | Wire.read(); // Store middle two bytes into accelY
            m_accelZ = Wire.read() << 8 | Wire.read(); // Store last two bytes into accelZ
            // convert data to force
            m_ForceX = m_accelX / 16384.0;
            m_ForceY = m_accelY / 16384.0;
            m_ForceZ = m_accelZ / 16384.0;

            //=========================
            //=read gyro  data ========
            //=========================

            Wire.beginTransmission(0b1101000); // I2C address of the MPU
            Wire.write(0x43);                  // Starting register for Gyro Readings
            Wire.endTransmission();
            Wire.requestFrom(0b1101000, 6); // Request Gyro Registers (43 - 48)
            while (Wire.available() < 6);
            m_gyroX = Wire.read() << 8 | Wire.read(); // Store first two bytes into accelX
            m_gyroY = Wire.read() << 8 | Wire.read(); // Store middle two bytes into accelY
            m_gyroZ = Wire.read() << 8 | Wire.read(); // Store last two bytes into accelZ
            // convert data to angle
            m_RotationX = m_gyroX / 131.0;
            m_RotationY = m_gyroY / 131.0;
            m_RotationZ = m_gyroZ / 131.0;
        }

        float Arduino_MPU::GetForceX() {return m_ForceX;};
        float Arduino_MPU::GetForceY() {return m_ForceY;};
        float Arduino_MPU::GetForceZ() {return m_ForceZ;};

        float Arduino_MPU::GetRotationX() {return m_RotationX;};
        float Arduino_MPU::GetRotationY() {return m_RotationY;};
        float Arduino_MPU::GetRotationZ() {return m_RotationZ;};

        float Arduino_MPU::GetYAW() { return 0.0; }
        float Arduino_MPU::GetPITCH() { return 0.0; }
        float Arduino_MPU::GetROLL() { return 0.0; }

























        // Raspberry implementation
        Raspberry_MPU::Raspberry_MPU(){};
        Raspberry_MPU::~Raspberry_MPU(){};
        float Raspberry_MPU::GetYAW() { return 0.0; }
        float Raspberry_MPU::GetPITCH() { return 0.0; }
        float Raspberry_MPU::GetROLL() { return 0.0; }
    }
}