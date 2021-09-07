//
// Created by Charlie Sewell on 13/05/2021.
//

#include <Model/Components/Transform.hpp>
#include "ReactTerrainShape.hpp"

ReactTerrainShape::ReactTerrainShape()
{

}

ReactTerrainShape::~ReactTerrainShape()
{

}
void ReactTerrainShape::CreateTerrainShape(reactphysics3d::PhysicsCommon &physicsCommon, std::vector<std::vector<float>> heightVals)
{
    heightFieldArray = new float[100*100];
    for(int x=0; x<100; ++x)
    {
        for(int z=0; z<100; ++z)
        {
            heightFieldArray[x * 100 + z] = heightVals.at(static_cast<float>(z)).at(static_cast<float>(x));
            std::cout << heightFieldArray[x * 100 + z] <<std::endl;
        }
    }
    shape = physicsCommon.createHeightFieldShape(100,100, 0, 255, heightFieldArray, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
}
void ReactTerrainShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon)
{

}