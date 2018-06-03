#pragma once

#include "notification.h"

class Observer
{
public:
    Observer() {}
    virtual void Notify(Notification* notification) = 0;
};
