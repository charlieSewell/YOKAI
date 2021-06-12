//
// Created by Charlie Sewell on 13/05/2021.
//

#include <Model/Components/Transform.hpp>
#include "ReactTerrainShape.hpp"

ReactTerrainShape::ReactTerrainShape()
{
    heightFieldArray = new float[TerrainFactory::getInstance().getTerrainSize()*TerrainFactory::getInstance().getTerrainSize()];
}
ReactTerrainShape::~ReactTerrainShape()
{
}
void ReactTerrainShape::CreateTerrainShape(reactphysics3d::PhysicsCommon &physicsCommon)
{
    int terrainSize = TerrainFactory::getInstance().getTerrainSize();
    for(int x=0; x<terrainSize; ++x)
    {
        for(int z=0; z<terrainSize; ++z)
        {
            heightFieldArray[x * terrainSize + z] = TerrainFactory::getInstance().heightAt(static_cast<float>(z),static_cast<float>(x));
        }
    }
    shape = physicsCommon.createHeightFieldShape(terrainSize, terrainSize, 0, 255, heightFieldArray, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);

}
void ReactTerrainShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon){
    physicsCommon.destroyHeightFieldShape(dynamic_cast<reactphysics3d::HeightFieldShape*>(shape));
    delete[] heightFieldArray;
}