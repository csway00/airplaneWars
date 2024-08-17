#ifndef GRADE_H
#define GRADE_H
#include "entity.h"
#include <QQueue>

class Grade : public Entity
{
public:
    Grade(QQueue<int>& g);

    void update();
    void draw(QPainter* painter);

private:
    QQueue<int> grade;

};

#endif // GRADE_H
