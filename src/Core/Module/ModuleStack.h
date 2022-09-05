#pragma once
#include "Module.h"
#include <vector>

namespace Robot
{

    class ModuleStack : public Module
    {
    public:
        ModuleStack();
        ~ModuleStack();

        void PushModule(Module *module);
        std::vector<Module *>::iterator begin() { return m_Modules.begin(); }
        std::vector<Module *>::iterator end() { return m_Modules.end(); }

    private:
        std::vector<Module *> m_Modules;
        unsigned int m_ModuleInsertIndex = 0;
    };

}