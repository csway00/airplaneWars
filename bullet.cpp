#include "bullet.h"

// Bullet::Bullet() {}

void Bullet::update()
{
    if (this->position.y() + getHight() < 0) {
        this->destroy();
    }
    Sprite::update();
}
