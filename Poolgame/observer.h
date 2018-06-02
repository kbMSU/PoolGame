#pragma once

#include "state.h"

class Observer
{
public:
    Observer() {}
    virtual void Notify(State* state) = 0;
};
