//
// Created by Charlie Sewell on 13/05/2021.
//

#include "CollisionEventHandler.hpp"
#include "Controller/GameObjectManager.hpp"
void CollisionEventHandler::onContact(const CollisionCallback::CallbackData &callbackData) {
    for (int i = 0; i < callbackData.getNbContactPairs(); i++) 
    {
        for (int j = 0; j < callbackData.getContactPair(i).getNbContactPoints(); j++) 
        {
            rp3d::Vector3 temp(callbackData.getContactPair(i).getContactPoint(j).getWorldNormal());
            if (temp.y <= -0.4)
           {
               GameObjectManager::getInstance().getPlayer()->onBox = true;
           } else {
               GameObjectManager::getInstance().getPlayer()->onBox = false;
           }
        }

    }
}
	
