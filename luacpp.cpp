#include "lua.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

class CTest
{
public:
	CTest(){};
	virtual ~CTest(){};
	int add(int x, int y)
	{
		printf("%d\n", x+y );
		return x+y;
	}
};

static int CreateCTest(lua_State *L)
{
	*(CTest**)lua_newuserdata(L, sizeof(CTest*)) = new CTest();
	luaL_getmetatable(L, "CTest");
	lua_setmetatable(L, -2);
	return 1;
}

static int DestroyCTest(lua_State* L)
{
	delete *(CTest**)lua_topointer(L,1);
	return 0;
}

static int CallAdd(lua_State *L)
{
	CTest *pT = *(CTest**)lua_topointer(L,1);
	lua_pushnumber(L, pT->add(lua_tonumber(L,2), lua_tonumber(L,3)));
	return 1; 
}

int main(int argc, char const *argv[])
{
	lua_State *L = lua_open();
	luaopen_base(L);
	lua_pushcfunction(L, CreateCTest);
	lua_setglobal(L, "CTest");
	luaL_newmetatable(L, "CTest");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, DestroyCTest);
	lua_settable(L, -3);
	lua_pushstring(L, "__index");
	lua_pushvalue(L,-2);
	lua_settable(L, -3);

	lua_pushstring(L, "add");
	lua_pushfunction(L,CallAdd);
	lua_settable(L, -3);
	lua_pop(L, 1);

	lua_dofile(L, "LuaUseClass.lua");
	lua_close(L);

	return 0;
}

//g++ luacpp.cpp lua.hpp -I/home/lai/lua-5.1.5/src/ /usr/local/lib/liblua.a -o luaavg