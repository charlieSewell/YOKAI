#pragma once
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>

/**
 * @class LuaManager
 * @brief Responsible for managing lua scripts
 */
class LuaManager
{
	public: 
        /*!
         * @brief Singleton Pattern for a single instance of the class
         * @return instance
         */
        static LuaManager &getInstance();

        /*!
         * @brief Getter for the lua state
         * @return lua_state
         */
        lua_State *getState();

        /*!
         * @brief Runs the specified lua script
         * @param string - scriptName
         */
        static void runScript(std::string scriptName);

		static void callFunction(std::string func);

	private:
        /*!
         * @brief Constructor
         */
        LuaManager();

        /*!
         * @brief Deconstructor
         */
        ~LuaManager();

        /// Lua state
        lua_State *L = nullptr;
};