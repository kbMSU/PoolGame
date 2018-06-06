#pragma once

#include <vector>

#include "observer.h"
#include "notification.h"

class Observable
{
public:
    Observable() {}
    virtual ~Observable() {
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

    virtual void Notify(std::unique_ptr<Notification> n) {
        for (Observer* o : m_observers) {
            o->Notify(std::move(n));
        }
    }

    //std::vector<std::shared_ptr<Observer>> getObservers() {return m_observers;}
protected:
    std::vector<Observer*> m_observers;
};
