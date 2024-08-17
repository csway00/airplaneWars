#ifndef MANAGER_H
#define MANAGER_H

#include "entity.h"
#include <QSet>
#include <QDebug>
#define MGR Manager::getInstance()

class Manager {
public:
    //获取管理的单例
    static Manager* getInstance() {
        static Manager* ins = nullptr;
        if (!ins) {
            ins = new Manager;
        }
        return ins;
    }

    //Entity* addEntity(Entity* e) {
    template<typename T>
    T* addEntity(T* e) {
        entities.insert(e);
        return e;
    }

    void update() {
        for (auto& e : entities) {
            e->update();
        }
    }

    void draw(QPainter* painter) {
        for (auto& e : entities) {
            e->draw(painter);
        }
    }

    qsizetype count() const {return entities.size();}

    void refersh() {
        // qDebug() << "Manager count : " << count();
        //bool QSet::remove(const T &value)
        for (auto& e : entities) {
            // qDebug() << "manager delete set object:" << e->type();
            if (!e->isActive()) {
                entities.remove(e);
                delete e;
                //e = nullptr;
            }
        }
    }

    template<typename T>
    QSet<T*> getEntityByType(int type_) {
        QSet<T*> set;
        for (auto& e : entities) {
            if (e->type() == type_) {
                set.insert(static_cast<T*>(e));
            }
        }
        return set;
    }

    // template<typename T>
    // QSet<T*> getEntityByTypeName() {
    //     QSet<T*> set;
    //     for (auto& e : entities) {
    //         if (typeid(T).hash_code() == typeid(e).hash_code()) {
    //             set.insert(static_cast<T*>(e));
    //         }
    //     }
    //     return set;
    // }

    // void refersh() {  //这里的Qt版本不支持removeIf();
    //     entities.removeIf([](Entity* e) {
    //         if (!e->isActive()) {
    //             qDebug() << "Manager destory" << e->type();
    //             delete e;
    //             return true;
    //         }
    //         return false;
    //     });
    // }

private:
    QSet<Entity*> entities;
    Manager() {}
};


#endif // MANAGER_H
