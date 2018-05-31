#pragma once

#include <vector>

#include "game.h"
#include "memento.h"

class Caretaker
{
public:
    Caretaker(Game* game);
    virtual ~Caretaker();
    Game* getGame() {return m_game;}
private:
    void rewind();
    void fastforward();
    void save();
private:
    Game* m_game;
    std::vector<Memento*> m_savedStates;
    int m_currentStateIndex = -1;
};

