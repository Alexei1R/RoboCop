#include <Arduino.h>
#include "main.h"
#include <Wire.h>

#include <GyroModule.h>

Robot::ModuleStack m_ModuleStack;
void PushModule(Robot::Module *module) {m_ModuleStack.PushModule(module);}

void setup()
{
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  PushModule(new Robot::Gyro());
  
}

void loop()
{


//Serial.print(" : ");
//
//Serial.println(m_gyro.GetYAW());
for (auto module : m_ModuleStack){
  module->OnUpdate();
  module->OnFixedUpdate();
}


delay(24);
}