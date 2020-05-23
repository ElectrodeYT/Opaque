#include "Scripts.h"
#include "log.h"

int Scripts::LoadScript(std::string path, bool callPCall) {
	// Basic things
	int error;
	// Load lua
	lua_State* Lua = luaL_newstate();
	// Load libs
	luaL_openlibs(Lua);
	// Load lua file
	error = luaL_loadfile(Lua, path.c_str());
	if (callPCall == true) { error = error || lua_pcall(Lua, 0, 0, 0); }
	if (error) {
		std::string error_str(lua_tostring(Lua, -1));
		LOG_ERR("Loading Script " << path << " failed!");
		LOG_ERR("Error Message: " << error_str);
		return -1;
	}
	// Get script id
	int id = lua.size();
	// Store pointer
	lua.push_back(Lua);
	return id;
}


void Scripts::DumpStack(int id) {
	LOG_DBG("Lua stack dump of script " << id << ":");
	// Get lua stack size
	int lua_top = lua_gettop(lua.at(id));
	for (int i = 1; i <= lua_top; i++) {
		int type = lua_type(lua.at(id), i); // Get type of stack variable
		switch (type) {
			case LUA_TSTRING:
				LOG_DBG(i << ": " << lua_tostring(lua.at(id), i));
				break;
			case LUA_TBOOLEAN:
				LOG_DBG(i << ": " << (lua_toboolean(lua.at(id), i) ? "true" : "false"));
				break;
			case LUA_TNUMBER:
				LOG_DBG(i << ": " << lua_tonumber(lua.at(id), i));
				break;
			default:
				LOG_DBG(i << ": " << lua_typename(lua.at(id), type));
				break;
		}
	}
}

int Scripts::CallFunction(int id, std::string func) {
	if (id == -1) {
		LOG_ERR("Attempting to call a function in a script that just doesnt exist!");
		return -1;
	}
	int return_value;
	// Push function name
	lua_getglobal(lua.at(id), func.c_str());
	// Call the function
	if (lua_pcall(lua.at(id), 0, 1, 0) != 0) {
		std::string error(lua_tostring(lua.at(id), -1));
		LOG_ERR("Error running function " << func << "!");
		LOG_ERR("Error code: " << error);
		return -1;
	}
	// Save value
	return_value = lua_tointeger(lua.at(id), -1);
	lua_pop(lua.at(id), 1);
	return return_value;
}

int Scripts::GetVariable(int id, std::string variable) {
	return 0;
}

bool Scripts::RegisterFunction(int id, int (*function) (lua_State* L), std::string function_name) {
	// Push function to lua stack
	LOG_DBG("Registering function " << function_name << " to script " << id);
	lua_pushcfunction(lua.at(id), function);
	lua_setglobal(lua.at(id), function_name.c_str());
	return false;
}

Scripts::~Scripts() {
	// I know this can cause a memory leak, not closing lua here,
	// but for reasons i cant
}