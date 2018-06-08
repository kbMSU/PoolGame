#pragma once

#include <vector>

#include "observer.h"
#include "notification.h"

/**
 * @brief The Observable class - Used in the Observer pattern
 */
class Observable
{
protected:
    Observable() {}
public:
    virtual ~Observable() {
        m_observers.clear();
    }

    /**
     * @brief AttachObserver - Attach an observer to this object
     * @param o - The observer to attach
     */
    virtual void AttachObserver(Observer* o) {
        m_observers.push_back(o);
    }

    /**
     * @brief DetachObserver - Detach an observer from this object
     * @param o - The observer to detach
     */
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

    /**
     * @brief Notify - Notify all attached observers
     * @param n - The notification to send
     */
    virtual void Notify(std::unique_ptr<Notification> n) {
        for (Observer* o : m_observers) {
            o->Notify(std::move(n));
        }
    }
protected:
    // All the observers that are monitoring this observable
    std::vector<Observer*> m_observers;
};
