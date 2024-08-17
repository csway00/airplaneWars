#include <QApplication>
#include "game.h"
#include "global.h"
#include "mainscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainScene m;
    m.show();

    // Game g;
    // g.run();
    // g.initGame(winWidth, winHight, "飞机大战");

    return a.exec();
}
