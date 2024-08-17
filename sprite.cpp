#include "sprite.h"
#include <QDebug>

Sprite::Sprite() {}

Sprite::~Sprite()
{
    for (auto& a : animas) {
        delete a;
    }
}

Sprite::Sprite(int x, int y, const QString &imagePath) : position(x, y)
{
    pixmap.load(imagePath);
}

void Sprite::update()
{
    // position += QVector2D(1, 1);
    position += speed * velocity;

    collider = QRect(position.toPoint(), pixmap.size());

    if (currAnima) {
        currAnima->update();
        currAnima->setPos(position);
        if (autoDel && currAnima->finished()) {
            destroy();
            emit currAnima->isOver();
            qDebug() << "已经结束了";
        }
    }
}

void Sprite::draw(QPainter *painter)
{
    //painter->drawPixmap(position.toPoint(), pixmap.scaled(75, 75));
    if (!currAnima)
        painter->drawPixmap(position.toPoint(), pixmap);
    else
        currAnima->draw(painter);
}

void Sprite::moveBy(int dx, int dy)
{
    position += QVector2D(dx, dy);
}

Animation *Sprite::addAnimation(const QString &tag, Animation *anim)
{
    if (!anim) {
        qWarning() << "anima is nullptr";
        return nullptr;
    }
    if (animas.contains(tag)) {
        qWarning() << "tag已经存在";
        return anim;
    }
    animas.insert(tag, anim);
    return anim;
}

void Sprite::runAnimation(const QString &tag, bool autoDel)
{
    this->autoDel = autoDel;
    if (!animas.contains(tag)) {
        qWarning() << "tag不存在";
        return;
    }
    // currAnima = new Animation;
    currAnima = animas.value(tag);
}
