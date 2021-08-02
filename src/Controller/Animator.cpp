#include <glm/gtx/string_cast.hpp>
#include <utility>
#include "Animator.hpp"
Animator::Animator(std::shared_ptr<Model> model)
	: currTime(0)
{
    this->modelToAnimate = std::move(model);
}
void Animator::BoneTransform(float TimeInSeconds)
{
    finalTransforms.resize(modelToAnimate->getBonesSize());
    glm::mat4 identity(1.0);
    currTime += TimeInSeconds;
    if(modelToAnimate != nullptr && modelToAnimate->getAnimation(animation) != nullptr)
    {
        double TicksPerSecond = modelToAnimate->getAnimation(animation)->getTPS();
        float TimeInTicks = currTime * static_cast<float>(TicksPerSecond);
        if(shouldEnd && TimeInTicks >= modelToAnimate->getAnimation(animation)->getDuration())
        {
            return;
        }
        float AnimationTime = static_cast<float>(fmod(TimeInTicks, modelToAnimate->getAnimation(animation)->getDuration()));

        ReadNodeHeirarchy(AnimationTime, modelToAnimate->getRootNode(), identity);
    }
    else
    {
        for(int i = 0;i < modelToAnimate->getBonesSize();i++)
        {
            finalTransforms[i] = glm::mat4(1.0f);
        }
    }
}
void Animator::ReadNodeHeirarchy(float AnimationTime, const Node& node, const glm::mat4& parentTransform)
{
    glm::mat4 nodeTransformation(node.transform);

    const auto* pNodeAnim = modelToAnimate->getAnimation(animation)->findFrame(node.name);

    if (pNodeAnim)
    {
        // Interpolate rotation and generate rotation transformation matrix
        glm::mat4 rotation = glm::mat4(CalcInterpolatedRotation(AnimationTime, pNodeAnim));

        // Interpolate translation and generate translation transformation matrix
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), CalcInterpolatedPosition(AnimationTime, pNodeAnim));

        nodeTransformation = translation * rotation;
    }

    glm::mat4 GlobalTransformation = parentTransform * nodeTransformation;
    if (modelToAnimate->getBoneMap()->find(node.name) != modelToAnimate->getBoneMap()->end())
    {
        unsigned int BoneIndex = modelToAnimate->getBoneMap()->at(node.name);
        finalTransforms[BoneIndex]= modelToAnimate->getGlobalInverseTransform() * GlobalTransformation * modelToAnimate->getBones()->at(BoneIndex).offset;
    }

   for(auto& child: node.children)
   {
       ReadNodeHeirarchy(AnimationTime,child,GlobalTransformation);
   }
}
glm::quat Animator::CalcInterpolatedRotation(double AnimationTime, const Frame* pNodeAnim)
{
    glm::quat rotation;
    // we need at least two values to interpolate...
    if (pNodeAnim->numRotations == 1)
    {
        rotation = pNodeAnim->rotation[0].second;
        return rotation;
    }

    unsigned int RotationIndex = modelToAnimate->getAnimation(animation)->FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);


    double DeltaTime = pNodeAnim->rotation[NextRotationIndex].first - pNodeAnim->rotation[RotationIndex].first;
    double Factor = (AnimationTime - pNodeAnim->rotation[RotationIndex].first) / DeltaTime;

    const glm::quat& StartRotationQ = pNodeAnim->rotation[RotationIndex].second;
    const glm::quat& EndRotationQ = pNodeAnim->rotation[NextRotationIndex].second;
    rotation = glm::slerp(StartRotationQ, EndRotationQ, static_cast<float>(Factor));
    rotation = glm::normalize(rotation);
    return rotation;
}
glm::vec3 Animator::CalcInterpolatedPosition(double AnimationTime, const Frame *pNodeAnim)
{
    glm::vec3 result;
    if (pNodeAnim->numPositions == 1)
    {
        result = pNodeAnim->position[0].second;
        return result;
    }

    unsigned PositionIndex = modelToAnimate->getAnimation(animation)->FindPosition(AnimationTime, pNodeAnim);
    unsigned NextPositionIndex = (PositionIndex + 1);

    double DeltaTime = pNodeAnim->position[NextPositionIndex].first - pNodeAnim->position[PositionIndex].first;
    double Factor = (AnimationTime - pNodeAnim->position[PositionIndex].first) / DeltaTime;

    const glm::vec3& Start = pNodeAnim->position[PositionIndex].second;
    const glm::vec3& End = pNodeAnim->position[NextPositionIndex].second;
    glm::vec3 Delta = End - Start;
    result = Start + static_cast<float>(Factor) * Delta;
    return result;
}
void Animator::setAnimation(std::string animationToSet)
{
	if(animation != animationToSet)
	{
		try
		{
			currTime = 0;
			SkeletalAnimation* test = modelToAnimate->getAnimation(animationToSet);
			this->animation = std::move(animationToSet);
		}catch (std::exception &e)
		{
			std::cout << e.what() <<std::endl;
		}
	}
}