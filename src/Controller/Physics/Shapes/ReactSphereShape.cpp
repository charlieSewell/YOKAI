//
// Created by charl on 19/05/2021.
//

#include "ReactSphereShape.hpp"
void ReactSphereShape::CreateSphereShape(float radius, reactphysics3d::PhysicsCommon &physicsCommon) {
    shape = physicsCommon.createSphereShape(radius);
}
void ReactSphereShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) {
    physicsCommon.destroySphereShape(dynamic_cast<rp3d::SphereShape*>(shape));
}