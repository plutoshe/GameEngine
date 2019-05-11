#pragma once
#include "SSERedef.h"

extern "C"
{
#include "lua.h"  
#include "lauxlib.h"  
#include "lualib.h"  
}
Vector3f LuaGetVector3f(lua_State *L);
Vector2f LuaGetVector2f(lua_State *L);