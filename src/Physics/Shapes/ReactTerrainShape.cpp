//
// Created by Charlie Sewell on 13/05/2021.
//

#include "Transform.hpp"
#include "ReactTerrainShape.hpp"

ReactTerrainShape::ReactTerrainShape()
{

}

ReactTerrainShape::~ReactTerrainShape()
{

}
void ReactTerrainShape::CreateTerrainShape(reactphysics3d::PhysicsCommon &physicsCommon, std::vector<std::vector<float>> heightVals)
{
    m_heightFieldArray = new float[100*100];
    for(size_t x=0; x<100; ++x)
    {
        for(size_t z=0; z<100; ++z)
        {
            m_heightFieldArray[x * 100 + z] = heightVals.at(z).at(x);
            //std::cout << heightFieldArray[x * 100 + z] <<std::endl;
        }
    }
    m_shape = physicsCommon.createHeightFieldShape(100,100, 0, 255, m_heightFieldArray, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
}
void ReactTerrainShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon)
{

}