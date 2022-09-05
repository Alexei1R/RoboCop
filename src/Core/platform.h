#pragma once

namespace Robot
{
    enum class PlatformApi
    {
        Arduino,
        Raspberry,

    };

    class Platform
    {
    public:
        Platform();
        inline static PlatformApi& GetApi() { return s_api; }

    private:
        static PlatformApi s_api ;
    };

}