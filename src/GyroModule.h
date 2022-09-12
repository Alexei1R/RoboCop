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
            Serial.print("\t");
            Serial.print(m_Gyro.GetAngleY());
            Serial.print("\t");
            Serial.print(m_Gyro.GetAngleZ());
            Serial.print("\t\n");
        }
        void OnFixedUpdate() override {}

    private:
        Robot::Gyroscope m_Gyro;
    };

    

}
