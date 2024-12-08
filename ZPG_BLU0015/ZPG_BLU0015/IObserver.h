#pragma once
/* Vratislav Blunar - BLU0015 */
#include "ObserverTypes.h"

class IObserver {
public:
    virtual void OnUpdate(NotifyType ANotifyType) = 0;
};