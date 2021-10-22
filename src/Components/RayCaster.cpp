#include "RayCaster.hpp"

RayCaster::RayCaster(GameObject* parent)
	: Component(parent)
{

}

int RayCaster::CastRay(glm::vec3 startPosition,glm::vec3 direction,float distance)
{
    glm::vec3 end = direction * distance + startPosition;

    PhysicsSystem::getInstance().physicsWorld->raycast(rp3d::Ray(ReactMath::glmVecToRP3d(startPosition), ReactMath::glmVecToRP3d(end)),this);
    if(!hits.empty())
    {
        float furthestHit = FLT_MAX;
        int gameObjID = -1;
        for(auto& a : hits)
        {
            if(a.first < furthestHit)
            {
                furthestHit = a.first;
                gameObjID = PhysicsSystem::getInstance().getPhysicsBody(a.second)->getGameObjectID();
            }
        }
        hits.clear();
        return gameObjID;
    }
    hits.clear();
    return -1;
}

rp3d::decimal RayCaster::notifyRaycastHit(const rp3d::RaycastInfo& info)
{
    if(info.collider != nullptr)
    {
        if(info.collider->getEntity().id != ownColliderID && info.collider->getEntity().id != excludedColliderID)
		{
            hits.emplace(info.hitFraction,info.collider->getEntity().id);
            return rp3d::decimal(1.0);
        }
		else
			return rp3d::decimal(1.0);
    }
    // Return a fraction of 1.0 to gather all hits
    return rp3d::decimal(0.0);
}

void RayCaster::setOwnColliderID(int ownColliderID)
{ 
	this->ownColliderID = ownColliderID;
}

void RayCaster::setExcludedColliderID(int id)
{
	excludedColliderID = id;
}