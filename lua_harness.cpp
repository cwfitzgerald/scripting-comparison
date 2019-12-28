#include "harness.hpp"
#include "moonjit/src/lua.hpp"
#include <cstdlib>
#include <iostream>

static void stackDump (lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

			case LUA_TSTRING:  /* strings */
				printf("`%s'", lua_tostring(L, i));
				break;

			case LUA_TBOOLEAN:  /* booleans */
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;

			case LUA_TNUMBER:  /* numbers */
				printf("%g", lua_tonumber(L, i));
				break;

			default:  /* other values */
				printf("%s", lua_typename(L, t));
				break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

int new_print(lua_State* state) {
	int count = lua_gettop(state);
	for (int i = 1; i <= count; ++i) {
		char const* string = lua_tostring(state, i);
		std::cout << string;
	}
	std::cout << '\n';
	return 0;
}

lua_State* state;

void initialize() {
	state = lua_open();

	luaL_openlibs(state);

	if (luaL_loadfile(state, "script/lua.lua") == 1) {
		std::cerr << "Didn't load\n";
		std::abort();
	};

	lua_newtable(state); // func table
	lua_pushstring(state, "print"); // func table string
	lua_getglobal(state, "print"); // func table string func
	lua_settable(state, -3); // func table
	lua_setfenv(state, -2); // func
	lua_pushvalue(state, -1); // func func

	stackDump(state);

	lua_call(state, 0, 0); // func
	lua_getfenv(state, -1); // func table
	lua_pushstring(state, "hello_world"); // func table string
	lua_gettable(state, -2); // func table function

	stackDump(state);

	lua_call(state, 0, 0); // func table
}