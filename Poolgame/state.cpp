#include "state.h"

GameState::GameState(GameState &state)
    : State(), m_stage(state.getStage()) {
    m_table = state.getTable()->duplicate();
    m_balls = new std::vector<Ball*>();
    for(Ball* b : (* (state).getBalls()) ) {
        m_balls->push_back(b->duplicate());
    }
}

void GameState::UpdateState(State *state) {
    if(GameState *gameState = dynamic_cast<GameState*>(state)) {
        m_table = gameState->getTable()->duplicate();
        m_stage = gameState->getStage();
        m_balls = new std::vector<Ball*>();
        for(Ball* b : * ((gameState)->getBalls())) {
            Ball* duplicate = b->duplicate();
            if(duplicate->isCueBall()) {
                BallDecorator* bd = dynamic_cast<BallDecorator*>(duplicate);
                CueBall* cb = dynamic_cast<CueBall*>(bd->getCueBall());
                m_mouseEventFunctions = cb->getEvents();
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
    for(int i=0;i<(*m_balls).size();i++) {
        content += (*m_balls)[i]->ExportState();
        if(i < (*m_balls).size() - 1) {
            content += ",\n";
        }
    }
    content += "]\n";
    return content;
}
