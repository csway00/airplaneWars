#ifndef MAP_H
#define MAP_H

#include "entity.h"
#include <QPixmap>

class Map : public Entity
{
public:
    Map();

    void update();
    void draw(QPainter* painter);

private:
    QPixmap pixmap;
    int yPos1;
    int yPos2;
    int speed = 2;

};

#endif // MAP_H
