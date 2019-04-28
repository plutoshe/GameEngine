#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SmartPointer.h"
#include "GameObject.h"
#include <vector>

//extern "C"
//{
//#include "lua.h"  
//#include "lauxlib.h"  
//#include "lualib.h"  
//}

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	// TODO: lua add gameobject
	// TODO: Normal addition interface

	std::vector<Engine::OwningPointer<GameObject>> GameobjectList;
	void Update();
	template<class T>
	Engine::ObservingPointer<GameObject> AddGameObject(T gameobject) {
		GameobjectList.push_back(Engine::OwningPointer<T>(gameobject));
		Engine::ObservingPointer<GameObject> currentGameObject = GameobjectList[GameobjectList.size() - 1];
		currentGameObject->UpdateConnectionPointer(currentGameObject);
		return currentGameObject;
	}

	Status AddGameObjectByLua(std::string filename) {
		/*using namespace std;
		lua_State *L = luaL_newstate();
		if (L == NULL)
		{
			return;
		}

		int bRet = luaL_loadfile(L, filename);
		if (bRet)
		{
			cout << "load file error" << endl;
			return;
		}
		
		  
		Engine::ObservingPointer < GameObject > newGameObject = GetNewGameObject();
		string str = lua_tostring(L, -1);
		cout << "encoding string = " << str.c_str() << endl; 
		newGameObject.Decode(str);

*/
	}

	Engine::ObservingPointer<GameObject> GetNewGameObject() {
		Engine::OwningPointer<GameObject> emptyGameObject(new GameObject());
		GameobjectList.push_back(emptyGameObject);
		emptyGameObject->UpdateConnectionPointer(emptyGameObject);
		return emptyGameObject;
	}
	void Start();
	void Release();

private:
		
};


