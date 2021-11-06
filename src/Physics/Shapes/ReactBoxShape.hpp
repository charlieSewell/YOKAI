//ReactBoxShape.hpp - Axis Alligned Bounding Box

#pragma once

#include "ReactShape.hpp"
/**
 * @class ReactBoxShape
 * @brief Class for createing Axis Aligned Bounding Boxes
 */
class ReactBoxShape : public ReactShape
{
    public:
        /**
         * @brief Default Constructor
         */
        ReactBoxShape() =default;
        /**
         * @brief Default Destructor
         */
        ~ReactBoxShape()=default;
        /**
         * @brief Creates a box shape
         * @param bounds
         * @param physicsCommon
         */
        void CreateBoxShape(glm::vec3 bounds, reactphysics3d::PhysicsCommon &physicsCommon);
        /**
         * @brief Deletes a box shape
         * @param physicsCommon
         */
        void DeleteShape(reactphysics3d::PhysicsCommon &physicsCommon) override;
};