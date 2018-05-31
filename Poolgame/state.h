#pragma once

#include "ball.h"
#include "table.h"
#include <vector>

class State
{
public:
    virtual ~State() {}
protected:
    State() {}
};

class GameState : public State
{
public:
    GameState(std::vector<Ball*>* balls, Table* table)
        :State(),m_balls(balls),m_table(table) {}
    virtual ~GameState() {
        delete m_table;
        for (auto b : *m_balls) delete b;
        delete m_balls;
    }

    std::vector<Ball*>* getBalls() {return m_balls;}
    Table* getTable() {return m_table;}

private:
    std::vector<Ball*>* m_balls;
    Table* m_table;
};
