#pragma once
#include "Core/Module/Module.h"
#include "Core/Gyroscope.h"

namespace Robot
{

    class GyroModule : public Module
    {
    public:
        GyroModule()
        {
            m_Gyro = Gyroscope::Create();
        }
        ~GyroModule() {}
        void OnAttach() override {}
        void OnDetach() override {}
        void OnUpdate() override
        {
            m_Gyro->Update();
        }
        void OnFixedUpdate() override {}

    private:
        Gyroscope *m_Gyro;
    };

}