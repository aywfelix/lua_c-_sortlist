
#ifndef TEST_REG_FUNCS_H
#define TEST_REG_FUNCS_H


#include "lua.hpp"
#include "sortlist.h"

//define c++ funcs
int createsortlist(lua_State *L);
int addnode(lua_State *L);
int getnodesbytm(lua_State *L);
int updatenodetm(lua_State *L);
int getnodebyid(lua_State *L);
int printnodes(lua_State *L);
int delnodebyids(lua_State *L);
int autogc(lua_State *L);   //free sortlist
int sortlist2string(lua_State *L); //print sortlist infor nodes counts

//register c++ funcs to lua
static const luaL_Reg construct_func[]={
	{"create", createsortlist},
	{NULL,NULL},
};

static const luaL_Reg sortlistlib_funcs[] = {
	{"add_node", addnode},
	{"get_nodes_by_tm", getnodesbytm},
	{"update_node_tm", updatenodetm},
	{"get_node_by_id", getnodebyid},
	{"print_nodes", printnodes},
	{"del_node_by_ids", delnodebyids},
	{"__gc", autogc},
	{"__tostring", sortlist2string},
	{NULL,NULL},
};

extern "C" int luaopen_SortList(lua_State *L);

#endif


//g++ lua.hpp sortlist.cpp sortlist.h sortlist_reg_funcs.cpp sortlist_reg_funcs.h -I/home/xxx/lua-5.1.5/src/ -fPIC -shared -o sortlist.so