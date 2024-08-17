#include "mainscene.h"
#include "global.h"
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include "global.h"
#include "game.h"
#include "Manager.h"


Game *g;

MainScene::MainScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(winWidth, winHight);
    // this->setWindowTitle("飞机大战");
    // this->setWindowIcon(QIcon(":/Image/icon.png"));

    this->setWindowFlag(Qt::FramelessWindowHint); //隐藏边框

    MyPushButton *quitBtn = new MyPushButton(":/Image/text_quit_01.png");
    quitBtn->setParent(this);
    quitBtn->move(this->width() * 0.68, this->height()*0.92);

    //退出程序
    connect(quitBtn, &MyPushButton::clicked, this, &MainScene::close);

    //右键, 退出程序
    mExitMenu = new QMenu(this);
    QAction* mExitAct = new QAction();

    mExitAct->setText(tr("退出"));
    mExitMenu->addAction(mExitAct);

    connect(mExitAct, &QAction::triggered, this, [=]() {
        qApp->exit(0);  //qApp为全局指针
    });

    /*g = new Game*/;

    //播放音乐
    backSound = new QSound(":/sound/game_music.wav");
    backSound->setLoops(-1); // 无限循环
    backSound->play();

    connect(g, &Game::gameOver, backSound, &QSound::stop);  //游戏结束后, 停止播放背景音乐
    connect(g, &Game::gameOver, this, [=]() {
        backSound->stop();
        qDebug() << "mainscene 音乐停止";
    });  //游戏结束后, 停止播放背景音乐

    //玩家正常
//    auto anima = play->addAnimation("normal", new Animation(500));

    //s = new Sprite;
    // s = new Sprite(0, 0, ":/Image/loading_01.png");

    // //s = MGR->addEntity(new PlayerPlane(0, this->height() - 40, ":/Image/F1_01.png"));
    // loadAnima = s->addAnimation("load", new Animation(100));  //new Animation(speed), speed越小越快
    // for (int i = 0; i < 3; i++) {
    //     //   playBoom->addFrame(QString(":/Image/F1_0%1.png").arg(i));
    //     loadAnima->addFrame(QString(":/Image/loading_0%1.png").arg(i));
    // }
    // // anima->addFrame(":/Image/F1_01.png");
    // // anima->addFrame(":/Image/F1_02.png");
    // // // play->runAnimation("normal", false);
    // // play->runAnimation("normal");

    // s->runAnimation("load", true); //true为:只播放一遍
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPixmap pixmap;
    pixmap.load(":/Image/Blackground_MeeGo.png");

    QPainter painter(this);

    painter.drawPixmap(0, 0, this->width(),this->height(), pixmap);

    pixmap.load(":/Image/LOGO.png");
    painter.drawPixmap(this->width() / 2 - pixmap.width() / 2, this->height() * 0.2, pixmap);

    pixmap.load(":/Image/text_dblclick.png");
    pixmap = pixmap.scaled(pixmap.width()*1.6, pixmap.height()* 1.6);  //设置显示大小, 单位: 像素
    painter.drawPixmap(this->width() / 2 - pixmap.width() / 2, this->height() * 0.8, pixmap);

    pixmap.load(":/Image/button_2_1.png");
    painter.drawPixmap(this->width() * 0.68, this->height()*0.92, pixmap);

}

void MainScene::contextMenuEvent(QContextMenuEvent *ev)
{
    mExitMenu->exec(QCursor::pos());

    //调用accept 表示，这个事件我己经处理，不需要向上传递了
    ev->accept();
}

void MainScene::mouseDoubleClickEvent(QMouseEvent *event)
{
    connect(g, &Game::gameOver, this, [=]() {
        backSound->stop();
        qDebug() << "mainscene 音乐停止";
    });  //游戏结束后, 停止播放背景音乐
    //this->hide();
    // Game g;
    // //g.setGeometry(this->geometry());
    // g.show();
    // g.run();
    // g.initGame(winWidth, winHight, "飞机大战");

    //Game* g = new Game;
    g = new Game;
    g->run();
    g->initGame(winWidth, winHight, "飞机大战");
    g->setGeometry(this->geometry());
    //g->setGeometry(0, 0, 480, 852);

    backSound->stop();

}

