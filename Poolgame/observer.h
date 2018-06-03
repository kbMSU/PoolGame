#pragma once

#include "notification.h"

class Observer
{
public:
    Observer() {}
    virtual void Notify(std::unique_ptr<Notification> n) = 0;
};
