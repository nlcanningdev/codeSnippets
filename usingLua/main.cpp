/*opens a lua state, demonstrates some basics, then opens a file
the file stays opened (hopefully forever, do more research on this)
tell it which function in lua will be called
then send arguments
then call (num arguments, num return values, error handler function)
lua can return multiple values from functions
then pop the return values after getting them
figure out a way to deal with conversion problems to and from lua
(changed number to size_t in luaconf file in dependencies
still problems converting to int.  maybe use only size_t?*/

#include <lua.hpp>
#include <luajit.h>
#include <iostream>

int main(int argv, char** argc) {
	//initialise lua state
	lua_State* L = luaL_newstate();

	//load libraries
	luaL_openlibs(L);

	lua_pushnumber(L, 20);
	lua_pushstring(L, "nic");

	std::cout << lua_tonumber(L, 1) << std::endl;
	std::cout << lua_tostring(L, -1) << std::endl;
	std::cout << "size of stack: " << lua_gettop(L) << std::endl;

	lua_pop(L, lua_gettop(L)); //this clears the entire stack, can pop multiple items at once

	char input;

	std::cin >> input;

	if (luaL_dofile(L, "testLua.lua")) { //this should setup all the lua functions to be used
		std::cout << "lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, lua_gettop(L));
		std::cin >> input;
		return 0;
	}

	lua_getglobal(L, "testLuaFunction");
	size_t index = 10;
	int assetType = 14;
	lua_pushnumber(L, index);
	lua_pushinteger(L, assetType);
	if (lua_pcall(L, 2, 2, 0)) { //pcall should automatically pop the arguments as well as itself
		std::cout << "lua_pcall error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, lua_gettop(L));
		std::cin >> input;
		return 0;
	}
	for (int a = 1; a <= lua_gettop(L); ++a) {
		std::cout << "stack " << a << ": " << lua_tonumber(L, a) << std::endl;
	}
	index = lua_tonumber(L, 1);
	assetType = lua_tointeger(L, 2);
	lua_pop(L, lua_gettop(L));
	std::cout << "index: " << index << std::endl;
	std::cout << "assetType: " << assetType << std::endl;
	std::cin >> input;
	lua_getglobal(L, "testLuaFunction");
	lua_pushnumber(L, index);
	lua_pushinteger(L, assetType);
	if (lua_pcall(L, 2, 2, 0)) { //pcall should automatically pop the arguments as well as itself
		std::cout << "lua_pcall error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, lua_gettop(L));
		return 0;
	}
	index = lua_tonumber(L, 1);
	assetType = lua_tointeger(L, 2);
	lua_pop(L, lua_gettop(L));
	std::cout << "index: " << index << std::endl;
	std::cout << "assetType: " << assetType << std::endl;
	//close
	lua_close(L);

	std::cin >> input;
	return 0;
}