#pragma once
#include "main.h"
#include "Core/Module/Module.h"
#include "Core/Gyroscope.h"

namespace Robot
{

    class Gyro : public Module
    {
    public:
        Gyro(){};
        ~Gyro() {};
        void OnAttach() override {
            m_Gyro.Begin();
        };
        void OnDetach() override {};



        void OnUpdate() override
        {
            m_Gyro.Update();
            Serial.print(m_Gyro.GetAngleX());
            Serial.print(",");
            Serial.print(m_Gyro.GetAngleY());
            Serial.print(",");
            Serial.println();
        }
        void OnFixedUpdate() override {}

    private:
        Robot::Gyroscope m_Gyro;
    };

    

}
