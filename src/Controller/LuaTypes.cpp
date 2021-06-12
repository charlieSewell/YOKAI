//
// Created by charl on 5/04/2021.
//

#include "LuaTypes.hpp"

GameObjectType LuaTypes::getNPCType()
{
    return GameObjectType::npc;
}

GameObjectType LuaTypes::getStaticType()
{
    return GameObjectType::staticObject;
}

GameObjectType LuaTypes::getPlayerType()
{
    return GameObjectType::player;
}