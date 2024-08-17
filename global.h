#ifndef GLOBAL_H
#define GLOBAL_H
#include "game.h"

enum EntityType {
    ET_None,
    ET_Player,
    ET_Bullet,
    ET_Enemy,
    ET_EnemySmall,
    ET_EnemyMiddle,
    ET_EnemyBig
};

//480, 854
const int winWidth = 480;
const int winHight = 854;

//extern Game *g;
//static Game *g;

#endif // GLOBAL_H
