/*
 * 在游戏界面添加一个齿轮的设置按钮, 里面有: 暂停, 继续, 退出游戏, 调节音量大小, 重玩...
*/

#include "game.h"
#include <QDebug>
#include <QTimer>
#include "map.h"
#include "enemyplane.h"
#include <QRandomGenerator>
#include "bullet.h"
#include "global.h"
#include <QMessageBox>
#include <QApplication>

#define RAND_BOUND(X) QRandomGenerator::global()->bounded(X)

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=]() {
        //更新数据
        this->updateGame();

        //绘图
        update();
    });

    timer->start(1000/60);  //60帧

    this->setWindowFlag(Qt::FramelessWindowHint); //隐藏边框

    //右键, 退出程序
    mExitMenu = new QMenu(this);
    QAction* mExitAct = new QAction();

    mExitAct->setText(tr("退出"));
    mExitMenu->addAction(mExitAct);

    connect(mExitAct, &QAction::triggered, this, [=]() {
        qApp->exit(0);  //qApp为全局指针
    });

    //play = new play(0, 0, "F:\\Desktop\\pictureSrc\\fork.jpg");

    //给Manager类的容器插入元素:entities
    //play = (Sprite*)mgr.addEntity(new Sprite(0, 0, "F:\\Desktop\\pictureSrc\\fork.jpg"));
    //play = mgr.addEntity(new Sprite(0, 0, ":/Image/Bomb.png"));

    //auto paly2 = mgr.addEntity(new Sprite(200, 0, ":/Image/F2_01.png"));
}


void Game::run()
{
    this->show();
}

void Game::initGame(int with, int hight, const QString &title)
{
    globalElapsedTimer.start();
    this->setFixedSize(with, hight);
    this->setWindowTitle(title);

    mWidth = with;
    mHeight = hight;
    // qDebug() << "game.cpp中: 宽度:" << Game::mWidth << ", 高度:" << Game::mHeight;
    //mgr.addEntity(new Map);
    map = new Map;
    // play = MGR->addEntity(new Sprite(0, 0, ":/Image/F1_01.png"));
    play = MGR->addEntity(new PlayerPlane(0, this->height() - 40, ":/Image/F1_01.png"));
    play->setType(EntityType::ET_Player); //setType

    this->gameRunAnimation();

    //播放音乐
    flye = new QSound(":/sound/flying.wav");
    flye->setLoops(-1); // 无限循环
    flye->play();

    enemyDown = new QSound(":/sound/enemy1_down.wav");

    gameOverSound = new QSound(":/sound/game_over.wav");

    defeatedLbl = new QLabel(this);
    // defeatedLbl->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    defeatedLbl->setFont(font);

    //this->updateDefeatedLbl();
}

void Game::clearGame()
{
    delete MGR;
    delete map;
}

void Game::updateGame()
{
    //qDebug() << __FUNCTION__;
    MGR->refersh();
    map->update();
    MGR->update();


    //限制飞机飞行
    if (play->position.x() + play->getWith()/2 < 0) {
        play->position.setX(-play->getWith()/2);
    } else if (play->position.x() + play->getWith()/2 > mWidth) {
        play->position.setX(mWidth - play->getWith()/2);
    } else if (play->position.y() < 0) {
        play->position.setY(0);
    } else if (play->position.y() + play->getHight() > mHeight) {
        play->position.setY(mHeight - play->getHight());
    } else if (play->position.x() < 0 && play->position.y() < 0) {
        play->position.setX(0);
        play->position.setY(0);
    }

    //控制子弹打出的个数
    static int i = 0;
    if (i % 30 == 0) {
        play->fire();
    }


    //敌机出场
    if (i % 60 == 0) {
        this->enemyAppearance();
    }

    //碰撞检测
    for (auto& e : MGR->getEntityByType<EnemyPlane>(EntityType:: ET_Enemy)) {
        //敌机与子弹碰撞:
        bool isDie = false;
        for (auto& b : MGR->getEntityByType<Bullet>(EntityType::ET_Bullet)) {
            if (e->collider.intersects(b->collider)) {
                e->destroy();
                enemyDown->play();
                //play->runAnimation("enemyBoom", true);
                b->destroy();
                //play->runAnimation("bulletBoom");
                isDie = true;
                this->defeatedCnt++;
                this->updateDefeatedLbl();
                break;
            }
        }

        //敌机与玩家的飞机碰撞:
        if (!isDie && e->collider.intersects(play->collider)) {
            e->destroy();
            play->runAnimation("boom", true);
            emit this->gameOver();  //发送游戏结束信号;
            flye->stop();
            gameOverSound->play();

            connect(playBoom, &Animation::isOver, this, &Game::isReplay);
            //this->isReplay(); //游戏结束, 选择是否重玩
        }
    }

    qDebug() << "对象个数: " <<MGR->count();  //答应Manager中set中对象的个数;
    i++;
}

void Game::drawGame(QPainter *painter)
{
    //qDebug() << __FUNCTION__;
    if (map == nullptr) {
        // qDebug() << "在Game中, map是空指针";
        // return;
        map = new Map;
    }
    map->draw(painter);
    MGR->draw(painter);

    // if (!grade) {
    //     grade = new Grade(defeatedDigit);
    // }
    // grade->draw(painter);


//     QPixmap pixmap;
//     int x = this->width() - defeatedLbl->width() - 10;
//     qDebug() << defeatedDigit.front() << "=============-=-=-=-==--==-=-=-=";

//     while (!defeatedDigit.empty()) {
//         int i = defeatedDigit.front();
//         qDebug() << i << "--------------------------=====================";
//         pixmap.load(QString(":/Image/%1.png").arg(i));
//         //defeatedLbl->setGeometry(QRect(this->width() - defeatedLbl->width() - 20, 15,400, 50)); //设 置大小和位置
//         painter->drawPixmap(x, 15, 21, 26, pixmap);
//         x += 26;
//         defeatedDigit.pop_front();
//     }

}

void Game::paintEvent(QPaintEvent *ev)
{
    QPainter* painter = new QPainter(this);
    this->drawGame(painter);

    QPixmap pixmap;

    pixmap.load(":/Image/text_score.png");
    painter->drawPixmap(20, 10, 395, 71, pixmap);

    int x = 335;
    for (const auto&d : defeatedDigit) {
        pixmap.load(QString(":/Image/%1.png").arg(d));
        //defeatedLbl->setGeometry(QRect(this->width() - defeatedLbl->width() - 20, 15,400, 50)); //设 置大小和位置
        painter->drawPixmap(x, 35, 21, 26, pixmap);
        x += 26;
    }
}

void Game::closeEvent(QCloseEvent *ev)
{
    this->clearGame();
}

void Game::keyPressEvent(QKeyEvent *ev)
{
    if (play == nullptr) {
        qDebug() << "play是空指针";
        return;
    }
    switch(ev->key()) {
    case Qt::Key_Up :
        //sprite->moveBy(0, -1);
        play->velocity.setY(-1);
        break;
    case Qt::Key_Down :
        // sprite->moveBy(0, 1);
        play->velocity.setY(1);
        break;
    case Qt::Key_Left :
        // play->moveBy(-1, 0);
        play->velocity.setX(-1);
        break;
    case Qt::Key_Right :
        // play->moveBy(1, 0);
        play->velocity.setX(1);
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    if (play == nullptr) {
        qDebug() << "play是空指针";
        return;
    }
    switch(ev->key()) {
    case Qt::Key_Up :
        //play->moveBy(0, -1);
        play->velocity.setY(0);
        break;
    case Qt::Key_Down :
        // play->moveBy(0, 1);
        play->velocity.setY(0);
        break;
    case Qt::Key_Left :
        // play->moveBy(-1, 0);
        play->velocity.setX(0);
        break;
    case Qt::Key_Right :
        // play->moveBy(1, 0);
        play->velocity.setX(0);
        break;
    }
}

void Game::enemyAppearance()
{
    QStringList enemyAirplanes= {":/Image/F2_01.png",
                   ":/Image/F3_01.png",
                   ":/Image/F4_01.png"};
    int rand = RAND_BOUND(3);
    auto enemy =  MGR->addEntity(new EnemyPlane(
        0, 0, enemyAirplanes[rand]));
    enemy->moveBy(RAND_BOUND(Game::mWidth - enemy->getWith()), -enemy->getHight());
    enemy->velocity.setY(1);

    switch(rand) {
    case 0:
        enemy->setEnemyType(EntityType::ET_EnemySmall);
        break;
    case 1:
        enemy->setEnemyType(EntityType::ET_EnemyMiddle);
        break;
    case 2:
        enemy->setEnemyType(EntityType::ET_EnemyBig);
        break;
    }
    enemy->setType(EntityType::ET_Enemy); //setType
}

void Game::gameRunAnimation()
{
    //玩家正常
    auto anima = play->addAnimation("normal", new Animation(500));
    anima->addFrame(":/Image/F1_01.png");
    anima->addFrame(":/Image/F1_02.png");
    // play->runAnimation("normal", false);
    play->runAnimation("normal");

    //玩家爆炸
    playBoom = play->addAnimation("boom", new Animation(200));
    for (int i = 3; i <= 5; i++) {
        playBoom->addFrame(QString(":/Image/F1_0%1.png").arg(i));
    }
    playBoom->addFrame(QString(":/Image/F3_06.png"));

    //子弹爆炸
    // auto bulletAnima = play->addAnimation("bulletBoom", new Animation);
    // bulletAnima->addFrame(":/Image/Bullets_01.png");
    // bulletAnima->addFrame(":/Image/Bullets_03.png");

    // //敌机爆炸
    // auto enemyBoom = play->addAnimation("enemyBoom", new Animation(200));
    // for (int i = 1; i <= 5; i++) {
    //     playBoom->addFrame(QString(":/Image/F2_0%1.png").arg(i));
    // }
}

void Game::isReplay()
{
    QMessageBox::information(this, "游戏结束", QString("歼灭敌机数:%1").arg(defeatedCnt));
    play->destroy();
    this->clearGame();
    //close();
    qApp->exit(0);  //qApp为全局指针

    // QMessageBox msgBox;
    // msgBox.setText(tr("游戏结束"));
    // //msgBox.setInformativeText(tr("Do you want to replay?"));
    // //msgBox.setDetailedText(tr("Differences here..."));
    // msgBox.setStandardButtons(QMessageBox::Yes
    //                           | QMessageBox::No
    //                           | QMessageBox::Close);

    // msgBox.setDefaultButton(QMessageBox::Yes);
    // int ret = msgBox.exec();
    // switch (ret)
    // {case QMessageBox::Yes: {
    //     // qDebug() << "Save document!";
    //     //this->hide();
    //     // this->clearGame();
    //     // g->deleteLater();
    //     // g = nullptr;
    //     // g = new Game;
    //     // g->initGame(winWidth, winHight, "飞机大战");
    //     // g->setGeometry(this->geometry());
    //     // g->run();
    //     //this->clearGame();
    //     this->hide();

    //     MainScene *m = new MainScene;
    //     m->setGeometry(this->geometry());
    //     m->show();

    //     //this->close();
    //     break;
    // } case QMessageBox::No: {
    //     qDebug() << "Discard changes!";
    //     break;
    // } case QMessageBox::Close: {
    //     qDebug() << "Close document!";
    //     play->destroy();
    //     close();
    //     break; }
    // }
}

void Game::contextMenuEvent(QContextMenuEvent *ev)
{
    mExitMenu->exec(QCursor::pos());

    //调用accept 表示，这个事件我己经处理，不需要向上传递了
    ev->accept();
}

void Game::updateDefeatedLbl()
{
    //QString str = QString("歼灭敌机数: %1").arg(this->defeatedCnt);

    //数位分离
    defeatedDigit.clear();
    int x = defeatedCnt;
    while (x) {
        defeatedDigit.push_front(x % 10);
        x /= 10;
    }
    //qDebug() << "str = " << str;
    // defeatedLbl->setText(str);
    // defeatedLbl->setGeometry(QRect(this->width() - defeatedLbl->width() - 20, 15,400, 50)); //设 置大小和位置
    // defeatedLbl->show();
}
