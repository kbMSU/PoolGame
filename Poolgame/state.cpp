#include "state.h"

/*GameState::GameState(GameState &state)
    : State(), m_stage(state.getStage())
    , m_table(state.getTable()), m_balls(state.getBalls())
{}*/

void GameState::UpdateState(State *state) {
    if(GameState *gameState = dynamic_cast<GameState*>(state)) {
        clearState();
        m_balls = gameState->getBalls();
        m_table = gameState->getTable();
        m_stage = gameState->getStage();
    } else {
        std::cerr << "GameState:UpdateState warning! This state object is invalid" << std::endl;
    }
}
