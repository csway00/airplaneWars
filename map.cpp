#include "map.h"
#include "game.h"
#include <QDebug>

Map::Map() {
    yPos1 = -Game::mHeight;
    yPos2 = 0;
    pixmap.load(":/Image/Blackground_MeeGo.png");

    //qDebug() << "map.cpp中: 宽度:" << Game::mWidth << ", 高度:" << Game::mHeight;
}

void Map::update()
{

    yPos1 += speed;
    if (yPos1 == 0) {
        yPos1 = -Game::mHeight;
    }
    yPos2 = (yPos2 + speed) % Game::mHeight;
    //qDebug() << "map.cpp中: yPos1 = " << yPos1 << ", yPos2 = " << yPos2;
}

void Map::draw(QPainter *painter)
{
    painter->drawPixmap(0, yPos1, pixmap);
    painter->drawPixmap(0, yPos2, pixmap);
}
