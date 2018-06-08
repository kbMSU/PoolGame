#pragma once

#include <iostream>
#include <string>

/**
 * @brief The Notification class - Observables send this to observers to notify them of any changes
 */
class Notification
{
public:
    Notification() {}
    virtual ~Notification() {}
    virtual std::string getMessage() = 0;
};

/**
 * @brief The CueBallStoppedNotification class - Sent by the cueball to the caretaker when the cueball comes to rest
 */
class CueBallStoppedNotification : public Notification
{
public:
    CueBallStoppedNotification() {}
    virtual ~CueBallStoppedNotification() {}
    virtual std::string getMessage() override {return "CueBallStopped";}
};
