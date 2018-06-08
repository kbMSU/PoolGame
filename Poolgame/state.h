#pragma once

#include "ball.h"
#include "table.h"
#include "balldecorator.h"

#include <iostream>
#include <vector>
#include <QMouseEvent>

/**
 * @brief The State class - The state stored by the memento
 */
class State
{
public:
    State() {}
    virtual ~State() {}

    /**
     * @brief duplicate - creates a deep copy duplicate of the state
     * @return state pointer
     */
    virtual State* Duplicate() = 0;

    /**
     * @brief UpdateState - Update this with information from the provided state
     * @param state - the new information
     */
    virtual void UpdateState(State* state) = 0;

    /**
     * @brief ExportState - creates a string (formatted JSON) of the state
     * @return state as a string
     */
    virtual std::string ExportState() = 0;
};

/**
 * @brief The GameState class - The state of the game
 */
class GameState : public State
{
public:
    GameState(std::vector<Ball*>* balls, Table* table)
        :State(),m_balls(balls),m_table(table) {}
    GameState(GameState& state);
    virtual ~GameState() {clearState();}

    /**
     * @brief duplicate - creates a deep copy duplicate of the state
     * @return state pointer
     */
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

    /**
     * @brief UpdateState - Update this with information from the provided state
     * @param state - the new information
     */
    virtual void UpdateState(State* state) override;

    /**
     * @brief ExportState - creates a string (formatted JSON) of the state
     * @return state as a string
     */
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
