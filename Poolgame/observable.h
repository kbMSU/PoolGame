#pragma once

#include <vector>

#include "observer.h"
#include "state.h"

class Observable
{
public:
    Observable() {}
    virtual ~Observable() {
        // Detach all observers
        m_observers.clear();
    }
    virtual void AttachObserver(Observer* o) {
        m_observers.push_back(o);
    }
    virtual void DetachObserver(Observer* o) {
        std::vector<Observer*>::iterator it;
        for(it = m_observers.begin(); it != m_observers.end(); ++it) {
            if((*it) == o) {
                break;
            }
        }
        if(it != m_observers.end())
            m_observers.erase(it);
    }
    virtual void Notify(State* state) {
        foreach (Observer* o, m_observers) {
            o->Notify(state);
        }
    }
private:
    std::vector<Observer*> m_observers;
};
