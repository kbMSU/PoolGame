#pragma once

#include <vector>
#include <QKeyEvent>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

#include "game.h"
#include "memento.h"
#include "observer.h"

/**
 * @brief The Caretaker class - Used in the memento pattern
 */
class Caretaker : public Observer
{
public:
    Caretaker(Game* game);
    virtual ~Caretaker();

    /**
     * @brief processKeyRelease - Perform the appropriate actions on key release
     * @param event
     */
    void processKeyRelease(QKeyEvent *event);

    /**
     * @brief reset - Reset the game to the original state
     */
    void reset();

    /**
     * @brief exportLastSave - Export the most recent saved state
     */
    void exportLastSave();

    /**
     * @brief saveHighScore - Persist the highscore to disk
     */
    void saveHighScore();


    int getScore() { return m_game->getScore(); }
    int getHighscore() { return m_highscore; }
    Game* getGame() {return m_game;}
    QSize getGameSize() const { return QSize(m_game->getMinimumWidth(),m_game->getMinimumHeight()); }
    void animate(double dt) { m_game->animate(dt); }
    int getStage() {return m_game->getStage();}
public:
    /**
     * @brief Notify - Notification to the observer from the observerable
     * @param n - The notification that was sent
     */
    virtual void Notify(std::unique_ptr<Notification> n) override;
private:
    /**
     * @brief rewind - Move back 1 state if possible
     */
    void rewind();

    /**
     * @brief fastforward - Move forward 1 state if possible
     */
    void fastforward();

    /**
     * @brief save - Save a new state
     */
    void save();

    /**
     * @brief restore - Restore a state
     */
    void restore();
private:
    Game* m_game;
    // The saved states
    std::vector<std::unique_ptr<Memento>> m_savedStates;
    int m_currentStateIndex = -1;
    int m_highscore = 0;
};

