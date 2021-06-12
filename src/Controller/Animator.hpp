#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/random.hpp>
#include "Model/Model.hpp"
#include "Controller/LuaManager.hpp"
#include <utility>
#include <vector>
/**
 * @class Animator
 * @brief Skeletal Animator component
 */
class Animator{
    public:
    /**
     * @brief Default Constructor for Animator
     */
        Animator() = default;
        /**
         * @brief Constructor for animator that takes a model pointer
         * @param model
         */
        Animator(std::shared_ptr<Model> model);
        /**
         * @brief Interpolates the animation based on the time input
         * @param TimeInSeconds
         */
        void BoneTransform(float TimeInSeconds);
        /**
         * @brief Adds the model to be animated
         * @param model
         */
        void addModel(std::shared_ptr<Model> model){modelToAnimate = std::move(model);}
        /**
         * @brief Sets the animation string
         * @param animationToSet
         */
        void setAnimation(std::string animationToSet);
        /**
         * @brief Starts the animation
         */
        void startAnimation(){shouldEnd = false;}
        /**
         * @brief Tells animation to stop when finished
         */
        void endAnimation(){shouldEnd = true;}
        ///transforms to be fed into shader
        std::vector<glm::mat4> finalTransforms;
        /**
         * @brief Registers class in lua
         */
		static void registerClass();

    private:
        /**
         * @brief Reads the node heirachy and animates that node
         * @param AnimationTime
         * @param node
         * @param ParentTransform
         */
        void ReadNodeHeirarchy(float AnimationTime, const Node& node, const glm::mat4& ParentTransform);
        /**
         * @brief Calculates interpolated Rotation
         * @param AnimationTime
         * @param pNodeAnim
         * @return
         */
        glm::quat CalcInterpolatedRotation(double AnimationTime, const Frame* pNodeAnim);
        /**
         * @brief Calculates interpolated Position
         * @param AnimationTime
         * @param pNodeAnim
         * @return
         */
        glm::vec3 CalcInterpolatedPosition(double AnimationTime, const Frame* pNodeAnim);
        ///current animation time
        float currTime;
        ///should animation end
        bool shouldEnd = false;
        ///string of animation to play
        std::string animation;
        ///pointer to model
        std::shared_ptr<Model> modelToAnimate;

};
