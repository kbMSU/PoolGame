#pragma once

#include "state.h"

/**
 * @brief The Memento class - Used in the memento pattern for Stage 3
 */
class Memento
{
    // This class can only be instantiated by game
    friend class Game;
public:
    virtual ~Memento() {delete m_state;}
    State* getState() {return m_state;}
    void setState(State* state) {m_state = state;}
private:
    // No other class (except friends) can instantiate a memento
    Memento(State* state)
        :m_state(state) {}
private:
    // The state stored by this memento
    State* m_state = nullptr;
};
