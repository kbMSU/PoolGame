#pragma once

#include "ball.h"
#include "table.h"
#include "balldecorator.h"

#include <iostream>
#include <vector>
#include <QMouseEvent>


class State
{
public:
    State() {}
    virtual ~State() {}
    virtual State* Duplicate() = 0;
    virtual void UpdateState(State* state) = 0;
};

class GameState : public State
{
public:
    GameState(std::vector<Ball*>* balls, Table* table, int stage)
        :State(),m_balls(balls),m_table(table),m_stage(stage) {}
    GameState(GameState& state);

    virtual State* Duplicate() override { return new GameState(*this); }

    virtual ~GameState() {clearState();}

    std::vector<Ball*>* getBalls() {return m_balls;}
    Table* getTable() {return m_table;}
    int getStage() {return m_stage;}
    MouseEventable::EventQueue& getEventFns() {return m_mouseEventFunctions;}

    /**
     * @brief addMouseFunctions - append all of the specified functions to be
     *  our eventqueue - these will be cycled through onclick, etc
     * @param fns
     */
    void addMouseFunctions(MouseEventable::EventQueue fns) {
        std::copy(fns.begin(), fns.end(), std::back_inserter(m_mouseEventFunctions));
    }

    virtual void UpdateState(State* state) override;
private:
    void clearState() {
        delete m_table;
        for (Ball* b : *m_balls) delete b;
        delete m_balls;
    }
private:
    std::vector<Ball*>* m_balls;
    Table* m_table;
    // store the functions that get scanned through whenever a mouse event happens
    MouseEventable::EventQueue m_mouseEventFunctions;
    int m_stage;
};
