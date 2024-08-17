#ifndef ANIMATION_H
#define ANIMATION_H

#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QVector2D>
#include <QObject>
#include <qobjectdefs.h>
// QOBJECTDEFS_H

class Animation : public QObject
{
    Q_OBJECT
public:

    explicit Animation(QObject *parent = nullptr);

    Animation(int _speed = 500);
    //添加帧图
    void addFrame(const QString& filename);
    QPixmap getFrame(int index) const;
    qsizetype count() const;

    void update();
    void draw(QPainter* painter);
    inline void setPos(const QVector2D &pos) {
        xPos = pos.x();
        yPos = pos.y();
    }

    inline bool finished() {
        return index == count()-1;
    }

private:
    QList<QPixmap> pixmaps;
    int xPos = -100;
    int yPos = -100;
    int index = 0;

    int speed = 500;

    //void sendOverSig();

// public:

signals:
    void isOver();

};

#endif // ANIMATION_H
