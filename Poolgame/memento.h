#pragma once

#include "state.h"

class Memento
{
    friend class Game;
public:
    virtual ~Memento() {delete m_state;}
    State* getState() {return m_state;}
    void setState(State* state) {m_state = state;}
private:
    Memento(State* state)
        :m_state(state) {}
private:
    State* m_state = nullptr;
};
