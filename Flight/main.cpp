#include "mainwindow.h"
#include <QApplication>
#include "Engine/Engine.h"

GameManager CurrentGameManager = GameManager();

class CollisionObject : public GameObject {
    void Update() {
        AddForce(Vector3f((float)(rand() % 300 - 150), (float)(rand() % 300 - 150), 0));
    }
};
DataStructure::List<Engine::ObservingPointer<CollisionObject>> collisionObjectList;
void AddCollisionObject(Vector3f position, int width, int height, std::string spriteName) {
    Engine::ObservingPointer<CollisionObject> ch2 = CurrentGameManager.AddGameObject(CollisionObject());
    ch2->BasicAttr.Position = position;
    ch2->NewPhysicsComponent();
    ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(width, height)));
    ch2->NewRenderComponent();
    ch2->renderComponent->CreateSprite(spriteName.c_str(), width, height);
    collisionObjectList.push(ch2);
    return;
}

int main(int argc, char *argv[])
{
    int screenHeight = 600;
    int screenWidth = 800;
    std::string collisionSpriteName = "data\\Block.dds";
    AddCollisionObject(Vector3f(0, (float)(-screenHeight)/ 2, 0), screenWidth, 30, collisionSpriteName);
    AddCollisionObject(Vector3f(0, (float)(screenHeight) / 2, 0), screenWidth, 30, collisionSpriteName);
    AddCollisionObject(Vector3f((float)(-screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);
    AddCollisionObject(Vector3f((float)(screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    CurrentGameManager.Run();
    return a.exec();
}
