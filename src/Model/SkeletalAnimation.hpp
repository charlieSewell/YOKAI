#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <map>
/**
 * @struct Frame
 * @brief Struct of animation frame data
 */
struct Frame {
    /// number of positions in the frame
    unsigned int numPositions = 0;
    /// number of rotation in the frame
    unsigned int numRotations = 0;
    ///vector of bone ids to positions
    std::vector<std::pair<double, glm::vec3>> position = {};
    ///vector of bone ids to rotations
    std::vector<std::pair<double, glm::quat>> rotation = {};
};
/**
 * @class SkeletalAnimation
 * @brief Holds all animation frames for a model
 */
class SkeletalAnimation {
    public:
        /**
         * @brief Default Constructor for SkeletalAnimation
         */
        SkeletalAnimation() =default;
        /**
         * @brief Constructor for SkeletalAnimation
         * @param name
         * @param animations
         * @param duration
         * @param TPS
         */
        SkeletalAnimation(std::string name, std::map<std::string,Frame> animations, float duration, float TPS);
        /**
         * @brief Finds a rotation frame given a time
         * @param currTime
         * @param frame
         * @return unsigned int
         */
        unsigned int FindRotation(double currTime, const Frame* frame);
        /**
         * @brief Finds a position frame given a time
         * @param currTime
         * @param frame
         * @return unsigned int
         */
        unsigned int FindPosition(double currTime, const Frame* frame);
        /**
         * @brief Finds a frame given frame name
         * @param frameName
         * @return
         */
        Frame* FindFrame(const std::string& frameName);
        /**
         * @brief Returns the Ticks Per Second
         * @return tps
         */
        double GetTPS(){return m_TPS;}
        /**
         * @brief Returns the Duration of the animation
         * @return
         */
        double GetDuration(){return m_duration;}
        /**
         * @brief returns the name of the animation
         * @return
         */
        std::string GetName(){return m_name;}
    private:
        ///map of frame names to frames
        std::map<std::string,Frame> m_frames;
        ///duration of animation
        double m_duration;
        ///ticks per second of animation
        double m_TPS;
        ///name of animation
        std::string m_name;

};
