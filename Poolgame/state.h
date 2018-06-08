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
    virtual std::string ExportState() = 0;
};

class GameState : public State
{
public:
    GameState(std::vector<Ball*>* balls, Table* table)
        :State(),m_balls(balls),m_table(table) {}
    GameState(GameState& state);
    virtual ~GameState() {clearState();}

    virtual State* Duplicate() override { return new GameState(*this); }

    std::vector<Ball*>* getBalls() {return m_balls;}
    Table* getTable() {return m_table;}
    int getStage() {return m_stage;}
    void setStage(int stage) {m_stage = stage;}
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

    virtual std::string ExportState() override;
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
    int m_stage = 1;
};
