#include "observable.h"

void Observable::AttachObserver(Observer *o) {
    m_observers.push_back(o);
}

void Observable::DetachObserver(Observer *o) {
    std::vector<Observer*>::iterator it;
    for(it = m_observers.begin(); it != m_observers.end(); ++it) {
        if((*it) == o) {
            break;
        }
    }
    if(it != m_observers.end())
        m_observers.erase(it);
}

void Observable::Notify(std::unique_ptr<Notification> n) {
    for (Observer* o : m_observers) {
        o->Notify(std::move(n));
    }
}
