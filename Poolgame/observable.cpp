#include "observable.h"

void Observable::attachObserver(Observer *o) {
    m_observers.push_back(o);
}

void Observable::detachObserver(Observer *o) {
    std::vector<Observer*>::iterator it;
    for(it = m_observers.begin(); it != m_observers.end(); ++it) {
        if((*it) == o) {
            break;
        }
    }
    if(it != m_observers.end())
        m_observers.erase(it);
}

void Observable::notify(std::unique_ptr<Notification> n) {
    for (Observer* o : m_observers) {
        o->notify(std::move(n));
    }
}
