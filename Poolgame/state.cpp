#include "state.h"

GameState::GameState(GameState &state)
    : State(), m_stage(state.getStage()) {
    /*m_table = state.getTable()->duplicate();
    m_balls = new std::vector<Ball*>();
    for(std::vector<Ball*>::iterator it = state.getBalls()->begin();
        it != state.getBalls()->end(); ++it) {
        m_balls->push_back((*it)->duplicate());
    }*/
    std::cout << "Gamestate : Copy constructor" << std::endl;
}

void GameState::UpdateState(State *state) {
    if(GameState *gameState = dynamic_cast<GameState*>(state)) {
        clearState();
        m_table = gameState->getTable()->duplicate();
        m_stage = gameState->getStage();
        m_balls = new std::vector<Ball*>();
        for(std::vector<Ball*>::iterator it = gameState->getBalls()->begin();
            it != gameState->getBalls()->end(); ++it) {
            m_balls->push_back((*it)->duplicate());
        }
    } else {
        std::cerr << "GameState:UpdateState warning! This state object is invalid" << std::endl;
    }
}
