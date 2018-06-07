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

int Caretaker::getHighscore() {
    QFile readfile(highscore_path);
    if(readfile.exists()) {
        readfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString content = readfile.readAll();
        readfile.close();
        QJsonObject highscoreObject = QJsonDocument::fromJson(content.toUtf8()).object();
        return highscoreObject.value("highscore").toInt(0);
    } else {
        return 0;
    }
}

void Caretaker::saveHighScore() {
    int score = m_game->getScore();

    QFile readfile(highscore_path);
    if(readfile.exists()) {
        readfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString content = readfile.readAll();
        readfile.close();
        QJsonObject highscoreObject = QJsonDocument::fromJson(content.toUtf8()).object();
        int highscore = highscoreObject.value("highscore").toInt(0);

        if(score <= highscore)
            return;
    }

    std::string content = "{ \"highscore\": " + std::to_string(score) + " }";
    QFile file(highscore_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(content.c_str());
    file.close();
}
