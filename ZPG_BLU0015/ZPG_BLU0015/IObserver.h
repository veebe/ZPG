#pragma once
#include "ObserverTypes.h"

class IObserver {
public:
    virtual void OnUpdate(NotifyType ANotifyType) = 0;
};