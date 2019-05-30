#include "QTRender/mainwindow.h"
#include <QApplication>
#include "Engine/Engine.h"
#include "QTRender/qtrendercomponent.h"
#include "QTRender/qtrendercontroller.h"

extern GameManager CurrentGameManager = GameManager();

class CollisionObject : public GameObject {
    void Update() {
        AddForce(Vector3f((float)(rand() % 300 - 150), (float)(rand() % 300 - 150), 0));
    }
};
static DataStructure::List<Engine::ObservingPointer<CollisionObject>> collisionObjectList;



void AddCollisionObject(Vector3f position, int width, int height, std::string spriteName) {
    Engine::ObservingPointer<CollisionObject> ch2 = CurrentGameManager.AddGameObject(CollisionObject());
    ch2->BasicAttr.Position = position;
    ch2->NewPhysicsComponent();
    ch2->physicsComponent->AddCollider(BoxCollider2D(Vector2f(0, 0), Vector2f(width, height)));
    QTRenderComponent qtComp;
    ch2->AddRenderComponent(qtComp);
    auto renderPtr = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ch2->renderComponent);
    renderPtr->CreateSprite(spriteName.c_str());
    renderPtr->SetSize(width, height);
    collisionObjectList.push(ch2);
    return;
}

int main(int argc, char *argv[])
{
    int screenHeight = 600;
    int screenWidth = 800;
    QApplication app(argc, argv);

    qDebug() << "start";
    CurrentGameManager.Initialization();
    QTRenderController qtController(&app);
    CurrentGameManager.AddRenderController(&qtController);
    qtController.test();


    QSurfaceFormat format;
    format.setSamples(16);

    CurrentGameManager.Render->Start();
    CurrentGameManager.Render->test();
    //reinterpret_cast<Engine::OwningPointer<QTRenderController>>(CurrentGameManager.Render);
    qDebug() << "Expoes: " << qtController.isExposed();
    std::string collisionSpriteName = "C:/Users/plutoshe/Downloads/1.jpg";
    AddCollisionObject(Vector3f(0, (float)(-screenHeight)/ 2, 0), screenWidth, 30, collisionSpriteName);
//    AddCollisionObject(Vector3f(0, (float)(screenHeight) / 2, 0), screenWidth, 30, collisionSpriteName);
//    AddCollisionObject(Vector3f((float)(-screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);
//    AddCollisionObject(Vector3f((float)(screenWidth) / 2, 0, 0), 30, screenHeight, collisionSpriteName);

    qDebug() << "phase 1";
    //CurrentGameManager.Run();
    return app.exec();
}
