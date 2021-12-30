#include <glm/gtx/string_cast.hpp>
#include <utility>
#include "Animator.hpp"
Animator::Animator(Model* model)
	: m_currTime(0)
{
    this->m_modelToAnimate = model;
}
void Animator::BoneTransform(float TimeInSeconds)
{
    finalTransforms.resize(m_modelToAnimate->GetBonesSize());
    glm::mat4 identity(1.0);
    m_currTime += TimeInSeconds;
    if(m_modelToAnimate != nullptr && m_modelToAnimate->GetAnimation(m_animation) != nullptr)
    {
        double TicksPerSecond = m_modelToAnimate->GetAnimation(m_animation)->GetTPS();
        float TimeInTicks = m_currTime * static_cast<float>(TicksPerSecond);
        if(m_shouldEnd && TimeInTicks >= m_modelToAnimate->GetAnimation(m_animation)->GetDuration())
        {
            return;
        }
        float AnimationTime = static_cast<float>(fmod(TimeInTicks, m_modelToAnimate->GetAnimation(m_animation)->GetDuration()));

        ReadNodeHeirarchy(AnimationTime, m_modelToAnimate->GetRootNode(), identity);
    }
    else
    {
        for(int i = 0;i < m_modelToAnimate->GetBonesSize();i++)
        {
            finalTransforms[i] = glm::mat4(1.0f);
        }
    }
}
void Animator::ReadNodeHeirarchy(float AnimationTime, const Node& node, const glm::mat4& parentTransform)
{
    glm::mat4 nodeTransformation(node.transform);

    const auto* pNodeAnim = m_modelToAnimate->GetAnimation(m_animation)->FindFrame(node.name);

    if (pNodeAnim)
    {
        // Interpolate rotation and generate rotation transformation matrix
        glm::mat4 rotation = glm::mat4(CalcInterpolatedRotation(AnimationTime, pNodeAnim));

        // Interpolate translation and generate translation transformation matrix
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), CalcInterpolatedPosition(AnimationTime, pNodeAnim));

        nodeTransformation = translation * rotation;
    }

    glm::mat4 GlobalTransformation = parentTransform * nodeTransformation;
    if (m_modelToAnimate->GetBoneMap()->find(node.name) != m_modelToAnimate->GetBoneMap()->end())
    {
        unsigned int BoneIndex = m_modelToAnimate->GetBoneMap()->at(node.name);
        finalTransforms[BoneIndex]= m_modelToAnimate->GetGlobalInverseTransform() * GlobalTransformation * m_modelToAnimate->GetBones()->at(BoneIndex).offset;
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

    unsigned int RotationIndex = m_modelToAnimate->GetAnimation(m_animation)->FindRotation(AnimationTime, pNodeAnim);
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

    unsigned PositionIndex = m_modelToAnimate->GetAnimation(m_animation)->FindPosition(AnimationTime, pNodeAnim);
    unsigned NextPositionIndex = (PositionIndex + 1);

    double DeltaTime = pNodeAnim->position[NextPositionIndex].first - pNodeAnim->position[PositionIndex].first;
    double Factor = (AnimationTime - pNodeAnim->position[PositionIndex].first) / DeltaTime;

    const glm::vec3& Start = pNodeAnim->position[PositionIndex].second;
    const glm::vec3& End = pNodeAnim->position[NextPositionIndex].second;
    glm::vec3 Delta = End - Start;
    result = Start + static_cast<float>(Factor) * Delta;
    return result;
}
void Animator::SetAnimation(std::string animationToSet)
{
	if(m_animation != animationToSet)
	{
		try
		{
			m_currTime = 0;
			SkeletalAnimation* test = m_modelToAnimate->GetAnimation(animationToSet);
			this->m_animation = std::move(animationToSet);
		}catch (std::exception &e)
		{
			std::cout << e.what() <<std::endl;
		}
	}
}