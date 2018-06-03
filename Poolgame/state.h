#pragma once

#include "ball.h"
#include "table.h"
#include <iostream>
#include <vector>

class State
{
public:
    State() {}
    virtual ~State() {}
    virtual void UpdateState(State* state) = 0;
};

class GameState : public State
{
public:
    GameState(std::vector<Ball*>* balls, Table* table, int stage)
        :State(),m_balls(balls),m_table(table),m_stage(stage) {}

    //GameState(GameState& state);

    virtual ~GameState() {clearState();}

    std::vector<Ball*>* getBalls() {return m_balls;}
    Table* getTable() {return m_table;}
    int getStage() {return m_stage;}

    virtual void UpdateState(State* state) override;
private:
    void clearState() {
        delete m_table;
        for (auto b : *m_balls) delete b;
        delete m_balls;
    }
private:
    std::vector<Ball*>* m_balls;
    Table* m_table;
    int m_stage;
};
