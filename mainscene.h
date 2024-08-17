#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QSound>
#include "animation.h"
#include "sprite.h"

// class Game;
class MainScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainScene(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *ev);

    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QMenu* mExitMenu;


    /*F:\Desktop\QTCode\smallProject\airplaneWars\mainscene.h:22: error: 'Game' does not name a type
In file included from ..\..\game.h:16,
                 from ..\..\animation.cpp:3:
..\..\mainscene.h:22:5: error: 'Game' does not name a type
   22 |     Game *g;
      |     ^~~~*/

public:
    QSound *backSound;
    //static QSound *backSound = new QSound(":/sound/game_music.wav");

private:
    Animation* loadAnima;
    Sprite* s;

signals:

};

// backSound =

#endif // MAINSCENE_H

