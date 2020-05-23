#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scripts.h"

// Lua Bindings
// Not in a class because of lua stuff

bool OpenWindow();
/// Add lua bindings
bool AddLuaBindings(lua_State* L);
// SFML Window
static sf::RenderWindow win;
static std::vector<sf::Sprite> sprites;
static std::vector<sf::Texture> textures;

// Clocks for delta time calculation

static double delta = 0.0f;
static sf::Clock deltatime_clock;

//// Lua functions

/// Clear screen
int L_Clear_Screen(lua_State* L);
/// Set frame rate
int L_Framerate(lua_State* L);
/// Poll SFML Events
int L_PollEvent(lua_State* L);
/// Change window title
int L_Title(lua_State* L);
/// Load Image file
int L_Load_Texture(lua_State* L);
/// Load Sprite from Image
int L_Load_Sprite(lua_State* L);
/// Draw Sprite
int L_Draw(lua_State* L);
/// Set Sprite Coords
int L_Sprite_SetCoords(lua_State* L);
/// Get Sprite Coords
int L_Sprite_GetCoords(lua_State* L);
/// Flip Buffers
int L_Flip_Buffer(lua_State* L);
/// Get Delta Time
int L_DeltaTime(lua_State* L);
/// Get Keys down
int L_KeysDown(lua_State* L);

/// Lua Lib Definitions

static const struct luaL_Reg lib_opaque[] = {
	{"clearScreen", L_Clear_Screen},
	{"framerate", L_Framerate},
	{"flip", L_Flip_Buffer},
	{"title", L_Title},
	{"pollEvent", L_PollEvent},
	{"deltaTime", L_DeltaTime},
	{NULL, NULL}
};

static const struct luaL_Reg lib_sprite[] = {
	{"loadTexture", L_Load_Texture},
	{"loadSprite", L_Load_Sprite},
	{"drawSprite", L_Draw},
	{"setCoords", L_Sprite_SetCoords},
	{"getCoords", L_Sprite_GetCoords},
	{NULL, NULL}
};

static const struct luaL_Reg lib_keyboard[] = {
	{NULL, NULL}
};