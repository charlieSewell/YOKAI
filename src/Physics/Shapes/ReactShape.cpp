//
// Created by charl on 19/05/2021.
//

#include "ReactShape.hpp"
void ReactShape::DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) {

}

reactphysics3d::CollisionShape* ReactShape::getShape() {
    return m_shape;
}
