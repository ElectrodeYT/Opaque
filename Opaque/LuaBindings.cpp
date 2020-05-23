#include <SFML/Graphics/Image.hpp> // For Lua image
#include "LuaBindings.h"
#include "log.h"

bool OpenWindow() {
	// The window needs to be a pointer because the assignment operator doesnt exist
	win.create(sf::VideoMode(800, 600), "Opaque");
	return false;
}

bool AddLuaBindings(lua_State* L) {
	// Register Libs
	// Opaque commands

	// lua_openlib() substitute for 5.2
	lua_newtable(L);
	luaL_setfuncs(L, lib_opaque, 0);
	lua_setglobal(L, "opaque");
	// Sprite commands
	lua_newtable(L);
	luaL_setfuncs(L, lib_sprite, 0);
	lua_setglobal(L, "sprite");
	return true;
}

/// LUA Functions
// Not a class because lua likes c

int L_Clear_Screen(lua_State* L) {
	win.clear();
	return 0;
}

int L_Framerate(lua_State* L) {
	// Get Framerate
	int framerate = luaL_checkinteger(L, 1);
	win.setFramerateLimit(framerate);
	return 0;
}

int L_PollEvent(lua_State* L) {
	int return_val = 0;
	sf::Event ev;
	win.pollEvent(ev);
	if (ev.type == sf::Event::Closed) {
		win.close();
		return_val = 1;
	}
	lua_pushinteger(L, return_val);
	//LOG_DBG("Lua called Poll Event");
	return 1; // Number of return values
}

int L_Title(lua_State* L) {
	const char* str = luaL_checkstring(L, 1);
	win.setTitle(str); // Set window title
	return 0;
}

int L_Load_Texture(lua_State* L) {
	const char* path = luaL_checkstring(L, 1); // Path to image file
	// Create new texture
	int tex_id = textures.size();
	textures.push_back(sf::Texture());
	// Load image file
	textures.at(tex_id).loadFromFile(path);
	// Return texture id
	lua_pushinteger(L, tex_id);
	return 1;
}

int L_Load_Sprite(lua_State* L) {
	DumpStackFromLuaState(L);
	int tex_id = luaL_checkinteger(L, 1); // Texture id
	// Create new sprite
	int sprite_id = sprites.size();
	sprites.push_back(sf::Sprite());
	// Set sprite texture
	sprites.at(sprite_id).setTexture(textures.at(tex_id));
	// Return sprite id
	lua_pushinteger(L, sprite_id);
	return 1;
}

int L_Draw(lua_State* L) {
	int sprite_id = luaL_checkinteger(L, 1); // Sprite id
	win.draw(sprites.at(sprite_id)); // Draw sprite
	return 0;
}

int L_Sprite_SetCoords(lua_State* L) {
	int sprite_id = luaL_checkinteger(L, 1); // Sprite id
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3); // Sprite id
	sprites.at(sprite_id).setPosition(sf::Vector2f(x, y));
	return 0;
}

int L_Sprite_GetCoords(lua_State* L) {
	int sprite_id = luaL_checkinteger(L, 1);
	// Return x and y
	lua_pushnumber(L, sprites.at(sprite_id).getPosition().x);
	lua_pushnumber(L, sprites.at(sprite_id).getPosition().y);
	return 2;
}

int L_Flip_Buffer(lua_State* L) {
	win.display();
	delta = deltatime_clock.getElapsedTime().asSeconds();
	deltatime_clock.restart();
	return 0;
}

int L_DeltaTime(lua_State* L) {
	lua_pushnumber(L, delta);
	return 1;
}

int L_KeysDown(lua_State* L) {
	// Create new, empty table
	lua_newtable(L);
	sf::Keyboard::
	return 1;
}
