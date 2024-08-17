#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>

class Entity {
public:
    Entity(){}
    virtual ~Entity(){}
    virtual void update() = 0;
    virtual void draw(QPainter* painter) = 0;

    inline bool isActive() const {return active;}
    inline void destroy() {active = false;}

    inline int type() const {return mType;}
    inline void setType(int type) {mType = type;}

private:
    bool active = true;  //实体是否是活动的  //在这个编译器中, bool默认值为false;
    int mType = 0; //实体的类型
};

#endif // ENTITY_H
