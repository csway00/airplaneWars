#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "sprite.h"

class EnemyPlane : public Sprite
{
public:
    // EnemyPlane();
    using Sprite::Sprite;
    void update() override;

    inline void setEnemyType(int type) {mType = type;}
private:
    bool active = true;  //实体是否是活动的  //在这个编译器中, bool默认值为false;
    int mType = 0; //
};

#endif // ENEMYPLANE_H
