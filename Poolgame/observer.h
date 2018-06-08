#pragma once

#include "notification.h"

/**
 * @brief The Observer class - Used in the observer pattern
 */
class Observer
{
public:
    Observer() {}

    /**
     * @brief Notify - Receive a notification from the observable
     * @param n - The notification received
     */
    virtual void notify(std::unique_ptr<Notification> n) = 0;
};
