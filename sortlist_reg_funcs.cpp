#include "sortlist_reg_funcs.h"

int createsortlist(lua_State *L)
{
	//创建一个对象指针放到stack里，返回给Lua中使用，userdata的位置-1
	SortList** sortlist = (SortList**)lua_newuserdata(L, sizeof(SortList*));
	*sortlist = new SortList();
	//Lua->stack，得到全局元表位置-1,userdata位置-2
	luaL_getmetatable(L, "SortList");
	//将元表赋值给位置-2的userdata，并弹出-1的元表
	lua_setmetatable(L, -2);
	return 1;
}

//sortlist:addnode("AAA",121212)
int addnode(lua_State *L)
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");
   
    const char * id = luaL_checkstring(L, 2);
    int tm = luaL_checknumber(L, 3);

	cout << "add node:(" << id <<":"<<tm<<")"<<endl;
	sortlist->AddNode(id,tm);
	return 1;
}

int getnodesbytm(lua_State *L)
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");
	int tm = luaL_checknumber(L, 2);
	list<Node> nodes = sortlist->GetNodesByTm(tm);  //GetNodesByTm
	//set table to lua {id=tm,....}
	lua_newtable(L);
	int index = 0;
	for(list<Node>::iterator iter = nodes.begin();iter != nodes.end(); iter++)
	{
		index++;
		Node node = *iter;
		const char* id = node.get_id().c_str();
		int tm = node.get_tm();
		lua_pushstring(L,id);
		lua_rawseti(L,-2,index);
	}
	lua_setglobal(L, "nodes");
	return 1;
}

int updatenodetm(lua_State *L)
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");
	const char *id = luaL_checkstring(L, 2);
	int tm = luaL_checknumber(L,3);
	cout << "update node("<<id<<":"<<tm<<")"<<endl;
	sortlist->UpdateNodeTm(id,tm);
	return 1;
}

int getnodebyid(lua_State *L)
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");
	const char *id = luaL_checkstring(L, 2);
	Node node = sortlist->GetNodeById(id);
	int tm = node.get_tm();
	cout << "get node("<<id<<":"<<tm<<")"<<endl;
	lua_createtable(L,0,0);
	lua_pushstring(L, id);
	lua_pushnumber(L, tm);
	lua_settable(L, -3);
	return 1;
}

int printnodes(lua_State *L)
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");
	sortlist->PrintNodes();
}

int delnodebyids(lua_State *L) //ids = {id1,id2,id3}
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");	
	list<string> ids;
	int nidx = lua_gettop(L);// 取 table 索引值 
	lua_pushnil(L);
	while(0!= lua_next(L, nidx))
	{
		const char *id = lua_tostring(L,-1);
		printf("del node id:%s\n", id);
		lua_pop(L, 1);
		ids.push_back(id);
	}
	lua_pop(L, 1);
	// lua_getglobal(L, "del_ids");
	// lua_Integer len = luaL_len(L, -1);
	// for(lua_Integer i=1; i<=len; ++i)
	// {
	// 	int ret_type = lua_rawgeti(L, -1, i);
	// 	const char *id = NULL;
	// 	if (ret_type == LUA_TNUMBER){
 //            if (lua_isinteger(L, -1)){
 //                 printf("%lld\n", lua_tointeger(L, -1));
 //             }
 //             else if (lua_isnumber(L, -1)){
 //                 printf("%g\n", lua_tonumber(L, -1));
 //             }
 //         }
 //         else if (ret_type == LUA_TSTRING){
 //         	id = lua_tostring(L, -1);
 //             printf("%s\n", lua_tostring(L, -1));
 //         }
 //         ids.push_back(id);
 //         lua_pop(L, 1);
	// }
	sortlist->DelNodeByIds(ids);
}

int autogc(lua_State *L)   //free sortlist
{
	SortList* s = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, s != NULL, 1, "invalid user data");
	if(s){
		delete s;
	}
	return 0;
}

int sortlist2string(lua_State *L) //print sortlist infor nodes counts
{
	SortList* sortlist = *(SortList**)luaL_checkudata(L, 1, "SortList");
	luaL_argcheck(L, &sortlist != NULL, 1, "invalid user data");	
	
}

void lua_setfuncs(lua_State *L, const luaL_Reg *l, int nup)
{
    for (; l->name != NULL; l++)
    {
        int i;
        for (i = 0; i < nup; i++)
            lua_pushvalue(L, -nup);
        lua_pushcclosure(L, l->func, nup);
        lua_setfield(L, -(nup + 2), l->name);
    }
    lua_pop(L, nup);
}

extern "C" int luaopen_SortList(lua_State *L)
{
	//创建全局元表（里面包含了对LUA_REGISTRYINDEX的操作），元表的位置为-1
	luaL_newmetatable(L, "SortList");
	//将元表作为一个副本压栈到位置-1，原元表位置-2
	lua_pushvalue(L, -1);
	//设置-2位置元表的__index索引的值为位置-1的元表，并弹出位置-1的元表，原元表的位置为-1
	lua_setfield(L, 2, "__index");

    lua_setfuncs(L, sortlistlib_funcs, 0);
    luaL_register(L, "SortList", construct_func);
	return 1;
}

