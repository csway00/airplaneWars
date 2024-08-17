#ifndef SPRITE_H
#define SPRITE_H
#include "entity.h"
#include <QVector2D>
#include <QRect>
#include "animation.h"
#include <QMap>
#include <QObject>

class Sprite : public QObject, public Entity
{
    Q_OBJECT
public:
    Sprite();
    ~Sprite();
    Sprite(int x, int y, const QString& imagePath);

    virtual void update();
    virtual void draw(QPainter* painter);

    void moveBy(int dx, int dy);

    QVector2D velocity;

    inline int getWith() const {return pixmap.width();}
    inline int getHight() const {return pixmap.height();}

public:
    QVector2D position;

    inline void setSpeed(int _speed) {speed = _speed;}

    QRect collider;

private:
    QPixmap pixmap;

    int speed = 3;

private:
    QMap<QString, Animation*> animas;
    // Animation* currAnima /*= nullptr*/;
    Animation* currAnima = nullptr;

public:
    Animation* addAnimation(const QString& tag, Animation* anim);
    void runAnimation(const QString& tag, bool autoDel = false); //autoDel: 是否只播放一遍

private:
    bool autoDel = false;
};

#endif // SPRITE_H
