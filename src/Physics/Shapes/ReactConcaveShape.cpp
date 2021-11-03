#include "ReactConcaveShape.hpp"
#include "Engine/ModelManager.hpp"

void ReactConcaveShape::CreateConcaveShape(reactphysics3d::PhysicsCommon &physicsCommon, unsigned int modelID)
{
    
    m_triangleMesh = physicsCommon.createTriangleMesh(); 
    Model* model = Yokai::getInstance().GetModelManager()->GetModel(modelID);
    m_vertices.resize(model->GetMeshes()->size());
    m_indices.resize(model->GetMeshes()->size());
    m_triangleArrays.resize(model->GetMeshes()->size());
    int meshCount = 0;
    std::vector<Mesh>::iterator mesh;
    for(mesh = model->GetMeshes()->begin(); mesh != model->GetMeshes()->end(); ++mesh)
    {
        std::vector<Vertex>::iterator vertice;
        std::vector<unsigned int>::iterator indice;
        for(vertice = mesh->getVertices()->begin(); vertice != mesh->getVertices()->end(); ++vertice)
        {
            glm::vec4 temp = mesh->getTransform() * glm::vec4(vertice->position,1.0);
            m_vertices.at(meshCount).push_back(temp.x);
            m_vertices.at(meshCount).push_back(temp.y);
            m_vertices.at(meshCount).push_back(temp.z);
        }
        for(indice = mesh->getIndices()->begin(); indice != mesh->getIndices()->end(); ++indice)
        {
            m_indices.at(meshCount).push_back(static_cast<int>(*indice));
        }

        m_triangleArrays.at(meshCount) = new rp3d::TriangleVertexArray(m_vertices.at(meshCount).size(), &m_vertices.at(meshCount)[0], 3 * sizeof(float), m_indices.at(meshCount).size()/3,
                                                                      &m_indices.at(meshCount)[0], 3 * sizeof(int),
                                                                      rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                      rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
        // Add the triangle vertex array to the triangle mesh 
        m_triangleMesh->addSubpart(m_triangleArrays[meshCount]);
        meshCount++;
    }
    m_shape = physicsCommon.createConcaveMeshShape(m_triangleMesh);
}
void ReactConcaveShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon)
{
    physicsCommon.destroyConcaveMeshShape(dynamic_cast<rp3d::ConcaveMeshShape*>(m_shape));
    for (auto triangle : m_triangleArrays)
    {
        delete triangle;
    }
    m_triangleArrays.clear();
};
ReactConcaveShape::~ReactConcaveShape() 
{
}