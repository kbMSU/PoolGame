#include "caretaker.h"

Caretaker::Caretaker(Game* game)
    :m_game(game) {
    save();
}

Caretaker::~Caretaker() {
    delete m_game;
    for (auto s : m_savedStates) delete s;
}

void Caretaker::rewind() {
    if(m_currentStateIndex <= 0)
        return;

    m_currentStateIndex--;
    m_game->restoreFromMemento(m_savedStates[m_currentStateIndex]);
}

void Caretaker::fastforward() {
    if(m_currentStateIndex >= m_savedStates.size()-1)
        return;

    m_currentStateIndex++;
    m_game->restoreFromMemento(m_savedStates[m_currentStateIndex]);
}

void Caretaker::save() {
    // If we have rewinded and any have future states,
    // get rid of them from the history
    while(m_currentStateIndex < m_savedStates.size() - 1) {
        Memento* state = m_savedStates[m_savedStates.size() - 1];
        m_savedStates.pop_back();
        delete state;
    }

    m_savedStates.push_back(m_game->saveToMemento());
    m_currentStateIndex = m_savedStates.size() - 1;
}
