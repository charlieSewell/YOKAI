#include "ReactConcaveShape.hpp"
#include "Controller/ModelManager.hpp"

void ReactConcaveShape::CreateConcaveShape(reactphysics3d::PhysicsCommon &physicsCommon, unsigned int modelID)
{
    
    triangleMesh = physicsCommon.createTriangleMesh(); 
    Model* model = Yokai::getInstance().getModelManager()->GetModel(modelID);
    vertices.resize(model->getMeshes()->size());
    indices.resize(model->getMeshes()->size());
    triangleArrays.resize(model->getMeshes()->size());
    int meshCount = 0;
    std::vector<Mesh>::iterator mesh;
    for(mesh = model->getMeshes()->begin(); mesh != model->getMeshes()->end(); ++mesh)
    {
        std::vector<Vertex>::iterator vertice;
        std::vector<unsigned int>::iterator indice;
        for(vertice = mesh->getVertices()->begin(); vertice != mesh->getVertices()->end(); ++vertice)
        {
            glm::vec4 temp = mesh->getTransform() * glm::vec4(vertice->position,1.0);
            vertices.at(meshCount).push_back(temp.x);
            vertices.at(meshCount).push_back(temp.y);
            vertices.at(meshCount).push_back(temp.z);
        }
        for(indice = mesh->getIndices()->begin(); indice != mesh->getIndices()->end(); ++indice)
        {
            indices.at(meshCount).push_back(static_cast<int>(*indice));
        }

        triangleArrays.at(meshCount) = new rp3d::TriangleVertexArray(vertices.at(meshCount).size(), &vertices.at(meshCount)[0], 3 * sizeof(float), indices.at(meshCount).size()/3,
                                                                      &indices.at(meshCount)[0], 3 * sizeof(int),
                                                                      rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                      rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
        // Add the triangle vertex array to the triangle mesh 
        triangleMesh->addSubpart(triangleArrays[meshCount]);
        meshCount++;
    }
    shape = physicsCommon.createConcaveMeshShape(triangleMesh);
}
void ReactConcaveShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon)
{
    physicsCommon.destroyConcaveMeshShape(dynamic_cast<rp3d::ConcaveMeshShape*>(shape));
    for (auto triangle : triangleArrays)
    {
        delete triangle;
    }
    triangleArrays.clear();
};
ReactConcaveShape::~ReactConcaveShape() {
    std::cout << "GOOOODBYYYYEEEE" << std::endl;
}