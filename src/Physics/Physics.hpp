#pragma once
#include <glm/glm.hpp>
#include "Export.hpp"
 namespace Physics 
{
    namespace Units 
    {
        struct YOKAI_API Seconds 
        {
            double value;
        };

        struct YOKAI_API MassInKilograms 
        {
            double value;
        };

        struct YOKAI_API Minutes 
        {
            double value;
        };

        struct YOKAI_API MetersPerSecond 
        {
            glm::dvec3 value;
        };
    }
    enum YOKAI_API CollisionCategory 
    {
        CATEGORY1 = 0x0001,
        CATEGORY2 = 0x0002,
        CATEGORY3 = 0x0004
    };
};