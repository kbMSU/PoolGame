#pragma once

#include <iostream>
#include <string>

class Notification
{
public:
    Notification() {}
    virtual ~Notification() {}
    virtual std::string getMessage() = 0;
};

class CueBallStoppedNotification : public Notification
{
public:
    CueBallStoppedNotification() {}
    virtual ~CueBallStoppedNotification() {}
    virtual std::string getMessage() override {return "CueBallStopped";}
};
