#include "Core/platform.h"
#include "Core/Gyroscope.h"
#include "Core/Module/Module.h"
#include "Core/Module/ModuleStack.h"


Robot::ModuleStack m_ModuleStack;
void PushModule(Robot::Module *module) {m_ModuleStack.PushModule(module);}