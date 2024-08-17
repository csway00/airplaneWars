#include "enemyplane.h"
#include "game.h"

// EnemyPlane::EnemyPlane() {}

void EnemyPlane::update()
{
    if (this->position.y() > Game::mHeight) {
        this->destroy();
    }
    Sprite::update();
}
