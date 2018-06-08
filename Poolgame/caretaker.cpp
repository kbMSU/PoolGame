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

    // Get the highscore
    QFile readfile(highscore_path);
    if(readfile.exists()) {
        readfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString content = readfile.readAll();
        readfile.close();
        QJsonObject highscoreObject = QJsonDocument::fromJson(content.toUtf8()).object();
        m_highscore = highscoreObject.value("highscore").toInt(0);
    }
}

Caretaker::~Caretaker() {
    delete m_game;
}

void Caretaker::rewind() {
    // If there are no states to rewind, just go back to initial state as defined by the config
    if(m_currentStateIndex <= 0) {
        restore();
        return;
    }

    m_currentStateIndex--;
    restore();
}

void Caretaker::reset() {
    while(m_currentStateIndex > 0) {
        rewind();
    }
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

void Caretaker::exportLastSave() {
    std::string content = "{ \"stage3\": true,\n"
            + m_savedStates.back()->getState()->ExportState()
            + " }";
    QFile file(export_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(content.c_str());
    file.close();
}

void Caretaker::Notify(std::unique_ptr<Notification> n) {
    // If the notification is that the CueBall has come to rest, then save the state
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

void Caretaker::saveHighScore() {
    int score = m_game->getScore();
    if(score < m_highscore)
        return;

    // If the current score is more than the highscore, then save it as the new highscore
    std::string content = "{ \"highscore\": " + std::to_string(score) + " }";
    QFile file(highscore_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(content.c_str());
    file.close();
}
