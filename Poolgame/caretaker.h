#pragma once

#include <vector>
#include <QKeyEvent>

#include "game.h"
#include "memento.h"
#include "observer.h"

class Caretaker : public Observer
{
public:
    Caretaker(Game* game);
    virtual ~Caretaker();
    Game* getGame() {return m_game;}
    void processKeyRelease(QKeyEvent *event);
public:
    virtual void Notify(std::unique_ptr<Notification> n) override;
private:
    void rewind();
    void fastforward();
    void save();
private:
    Game* m_game;
    std::vector<std::unique_ptr<Memento>> m_savedStates;
    int m_currentStateIndex = -1;
};

