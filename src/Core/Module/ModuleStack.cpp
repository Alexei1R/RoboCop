#include "ModuleStack.h"

namespace Robot {
	ModuleStack::ModuleStack()
	{
	}

	ModuleStack::~ModuleStack()
	{
		for (Module* module : m_Modules)
			delete module;
	}

	void ModuleStack::PushModule(Module* module)
	{
		m_Modules.emplace(m_Modules.begin() + m_ModuleInsertIndex, module);
		m_ModuleInsertIndex++;
		module->OnAttach();
	}

	

	
}