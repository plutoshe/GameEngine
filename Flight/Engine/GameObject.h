#pragma once
#include "SSERedef.h"
#include "GLib.h"
#include "assert.h"
#include "SSERedef.h"
#include "GameObjectBasicAttr.h"
#include "Status.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "LuaUtil.h"

class GameManager;
class GameObject
{
public:
	Matrix4f LocalToWorldMatrix() {
		Matrix4f a = Matrix4f::GetTranslationMatrix(Vector4f(BasicAttr.Position)) * Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
		return a;
	}

	Matrix4f RotationMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation);
	}

	Matrix4f WorldToLocalMatrix() {
		return Matrix4f::GetRotationMatrix(BasicAttr.Rotation).Inversion() * Matrix4f::GetTranslationMatrix(BasicAttr.Position).Inversion();
	}
	Engine::ObservingPointer<GameObject> parentGameObject;
	Engine::ObservingPointer<GameObject> selfPointer;
	GameObject();
	~GameObject();
	GameObject(const GameObject &g) {
		this->equal(g);
	}
	void operator =(const GameObject &g) {
		this->equal(g);
	}

	//Interface
	virtual void Start() {}
	virtual void Update() {}

	virtual void OnCollisionEnter(Engine::ObservingPointer<GameObject> other) {}

	void UpdateConnectionPointer(Engine::ObservingPointer<GameObject> g);

	bool HasPhysicsComponent();
	bool HasRenderComponent();

	void NewPhysicsComponent();
	void NewRenderComponent();

	Status UpdatePhysicsComponent(PhysicsComponent p);
	Status UpdateRenderComponent(RenderComponent r);

	Engine::ObservingPointer<PhysicsComponent> GetPhysicsComponent();
	Engine::ObservingPointer<RenderComponent> GetRenderComponent();
	/*template<typename T>
	T GetComponent();*/
		
	GameObjectBasicAttr BasicAttr;

	Engine::OwningPointer<PhysicsComponent> physicsComponent;
	Engine::OwningPointer<RenderComponent> renderComponent;
	bool Active = true;
	bool willDelete = false;
	void Release();

	// TODO: Add collider
	// 2D_Collider: 5 Type
	// Box, Circle, Capsule, Edge, Polygon
	// 3D Collider: 3 Type
	// Cube, Sphere, Capsule

	void Decode(std::string decodingStr) {
		size_t pos = decodingStr.find(",");
		if (pos != -1) {
			decodingStr.substr(0, pos - 1);
		}
		
	}

	void AddForce(Vector3f force);

	Status LoadDataByLua(std::string filename) {
		lua_State *L = luaL_newstate();
		if (L == NULL)
		{
			return NullPointerError;
		}

		int bRet = luaL_loadfile(L, filename.c_str());
		if (bRet)
		{
			return BadError;
		}

		bRet = lua_pcall(L, 0, 0, 0);
		if (bRet)
		{
			return BadError;
		}

		if (lua_getglobal(L, "position"))
			this->BasicAttr.Position = LuaGetVector3f(L);

		if (lua_getglobal(L, "rotation"))
			this->BasicAttr.Rotation = LuaGetVector3f(L);

		if (lua_getglobal(L, "physics_component")) {
			this->NewPhysicsComponent();
			if (lua_getfield(L, -1, "velocity")) {
				this->physicsComponent->velocity = LuaGetVector3f(L);
				lua_pop(L, 1);
			}
			if (lua_getfield(L, -1, "mass")) {
				this->physicsComponent->Mass = lua_tonumber(L, -1);
				lua_pop(L, 1);
			}
			if (lua_getfield(L, -1, "dragcof")) {
				this->physicsComponent->DragCof = lua_tonumber(L, -1);;
				lua_pop(L, 1);
			}
			// TODO:
			// Add Collider
		}
		if (lua_getglobal(L, "render_component")) {
			this->NewRenderComponent();
			bool hasSize = false;
			Vector2f spriteSize(-1, -1);
			if (lua_getfield(L, -1, "size")) {
				hasSize = true;
				spriteSize = LuaGetVector2f(L);
				lua_pop(L, 1);
			}
			if (lua_getfield(L, -1, "spriteName")) {
				if (hasSize)
					this->renderComponent->CreateSprite(lua_tostring(L, -1), spriteSize.x, spriteSize.y);
				else
					this->renderComponent->CreateSprite(lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
		return NoError;
	}

	void SaveDataToLua(std::string filename) {

	}
	// TODO: 3D Collider
	// Sphere Collider, Cube Collider, Capsule Collider

private:
	void equal(const GameObject& g) {
		BasicAttr = g.BasicAttr;
		if (g.physicsComponent)
			physicsComponent = Engine::OwningPointer<PhysicsComponent>(*(g.physicsComponent));
		if (g.renderComponent)
			renderComponent = Engine::OwningPointer<RenderComponent>(*(g.renderComponent));

	}

	


	//Engine::OwningPointer<GameObject3DBasicAttr> attr;
	//
	//Engine::OwningPointer<PhysicsComponent> physics;
	//Engine::OwningPointer<RenderComponent> render;

	//
	//Vector3f DriveForceOnCurrentFrame = Vector3f(0, 0, 0);
	//
		
	//void UpdatePhysics(double i_dt, std::vector<Vector3f> addition_Forces = std::vector<Vector3f>());
};