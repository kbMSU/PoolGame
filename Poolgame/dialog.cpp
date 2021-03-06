#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMouseEvent>

#include "utils.h"

Dialog::Dialog(Game *game, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_caretaker(new Caretaker(game))
{
    ui->setupUi(this);

    setupMenus();

    if(m_caretaker->getStage() < 3) {
        startGame();
    } else {
        showStartScreen();
    }
}

void Dialog::setupMenus() {
    // Get the start screen
    m_startView = new QQuickView;
    m_startView->setSource(QUrl::fromLocalFile(start_screen_path));
    QObject* startItem = m_startView->rootObject();
    // Write the value of the highscore on the start screen
    QQmlProperty::write(startItem, "highscore", m_caretaker->getHighscore());
    // Listen to button clicks from the start screen
    QObject::connect(startItem,SIGNAL(qmlSignal(QString)),this,SLOT(receiveMessage(QString)));

    // Get the confirm quit screen
    m_confirmView = new QQuickView;
    m_confirmView->setSource(QUrl::fromLocalFile(confirm_screen_path));
    QObject* confirmItem = m_confirmView->rootObject();
    // Listen to button clicks from the confirm quit screen
    QObject::connect(confirmItem,SIGNAL(qmlSignal(QString)),this,SLOT(receiveMessage(QString)));

    // Get the in-game menu screen
    m_menuView = new QQuickView;
    m_menuView->setSource(QUrl::fromLocalFile(menu_screen_path));
    QObject* menuItem = m_menuView->rootObject();
    // Listen to button clicks from the menu screen
    QObject::connect(menuItem,SIGNAL(qmlSignal(QString)),this,SLOT(receiveMessage(QString)));
}

void Dialog::startGame() {
    m_startView->hide();

    // for animating (i.e. movement, collision) every animFrameMS
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(nextAnim()));
    aTimer->start(animFrameMS);

    // for drawing every drawFrameMS milliseconds
    dTimer = new QTimer(this);
    connect(dTimer, SIGNAL(timeout()), this, SLOT(tryRender()));
    dTimer->start(drawFrameMS);

    // set the window size to be at least the table size
    this->resize(m_caretaker->getGameSize());

    show();
}

Dialog::~Dialog()
{
    delete aTimer;
    delete dTimer;
    delete m_caretaker;
    delete ui;
    delete m_startView;
    delete m_confirmView;
    delete m_menuView;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_caretaker->animate(1.0/(double)animFrameMS);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_caretaker->render(painter);
}

void Dialog::mousePressEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseClickFn, event);
}

void Dialog::mouseReleaseEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseRelFn, event);
}
void Dialog::mouseMoveEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseMoveFn, event);
}

void Dialog::showStartScreen() {
    m_startView->show();
    m_confirmView->hide();
    m_menuView->hide();
    hide();
}

void Dialog::showConfirmBox() {
    QObject* confirmItem = m_confirmView->rootObject();
    QQmlProperty::write(confirmItem, "score", m_caretaker->getScore());

    m_confirmView->show();
    m_startView->hide();
    m_menuView->hide();
    hide();
}

void Dialog::showGame() {
    show();
    m_confirmView->hide();
    m_startView->hide();
    m_menuView->hide();
}

void Dialog::showMenu() {
    hide();
    m_menuView->show();
    m_startView->hide();
    m_confirmView->hide();
}

void Dialog::quitGame() {
    m_caretaker->saveHighScore();

    m_confirmView->close();
    m_startView->close();
    m_menuView->close();
    close();
}

void Dialog::keyReleaseEvent(QKeyEvent *event) {
    if(m_caretaker->getStage() < 3)
        return;

    switch (event->key()) {
    case Qt::Key_Q:
        showConfirmBox();
        break;
    case Qt::Key_M:
        showMenu();
        break;
    default:
        m_caretaker->processKeyRelease(event);
        break;
    }
}

void Dialog::receiveMessage(const QString& msg) {
    if(msg.toStdString() == "StartGame") {
        startGame();
    } else if (msg.toStdString() == "CancelQuit") {
        showGame();
    } else if (msg.toStdString() == "ConfirmQuit") {
        quitGame();
    } else if (msg.toStdString() == "ResetGame") {
        m_caretaker->reset();
        showGame();
    } else if (msg.toStdString() == "ExportSave") {
        m_caretaker->exportLastSave();
        showGame();
    } else if (msg.toStdString() == "BackMenu") {
        showGame();
    }
}

void Dialog::evalAllEventsOfTypeSpecified(MouseEventable::EVENTS t, QMouseEvent *event) {
    // handle all the clicky events, and remove them if they've xPIRED
    MouseEventable::EventQueue& Qu = m_caretaker->getEventFns();
    for (ssize_t i = Qu.size()-1; i >= 0; i--) {
        if (auto spt = (Qu.at(i)).lock()) {
            if (spt->second == t) {
                spt->first(event);
            }
        } else {
            // remove this element from our vector
            Qu.erase(Qu.begin() + i);
        }
    }
}
