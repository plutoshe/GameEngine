#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SmartPointer.h"
#include "GameObject.h"
#include "List.h"

extern "C"
{
	#include "lua.h"  
	#include "lauxlib.h"  
	#include "lualib.h"  
}

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	// TODO: lua add gameobject
	// TODO: Normal addition interface

	DataStructure::List<Engine::OwningPointer<GameObject>> GameobjectList;

	void Update();
	template<class T>
	Engine::ObservingPointer<GameObject> AddGameObject(T gameobject) {
		GameobjectList.push(Engine::OwningPointer<T>(gameobject));
		Engine::ObservingPointer<GameObject> currentGameObject = GameobjectList[GameobjectList.get_size() - 1];
		currentGameObject->UpdateConnectionPointer(currentGameObject);
		return currentGameObject;
	}

	void RemoveGameObject(Engine::ObservingPointer<GameObject> p);

	Status AddGameObjectByLua(std::string filename) {
		using namespace std;
		lua_State *L = luaL_newstate();
		if (L == NULL)
		{
			return NullPointerError;
		}

		int bRet = luaL_loadfile(L, filename.c_str());
		if (bRet)
		{
			cout << "load file error" << endl;
			return BadError;
		}
		
		  
		Engine::ObservingPointer < GameObject > newGameObject = GetNewGameObject();
		string str = lua_tostring(L, -1);
		cout << "encoding string = " << str.c_str() << endl; 
		return NoError;
	}

	Engine::ObservingPointer<GameObject> GetNewGameObject() {
		Engine::OwningPointer<GameObject> emptyGameObject(new GameObject());
		GameobjectList.push(emptyGameObject);
		emptyGameObject->UpdateConnectionPointer(emptyGameObject);
		return emptyGameObject;
	}
	void Start();
	void Release();

private:
		
};


