#pragma once
#include "IObserver.h"

enum NotifyType {
	VIEWMATRIX,
	PROJECTIONMATRIX
};

class ISubject {
public:
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify(NotifyType Atype) = 0;
};