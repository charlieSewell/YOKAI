
#include "Controller/LuaManager.hpp"
#include "Model/GameObjects/GameObject.hpp"
namespace LuaTypes {
    /**
     * @brief Returns NPC Type
     * @return GameObjectType
     */
    GameObjectType getNPCType();
    /**
     * @brief Returns Static Type
     * @return GameObjectType
     */
    GameObjectType getStaticType();
    /**
     * @brief Returns Player Type
     * @return GameObjectType
     */
    GameObjectType getPlayerType();
};
//Wrapper found online to make Enums work in Lua
//https://github.com/vinniefalco/LuaBridge/blob/baba8b6a95a7aa92996e86a0846750aac9a57274/Tests/Source/IssueTests.cpp#L147
template <typename T>
/**
 * @struct EnumWrapper
 * @brief Wrapper used to pass enums to Lua
 * @tparam T
 */
struct EnumWrapper
{
    static typename std::enable_if<std::is_enum<T>::value, void>::type push(lua_State* L, T value)
    {
        lua_pushnumber (L, static_cast<std::size_t> (value));
    }

    static typename std::enable_if<std::is_enum<T>::value, T>::type get(lua_State* L, int index)
    {
        return static_cast <T> (lua_tointeger (L, index));
    }
};

namespace luabridge {

    template <>
    struct Stack <GameObjectType> : EnumWrapper <GameObjectType>
    {

    };
}
