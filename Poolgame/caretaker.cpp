#include "caretaker.h"

Caretaker::Caretaker(Game* game)
    :m_game(game) {

    // Saving states are only needed if we are in stage 3
    if(m_game->getStage() < 3)
        return;

    // Save initial state
    save();    

    // Set this caretaker to observe the cueball (if one exists)
    if(Ball* cb = m_game->getCueBall()) {
        cb->AttachObserver(this);
    }
}

Caretaker::~Caretaker() {
    delete m_game;
}

void Caretaker::rewind() {
    if(m_currentStateIndex <= 0) {
        restore();
        return;
    }

    m_currentStateIndex--;
    restore();
}

void Caretaker::fastforward() {
    if(m_currentStateIndex >= int(m_savedStates.size())-1)
        return;

    m_currentStateIndex++;
    restore();
}

void Caretaker::restore() {
    m_game->restoreFromMemento(m_savedStates[m_currentStateIndex].get());
    if(Ball* cb = m_game->getCueBall()) {
        cb->AttachObserver(this);
    }
}

void Caretaker::save() {
    // If we have rewinded and any have future states,
    // get rid of them from the history
    while(m_currentStateIndex < int(m_savedStates.size()) - 1) {
        m_savedStates.pop_back();
    }

    m_savedStates.push_back(m_game->saveToMemento());
    m_currentStateIndex = m_savedStates.size() - 1;
}

void Caretaker::Notify(std::unique_ptr<Notification> n) {
    if(CueBallStoppedNotification* c = dynamic_cast<CueBallStoppedNotification*>(n.get()))
        save();
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
