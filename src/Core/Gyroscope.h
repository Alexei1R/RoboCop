#pragma once
#include <Arduino.h>

namespace Robot
{
    class Gyroscope
    {
    public:
        virtual float GetYAW();
        virtual float GetPITCH();
        virtual float GetROLL();
        virtual void Update();

        virtual float GetForceX();
        virtual float GetForceY();
        virtual float GetForceZ();

        virtual float GetRotationX();
        virtual float GetRotationY();
        virtual float GetRotationZ();

        static Gyroscope *Create();
    };

    /// abstractions ===================
    namespace Abstraction
    {
        class Arduino_MPU : public Gyroscope
        {
        public:
            Arduino_MPU();
            ~Arduino_MPU();

            void Update() override;

            float GetYAW() override;
            float GetPITCH() override;
            float GetROLL() override;

            virtual float GetForceX()override;
            virtual float GetForceY()override;
            virtual float GetForceZ()override;

            virtual float GetRotationX()override;
            virtual float GetRotationY()override;
            virtual float GetRotationZ()override;

        private:
            // Accelerometer Force
            float m_ForceX, m_ForceY, m_ForceZ;
            float m_RotationX, m_RotationY, m_RotationZ;
        };

        class Raspberry_MPU : public Gyroscope
        {
        public:
            Raspberry_MPU();
            ~Raspberry_MPU();

            void Update() override;

            float GetYAW() override;
            float GetPITCH() override;
            float GetROLL() override;

            virtual float GetForceX()override;
            virtual float GetForceY()override;
            virtual float GetForceZ()override;

            virtual float GetRotationX()override;
            virtual float GetRotationY()override;
            virtual float GetRotationZ()override;
        };
    }

}