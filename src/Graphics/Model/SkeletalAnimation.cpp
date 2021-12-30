//
// Created by charl on 22/04/2021.
//

#include "SkeletalAnimation.hpp"

#include <utility>
SkeletalAnimation::SkeletalAnimation(std::string name, std::map<std::string,Frame> frames, float duration, float TPS)
{
    this->m_frames = std::move(frames);
    this->m_duration = duration;
    this->m_TPS = TPS;
    this->m_name = std::move(name);
}

unsigned int SkeletalAnimation::FindPosition(double currTime, const Frame* frame)
{
    for (unsigned int i = 0 ; i < frame->numPositions; i++)
    {
        if (currTime < frame->position[i + 1].first)
        {
            return i;
        }
    }
    return(0);
}
unsigned int SkeletalAnimation::FindRotation(double currTime, const Frame* frame)
{
    for (unsigned int i = 0 ; i < frame->numRotations; i++)
    {
        if (currTime < frame->rotation[i + 1].first)
        {
            return i;
        }
    }
    return(0);
}
Frame* SkeletalAnimation::FindFrame(const std::string& frameName)
{
    if (m_frames.count(frameName)) 
    {
        return &m_frames.at(frameName);
    }
    return nullptr;
}
