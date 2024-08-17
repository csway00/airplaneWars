#include "playerplane.h"
#include "Manager.h"
#include "bullet.h"
#include "global.h"
#include <QSound>

//PlayerPlane::PlayerPlane() {}

void PlayerPlane::fire()
{
    auto b = MGR->addEntity(new Bullet(position.x() + getWith() / 5, position.y(), ":/Image/Bullets_01.png"));
    b->setSpeed(6);  //setSpeed //设置子弹的速度
    b->setType(EntityType::ET_Bullet); //setType
    b->velocity.setY(-1);
    QSound* bulletSound = new QSound(":/sound/bullet.wav");
    bulletSound->play();
}
