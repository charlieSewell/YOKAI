//
// Created by Charlie Sewell on 13/05/2021.
//
#pragma once
#include "ReactShape.hpp"

class ReactTerrainShape : public ReactShape{
  public:
    /**
     * @brief Default Constructor
     */
    ReactTerrainShape();
    /**
     * @brief Default Destructor
     */
    ~ReactTerrainShape();
    /**
     * @brief Creates a Terrain Shape
     * @param physicsCommon
     */
    void CreateTerrainShape(reactphysics3d::PhysicsCommon &physicsCommon,std::vector<std::vector<float>> heightVals);
    /**
     * @brief Deletes a Terrain Shape
     * @param physicsCommon
     */
    void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) override;
  private:
    ///float* to heightfield array
    float *heightFieldArray = nullptr;
};
