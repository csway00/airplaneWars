#include "animation.h"
#include <QElapsedTimer>
#include "game.h"

Animation::Animation(QObject *parent) : QObject{parent}
{

}

Animation::Animation(int _speed) :speed(_speed) {}

void Animation::addFrame(const QString &filename)
{
    pixmaps.append(QPixmap(filename));
}

QPixmap Animation::getFrame(int index) const
{
    return pixmaps[index];
}

qsizetype Animation::count() const
{
    return pixmaps.count();
}

void Animation::update()
{
    // index++;
    // index = index % pixmaps.count();
    index = Game::globalElapsedTimer.elapsed() / speed % this->count();
}

void Animation::draw(QPainter *painter)
{
    painter->drawPixmap(xPos, yPos, pixmaps[index]);
}

// void Animation::sendOverSig()
// {
//     if (index == this->count()-1) {
//         emit this->isWindowType();
//     }
// }
