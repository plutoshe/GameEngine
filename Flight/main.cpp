#include "QTRender/mainwindow.h"
#include <QApplication>
#include "Engine/Engine.h"
#include "QTRender/qtrendercomponent.h"
#include "QTRender/qtrendercontroller.h"

class CollisionObject : public GameObject {
public:
    CollisionObject() : GameObject() {}
    void Update() {
        AddForce(Vector3f((float)(rand() % 300 - 150), (float)(rand() % 300 - 150), 0));
    }
};
static DataStructure::List<Engine::ObservingPointer<CollisionObject>> collisionObjectList;



void AddCollisionObject(Vector3f position, int width, int height, std::string spriteName) {
    qDebug() << "add 1";
    Engine::ObservingPointer<CollisionObject> ch2 = GameManager::Instance->AddGameObject(Engine::OwningPointer<CollisionObject>(new CollisionObject()));
    ch2->BasicAttr.Position = position;
    ch2->NewPhysicsComponent();
    ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(width, height)));
    QTRenderComponent *qtComp = new QTRenderComponent();
    ch2->AddRenderComponent(qtComp);
    auto renderPtr = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ch2->renderComponent);
    renderPtr->CreateSprite(spriteName.c_str());
    renderPtr->SetSize(width, height);
    collisionObjectList.push(ch2);
    qDebug() << "add 2";
    return;
}

int main(int argc, char *argv[])
{
    // TODO: optimize qt render add way, make gamemanager as virtual class, and implement a qt game project based
    // on this game manager, and embed these render initializaton into game manager's initialization.
    // CurrentGameManager.Initialization();
    GameManager::CreateNewManager();

    QApplication app(argc, argv);
    QTRenderController *qtController = new QTRenderController(&app);
    qtController->screenHeight = 600;
    qtController->screenWidth = 800;
    GameManager::Instance->AddRenderController(qtController);
    GameManager::Instance->Initialization();

#ifdef __APPLE__
    std::string collisionSpriteName = "/Users/plutoshe/Downloads/1.jpg";
#endif
#ifdef __MINGW32__
    std::string collisionSpriteName = "C:/Users/plutoshe/Downloads/1.jpg";
#endif
    AddCollisionObject(Vector3f(0, (float)(-qtController->screenHeight)/ 2, 0), qtController->screenWidth, 30, collisionSpriteName);
    AddCollisionObject(Vector3f(0, (float)(qtController->screenHeight) / 2, 0), qtController->screenWidth, 30, collisionSpriteName);
    AddCollisionObject(Vector3f((float)(-qtController->screenWidth) / 2, 0, 0), 30, qtController->screenHeight, collisionSpriteName);
    AddCollisionObject(Vector3f((float)(qtController->screenWidth) / 2, 0, 0), 30, qtController->screenHeight, collisionSpriteName);
    //GameManager::Instance->Run();
    qtController->CreateAWindow();
    app.processEvents();
    GameManager::Instance->Run();
    return app.exec();
}
