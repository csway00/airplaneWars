

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "sprite.h"
#include "Manager.h"
#include "map.h"
#include "playerplane.h"
#include <QElapsedTimer>
#include "enemyplane.h"
#include "animation.h"
#include "mainscene.h"
#include <QMenu>
#include <QSound>
#include <QLabel>
#include <QQueue>
#include "grade.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);

    //1. 运行游戏
    void run();

    //2. 初始化游戏
    void initGame(int with, int hight, const QString& title);

    //3. 清理游戏
    void clearGame();

    //4. 更新游戏
    void updateGame();

    //5. 绘制游戏
    void drawGame(QPainter* painter);

protected:
    void paintEvent(QPaintEvent* ev);
    void closeEvent(QCloseEvent* ev);

    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);

private:
    PlayerPlane *play;
    //Manager mgr;

    Map* map;  /*因为Manager类的容器时set, 会根据指针的大小排序,
所以背景可能先绘制, 也可能后绘制, 后绘制就会覆盖其他图片*/

public:
    inline static int mWidth = 0;
    inline static int mHeight = 0;
    inline static QElapsedTimer globalElapsedTimer;

private:
    void enemyAppearance();

public:
    void gameRunAnimation();

    void isReplay();

    void contextMenuEvent(QContextMenuEvent *ev);
private:
    Animation* playBoom;
    QMenu* mExitMenu;

private:
    QSound* flye;
    QSound* enemyDown;
    QSound* gameOverSound;

private:
    int defeatedCnt = 0;
    QLabel *defeatedLbl;
    void updateDefeatedLbl();
    QQueue<int> defeatedDigit;
    // Grade *grade;

signals:
    void gameOver();
};

#endif // GAME_H
