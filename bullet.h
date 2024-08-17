#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"

class Bullet : public Sprite
{
public:
    // Bullet();
    using Sprite::Sprite;

    void update() override;
};

#endif // BULLET_H
