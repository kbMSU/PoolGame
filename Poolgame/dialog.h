#pragma once
#include <QDialog>
#include "ball.h"
#include "game.h"
#include "caretaker.h"
#include <QtQuick>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Game* game, QWidget *parent = 0);
    ~Dialog();

protected:
    /**
     * @brief paintEvent - called whenever window repainting is requested
     */
    void paintEvent(QPaintEvent *);
public slots:
    /**
     * @brief nextAnim - move the objects and perform collision events
     */
    void nextAnim();
    /**
     * @brief tryRender - draw the objects to screen
     */
    void tryRender();

    // qt mouse click
    void mousePressEvent(QMouseEvent* event);
    // qt mouse release
    void mouseReleaseEvent(QMouseEvent* event);
    // qt mouse move
    void mouseMoveEvent(QMouseEvent* event);

    // qt key release
    void keyReleaseEvent(QKeyEvent *event);

    void receiveMessage(const QString& msg);
private:
    /**
     * @brief evalAllEventsOfTypeSpecified - for each of the functions in the event queue
     *  invoke them if the event type is equal
     * @param t - the event type
     * @param event - the event to forward on to the function
     */
    void evalAllEventsOfTypeSpecified(MouseEventable::EVENTS t, QMouseEvent* event);

    void startGame();

    void showStartScreen();

    void showConfirmBox();

    void showGame();

    void quitGame();
private:
    /**
     * @brief aTimer - timer for calling nextAnim in intervals
     */
    QTimer* aTimer = nullptr;
    /**
     * @brief dTimer - timer for calling tryRender in intervals
     */
    QTimer* dTimer = nullptr;
    /**
     * @brief ui our drawable ui
     */
    Ui::Dialog *ui;
    /**
     * @brief m_caretaker - the caretaker for the game
     */
    Caretaker* m_caretaker;
    /**
     * @brief m_startView - the starting screen for the game
     */
    QQuickView* m_startView;
    /**
     * @brief m_confirmView - quit confirmation box
     */
    QQuickView* m_confirmView;
};

