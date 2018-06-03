#include "caretaker.h"

Caretaker::Caretaker(Game* game)
    :m_game(game) {
    // Save initial state
    save();
    // Set this caretaker to observe the cueball (if one exists)
    if(CueBall* cb = m_game->getCueBall()) {
        cb->AttachObserver(std::shared_ptr<Caretaker>(this));
    }
}

Caretaker::~Caretaker() {
    delete m_game;
    //for (auto s : m_savedStates) delete s;
}

void Caretaker::rewind() {
    if(m_currentStateIndex <= 0)
        return;

    m_currentStateIndex--;
    m_game->restoreFromMemento(m_savedStates[m_currentStateIndex].get());
}

void Caretaker::fastforward() {
    if(m_currentStateIndex >= m_savedStates.size()-1)
        return;

    m_currentStateIndex++;
    m_game->restoreFromMemento(m_savedStates[m_currentStateIndex].get());
}

void Caretaker::save() {
    // If we have rewinded and any have future states,
    // get rid of them from the history
    while(m_currentStateIndex < m_savedStates.size() - 1) {
        //Memento* state = m_savedStates[m_savedStates.size() - 1];
        m_savedStates.pop_back();
        //delete state;
    }

    m_savedStates.push_back(m_game->saveToMemento());
    for(int i=0; i<m_savedStates.size(); i++) {
        GameState *gs = dynamic_cast<GameState*>(m_savedStates[i]->getState());
        Ball* b =gs->getBalls()->front();
        std::cout << b->getPosition().x() << ", " << b->getPosition().y() << std::endl;
    }
    std::cout << "" << std::endl;
    m_currentStateIndex = m_savedStates.size() - 1;
}

void Caretaker::Notify(std::unique_ptr<Notification> n) {
    if(CueBallStoppedNotification* c =
            dynamic_cast<CueBallStoppedNotification*>(n.get())) {
        save();
    }
}

void Caretaker::processKeyRelease(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_R:
        rewind();
        break;
    case Qt::Key_F:
        fastforward();
        break;
    default:
        break;
    }
}
