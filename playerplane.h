#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "sprite.h"

class PlayerPlane : public Sprite
{
public:
    //PlayerPlane();
    using Sprite::Sprite;
    void fire();
};

#endif // PLAYERPLANE_H
