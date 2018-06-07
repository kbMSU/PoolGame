#pragma once

#include <vector>
#include <QKeyEvent>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

#include "game.h"
#include "memento.h"
#include "observer.h"

class Caretaker : public Observer
{
public:
    Caretaker(Game* game);
    virtual ~Caretaker();
    Game* getGame() {return m_game;}
    void processKeyRelease(QKeyEvent *event);
    void reset();
    void exportLastSave();
    int getScore() { return m_game->getScore(); }
    int getHighscore() { return m_highscore; }
    void saveHighScore();

    QSize getGameSize() const { return QSize(m_game->getMinimumWidth(),m_game->getMinimumHeight()); }
    void animate(double dt) { m_game->animate(dt); }
public:
    virtual void Notify(std::unique_ptr<Notification> n) override;
private:
    void rewind();
    void fastforward();
    void restore();
    void save();
private:
    Game* m_game;
    std::vector<std::unique_ptr<Memento>> m_savedStates;
    int m_currentStateIndex = -1;
    int m_highscore = 0;
};

