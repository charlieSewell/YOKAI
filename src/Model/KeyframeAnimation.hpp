#pragma once

#include <iostream>
#include <vector>
#include "Model/ObjectLoading/ModelLoader.hpp"
#include <fstream>
#include <memory>
#include "Components/Transform.hpp"

/**
 * @class KeyframeAnimation
 * @brief Class for storing keyframe animations
 */
class KeyframeAnimation 
{
	public:
        /**
         * @brief Default constructor
         */
        KeyframeAnimation();
        /**
         * @brief Reads text file and loads all key frame models
         * @param textPath
         */
        void readFile(const std::string &textPath);
        /**
         * @brief Sets current animation
         * @param name
         */
        void setAnimation(std::string name);
        /**
         * @brief Adds an animation given a range of frames
         * @param animation
         * @param firstFrame
         * @param lastFrame
         */
        void addAnimation(const std::string& animation, int firstFrame, int lastFrame);
        /**
         * @brief Gets the current animation name
         * @return
         */
        std::string getCurrentAnimation() const; 
        /**
         * @brief Loads the model
         * @param modelPath
         */
        void collectModel(const std::string &modelPath);
        /**
         * @brief Sets the current frame of animation
         * @param dTime
         */
        void setCurrentFrame(double dTime);
        /**
         * @brief Gets the current frame
         * @return frame
         */
        int getCurrentFrame() const;
        /**
         * @brief Draws the Model
         * @param t
         */
        void draw(Transform t);
        /**
         * @brief Sets the ticks per second
         * @param tps
         */
        void setTPS(float tps);
        /**
         * @brief Gets the ticks per second
         * @return tps
         */
        float getTPS() const;
        /**
         * @brief Sets the animation to finish
         * @param a
         */
        void setAnimationFinished(bool a);
        /**
         * @brief Checks if animation is finished
         */
        void checkAnimationFinished();
        /**
         * Returns a bool based on whether animation is underway
         * @return
         */
        bool getAnimationFinished() const;
        /**
         * @brief Checks to make sure animation isnt in progress before swapping
         */
        void swapAnimationCheck();

	private:
      ///Shader for model
      std::shared_ptr<Shader> shader;
      ///vector of keyframes
      std::vector<std::shared_ptr<Model>> models;
      ///Model Loader
      ModelLoader loader;
      ///current frame
      int currentFrame;
      ///total animation time
      double totalTime;
      ///Ticks per second
      float ticksPerSecond;
      ///animation map
      std::map<std::string, std::pair<int, int>> animations;
      ///currently playing animation name
      std::string currentAnimation;
      ///is animation finished
      bool animationFinished;
      ///temp animation
      std::string tempAnimation;
};