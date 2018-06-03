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
    m_game->restoreFromMemento(std::move(m_savedStates[m_currentStateIndex]));
}

void Caretaker::fastforward() {
    if(m_currentStateIndex >= m_savedStates.size()-1)
        return;

    m_currentStateIndex++;
    m_game->restoreFromMemento(std::move(m_savedStates[m_currentStateIndex]));
}

void Caretaker::save() {
    // If we have rewinded and any have future states,
    // get rid of them from the history
    while(m_currentStateIndex < m_savedStates.size() - 1) {
        //Memento* state = m_savedStates[m_savedStates.size() - 1];
        m_savedStates.pop_back();
        //delete state;
    }

    m_savedStates.push_back(std::unique_ptr<Memento>(m_game->saveToMemento()));

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
