#pragma once

#include <vector>

#include "observer.h"
#include "notification.h"

class Observable
{
public:
    Observable() {}
    virtual ~Observable() {
        // Detach all observers
        m_observers.clear();
    }
    virtual void AttachObserver(std::shared_ptr<Observer> o) {
        m_observers.push_back(o);
    }
    virtual void DetachObserver(std::shared_ptr<Observer> o) {
        std::vector<std::shared_ptr<Observer>>::iterator it;
        for(it = m_observers.begin(); it != m_observers.end(); ++it) {
            if((*it) == o) {
                break;
            }
        }
        if(it != m_observers.end())
            m_observers.erase(it);
    }
    virtual void Notify(std::unique_ptr<Notification> n) {
        foreach (std::shared_ptr<Observer> o, m_observers) {
            o->Notify(std::move(n));
        }
    }
private:
    std::vector<std::shared_ptr<Observer>> m_observers;
};
