#include "GameObject.h"
#include "GameManager.h"

extern GameManager CurrentGameManager;

GameObject::GameObject() {
	BasicAttr = Engine::OwningPointer<GameObject3DBasicAttr>(
		new GameObject3DBasicAttr()
		);
}
GameObject::~GameObject() {}

bool GameObject::HasPhysicsComponent() {
	return physicsComponent != nullptr;
}

bool GameObject::HasRenderComponent() {
	return renderComponent != nullptr;
}

void GameObject::NewPhysicsComponent() {
	// TODO: Finish the new function of Physics system

	//physicsComponent = Engine::OwningPointer<PhysicsComponent>(PhysicsComponent());
	/*ParentManager->Physics->AddRenderController(physicsComponent);*/
}

void GameObject::NewRenderComponent() {
	if (HasRenderComponent())
		return;
	renderComponent = Engine::OwningPointer<RenderComponent>(RenderComponent());
	renderComponent->ParentGameObject = selfPointer;
	CurrentGameManager.Render->AddRenderController(renderComponent);
	//renderComponent = ;
}

Status GameObject::AddPhysicsComponent(PhysicsComponent p) {
	if (HasPhysicsComponent())
		return Status(400, "Already has a component");
	physicsComponent = Engine::OwningPointer<PhysicsComponent>(&p);
	return NoError;
}

Status GameObject::AddRenderComponent(RenderComponent r) {
	if (HasRenderComponent())
		return Status(400, "Already has a component");
	renderComponent = Engine::OwningPointer<RenderComponent>(&r);
	return NoError;
}

Status GameObject::UpdatePhysicsComponent(PhysicsComponent p) {
	if (physicsComponent == nullptr)
		return NullPointerError;
	*physicsComponent = p;
	return NoError;
}
Status GameObject::UpdateRenderComponent(RenderComponent r) {
	if (renderComponent == nullptr)
		return NullPointerError;
	*renderComponent = r;
	return NoError;
}

Engine::ObservingPointer<PhysicsComponent> GameObject::GetPhysicsComponent() {
	return physicsComponent;
}

Engine::ObservingPointer<RenderComponent> GameObject::GetRenderComponent() {
	return renderComponent;
}

void GameObject::Release() {
	/*if (physicsComponent != nullptr)
		physicsComponent->Release();*/
	if (renderComponent != nullptr)
		renderComponent->Release();
}

void GameObject::UpdateConnectionPointer(Engine::ObservingPointer<GameObject> g) {
	selfPointer = g;
	if (renderComponent)
		renderComponent->ParentGameObject = g;
	if (physicsComponent)
		physicsComponent->ParentGameObject = g;
}


//void GameObject::CheckInput(unsigned int i_VKeyID) {
//	
//	char key = i_VKeyID;
//	switch (key)
//	{
//		case 'A':position.x = position.x - 20.f; DEBUG_LOG("A"); break;
//		case 'W':position.y = position.y + 20.f; DEBUG_LOG("W"); break;
//		case 'S':position.y = position.y - 20.f; DEBUG_LOG("S"); break;
//		case 'D':position.x = position.x + 20.f; DEBUG_LOG("D"); break;
//		case 'R':DriveForceOnCurrentFrame = Vector3f(10, 10, 0); DEBUG_LOG("r"); break;
//		default:
//			break;
//	}
//}
//void GameObject::CreateSprite(const char * i_pFilename)
//{
//	assert(i_pFilename);
//
//	size_t sizeTextureFile = 0;
//
//	// Load the source file (texture data)
//	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);
//
//	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
//	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;
//
//	// exit if something didn't work
//	// probably need some debug logging in here!!!!
//	if (pTextureFile)
//		delete[] pTextureFile;
//
//	if (pTexture == nullptr)
//		return;
//
//	unsigned int width = 0;
//	unsigned int height = 0;
//	unsigned int depth = 0;
//
//	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
//	bool result = GLib::GetDimensions(pTexture, width, height, depth);
//	assert(result == true);
//	assert((width > 0) && (height > 0));
//
//	// Define the sprite edges
//	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
//	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
//	GLib::RGBA							Color = { 255, 255, 255, 255 };
//
//	// Create the sprite
//	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
//	if (pSprite == nullptr)
//	{
//		GLib::Release(pTexture);
//		return;
//	}
//
//	// Bind the texture to sprite
//	GLib::Sprites::SetTexture(*pSprite, *pTexture);
//
//	irender = pSprite;
//}
//
//
//void * GameObject::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
//{
//	assert(i_pFilename != NULL);
//
//	FILE * pFile = NULL;
//
//	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
//	if (fopenError != 0)
//		return NULL;
//
//	assert(pFile != NULL);
//
//	int FileIOError = fseek(pFile, 0, SEEK_END);
//	assert(FileIOError == 0);
//
//	long FileSize = ftell(pFile);
//	assert(FileSize >= 0);
//
//	FileIOError = fseek(pFile, 0, SEEK_SET);
//	assert(FileIOError == 0);
//
//	uint8_t * pBuffer = new uint8_t[FileSize];
//	assert(pBuffer);
//
//	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
//	assert(FileRead == FileSize);
//
//	fclose(pFile);
//
//	o_sizeFile = FileSize;
//
//	return pBuffer;
//}
//
//void GameObject::UpdatePhysics(double i_dt, std::vector<Vector3f> addition_Forces) {
//	Vector3f totalForce(DriveForceOnCurrentFrame);
//	for (auto id = 0; id = addition_Forces.size(); id++) {
//		totalForce = totalForce + addition_Forces[id];
//	}
//	totalForce = totalForce + 。.normalized() * (-dragCof);
//	//DEBUG_LOG("%d %d", totalForce.x, totalForce.y);
//	Physcis::AddForce(*this, totalForce, i_dt);	
//	DriveForceOnCurrentFrame.Clear();
//}