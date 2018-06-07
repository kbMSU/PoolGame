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

    QString startPath = QDir::currentPath() + "../../../../start.qml";
    m_startView = new QQuickView;
    m_startView->setSource(QUrl::fromLocalFile(startPath));

    QObject* startItem = m_startView->rootObject();
    QObject::connect(startItem,SIGNAL(qmlSignal(QString)),this,SLOT(receiveMessage(QString)));

    QString confirmPath = QDir::currentPath() + "../../../../QuitConfirm.qml";
    m_confirmView = new QQuickView;
    m_confirmView->setSource(QUrl::fromLocalFile(confirmPath));

    QObject* confirmItem = m_confirmView->rootObject();
    QObject::connect(confirmItem,SIGNAL(qmlSignal(QString)),this,SLOT(receiveMessage(QString)));

    showStartScreen();
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
    m_caretaker->getGame()->render(painter);
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
    hide();
}

void Dialog::showConfirmBox() {
    m_confirmView->show();
    m_startView->hide();
    hide();
}

void Dialog::showGame() {
    show();
    m_confirmView->hide();
    m_startView->hide();
}

void Dialog::quitGame() {
    m_confirmView->close();
    m_startView->close();
    close();
}

void Dialog::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Q:
        showConfirmBox();
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
    }
}

void Dialog::evalAllEventsOfTypeSpecified(MouseEventable::EVENTS t, QMouseEvent *event) {
    // handle all the clicky events, and remove them if they've xPIRED
    MouseEventable::EventQueue& Qu = m_caretaker->getGame()->getEventFns();
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
