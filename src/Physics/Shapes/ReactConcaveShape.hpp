//
// Created by Charlie Sewell on 13/05/2021.
//
#pragma once
#include <vector>
#include "ReactShape.hpp"
#include "Engine/Yokai.hpp"
class ReactConcaveShape : public ReactShape{
  public:
    /**
     * @brief Default Constructor
     */
    ReactConcaveShape() = default;
    /**
     * @brief Default Destructor
     */
    ~ReactConcaveShape();
    /**
     * @brief Creates a Concave Shape
     * @param physicsCommon
     */
    void CreateConcaveShape(reactphysics3d::PhysicsCommon &physicsCommon, unsigned int modelID);
    /**
     * @brief Deletes a Concave Shape
     * @param physicsCommon
     */
    void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) override;
  private:
    ///vertices of concave shape
    std::vector<std::vector<float>> m_vertices;
    ///indices of concave shape
    std::vector<std::vector<int>> m_indices;
    ///triangle arrays of concave shape
    std::vector<rp3d::TriangleVertexArray*> m_triangleArrays;
    ///triangle mesh of concave shape
    rp3d::TriangleMesh* m_triangleMesh;
    ///concave mesh
    rp3d::ConcaveMeshShape* m_concaveMesh;
};
