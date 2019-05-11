#include "LuaUtil.h"

Vector3f LuaGetVector3f(lua_State *L) {
	Vector3f r;
	for (int i = 1; i <= 3; ++i) {
		lua_pushnumber(L, i);
		lua_gettable(L, -2);
		r[i - 1] = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}
	return r;
}

Vector2f LuaGetVector2f(lua_State *L) {
	Vector2f r;
	for (int i = 1; i <= 2; ++i) {
		lua_pushnumber(L, i);
		lua_gettable(L, -2);
		r[i - 1] = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}
	return r;
}