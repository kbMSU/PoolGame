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
    virtual void AttachObserver(Observer* o);

    /**
     * @brief DetachObserver - Detach an observer from this object
     * @param o - The observer to detach
     */
    virtual void DetachObserver(Observer* o);

    /**
     * @brief Notify - Notify all attached observers
     * @param n - The notification to send
     */
    virtual void Notify(std::unique_ptr<Notification> n);
protected:
    // All the observers that are monitoring this observable
    std::vector<Observer*> m_observers;
};
