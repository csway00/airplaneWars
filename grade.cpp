#include "grade.h"
#include <QDebug>
#include "global.h"

Grade::Grade(QQueue<int>& g) : grade(g) {}

void Grade::update()
{

}

void Grade::draw(QPainter *painter)
{
    QPixmap pixmap;

    //int x = this->width() - defeatedLbl->width() - 10;
    int x = 0;
    while (!grade.empty()) {
        int i = grade.front();
        qDebug() << i << "--------------------------=====================";
        pixmap.load(QString(":/Image/%1.png").arg(i));
        //defeatedLbl->setGeometry(QRect(this->width() - defeatedLbl->width() - 20, 15,400, 50)); //设 置大小和位置
        painter->drawPixmap(x, winHight - 15, 21, 26, pixmap);
        x += 26;
        grade.pop_front();
    }
}
