#pragma once

#include "ball.h"
#include "table.h"
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
    virtual ~GameState() {clearState();}

    std::vector<Ball*>* getBalls() {return m_balls;}
    Table* getTable() {return m_table;}
    int getStage() {return m_stage;}

    virtual void UpdateState(State* state) override {
        if(GameState *gameState = dynamic_cast<GameState*>(state)) {
            clearState();
            m_balls = gameState->getBalls();
            m_table = gameState->getTable();
            m_stage = gameState->getStage();
        } else {
            std::cerr << "GameState:UpdateState warning! This state object is invalid" << std::endl;
        }
    }
private:
    void clearState() {
        /*delete m_table;
        for (auto b : *m_balls) delete b;
        delete m_balls;*/
    }
private:
    std::vector<Ball*>* m_balls;
    Table* m_table;
    int m_stage;
};
