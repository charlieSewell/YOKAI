// Lua Manager cpp
// Vladislav Kennebury 11/03/2021
// Version 1

#include "Controller/LuaManager.hpp"

LuaManager::LuaManager() 
{
    L = luaL_newstate();
    luaL_openlibs(L);

}

LuaManager & LuaManager::getInstance()
{
    static LuaManager instance;
    return instance;
}

LuaManager::~LuaManager() 
{
    //lua_close(L);
}

lua_State *LuaManager::getState()
{
    if (L != nullptr)
    {
        return L;
    }
    L = luaL_newstate();
    return L;
}

void LuaManager::runScript(std::string scriptName)
{
    luaL_dofile(getInstance().getState(), scriptName.c_str());
}

void LuaManager::callFunction(std::string func)
{
	luaL_dostring(getInstance().getState(), func.c_str());
}
