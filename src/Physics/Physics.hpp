#pragma once
#include <glm/glm.hpp>
 namespace Physics 
{
    namespace Units 
    {
        struct Seconds 
        {
            double value;
        };

        struct MassInKilograms 
        {
            double value;
        };

        struct Minutes 
        {
            double value;
        };

        struct MetersPerSecond 
        {
            glm::dvec3 value;
        };
    }
    enum CollisionCategory 
    {
        CATEGORY1 = 0x0001,
        CATEGORY2 = 0x0002,
        CATEGORY3 = 0x0004
    };
};