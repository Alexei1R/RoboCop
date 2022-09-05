#pragma once

namespace Robot
{



    class Module
    {
    public:
        Module();
        virtual ~Module() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnFixedUpdate() {}
    };


    \

}