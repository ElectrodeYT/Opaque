#include <iostream>
#include "log.h"
#include "Scripts.h"
#include "LuaBindings.h"

int lua_log(lua_State* L) {
	std::string str(luaL_checkstring(L, 1));
	LOG_MSG("LUA: " << str);
	return 0;
}

int main() {
	// Create Script engine
	Scripts scripts;
	LOG_MSG("Opaque Engine, built on " << __DATE__ << " " << __TIME__);
	LOG_DBG("Running Pre-Window Script");
	int pre = scripts.LoadScript("pre.lua");
	int ret = scripts.CallFunction(pre, "hello");
	// Register some functions to the pre-window scripts
	// We dont register most functions tho
	scripts.RegisterFunction(pre, lua_log, "log");
	LOG_DBG("Pre window return: " << ret);
	LOG_DBG("Calling main script");
	int main_script = scripts.LoadScript("main.lua", false); // We dont want to run pcall
	// Create window
	OpenWindow();
	// Bind some functions
	AddLuaBindings(scripts.lua.at(main_script));
	scripts.RegisterFunction(main_script, lua_log, "log");
	scripts.DumpStack(main_script);
	// PCall everything not in a function
	// We dont do this in scripts.LoadScript for this because we need to load the libs first
	int pcall_error = lua_pcall(scripts.lua.at(main_script), 0, 0, 0);
	if (pcall_error) {
		std::string error_str(lua_tostring(scripts.lua.at(main_script), -1));
		LOG_ERR("PCalling main scripts threw error!");
		LOG_ERR("Error Message: " << error_str);
		return -1;
	}
	// Call main function
	scripts.CallFunction(main_script, "main");
	//// GAME LOOP
	bool do_loop = true;
	while (do_loop) {
		// Check if the loop threw a error or requested a close
		int loop_ret = scripts.CallFunction(main_script, "loop");
		if (loop_ret == -1) {
			LOG_ERR("FATAL: loop function threw error");
			exit(-1);
		} else if (loop_ret == -2) {
			LOG_MSG("Lua Loop requested the game stop");
			do_loop = false;
			continue;
		}
	}
}