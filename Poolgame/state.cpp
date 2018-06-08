#include "state.h"

GameState::GameState(GameState &state)
    : State(), m_stage(state.getStage()) {
    // Perform a deep copy
    m_table = state.getTable()->duplicate();
    m_balls = new std::vector<Ball*>();
    for(Ball* b : (* (state).getBalls()) ) {
        m_balls->push_back(b->duplicate());
    }
}

void GameState::UpdateState(State *state) {
    if(GameState *gameState = dynamic_cast<GameState*>(state)) {
        // Perform a deepcopy
        m_table = gameState->getTable()->duplicate();
        m_stage = gameState->getStage();
        m_balls = new std::vector<Ball*>();
        for(Ball* b : * ((gameState)->getBalls())) {
            Ball* duplicate = b->duplicate();
            // If its a cueball we need to get the EventFunctions to re-enable click functionality after restore
            if(duplicate->isCueBall()) {
                if(BallDecorator* bd = dynamic_cast<BallDecorator*>(duplicate)) {
                    if(CueBall* cb = dynamic_cast<CueBall*>(bd->getCueBall())) {
                        m_mouseEventFunctions = cb->getEvents();
                    }
                }
            }
            m_balls->push_back(duplicate);
        }
    } else {
        std::cerr << "GameState:UpdateState warning! This state object is invalid" << std::endl;
    }
}

std::string GameState::ExportState() {
    std::string content = "\"table\": {\n";
    content += m_table->ExportState();
    content += "},\n";
    content += "\"balls\": [\n";
    int size = (*m_balls).size();
    for(int i=0;i<size;i++) {
        content += (*m_balls)[i]->ExportState();
        if(i < size - 1) {
            content += ",\n";
        }
    }
    content += "]\n";
    return content;
}
