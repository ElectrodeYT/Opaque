#pragma once
/// Opaque Engine
// Scripts.h
// Scripts Header

#include <string>
#include <vector>
#include <lua.hpp>
#include "log.h"

class Scripts {
public:
	/// Load a lua file.
	/// Returns: script id.
	int LoadScript(std::string path, bool callPCall = true);
	/// Clean Stack
	bool CleanStack();
	/// Dump stack
	void DumpStack(int id);
	/// Call Function
	int CallFunction(int id, std::string func);
	/// Get a lua variable name.
	int GetVariable(int id, std::string variable);
	/// Register a C++ Function.
	bool RegisterFunction(int id, int (*function) (lua_State* L), std::string function_name);
	/// Deconstructor
	~Scripts();
	// Lua States
	std::vector<lua_State*> lua;
};

inline void DumpStackFromLuaState(lua_State* L) {
	LOG_DBG("Lua stack dump:");
	// Get lua stack size
	int lua_top = lua_gettop(L);
	for (int i = 1; i <= lua_top; i++) {
		int type = lua_type(L, i); // Get type of stack variable
		switch (type) {
		case LUA_TSTRING:
			LOG_DBG(i << ": " << lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:
			LOG_DBG(i << ": " << (lua_toboolean(L, i) ? "true" : "false"));
			break;
		case LUA_TNUMBER:
			LOG_DBG(i << ": " << lua_tonumber(L, i));
			break;
		default:
			LOG_DBG(i << ": " << lua_typename(L, type));
			break;
		}
	}
}