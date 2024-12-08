#pragma once
/* Vratislav Blunar - BLU0015 */
#include "IObserver.h"
#include "ObserverTypes.h"

#include "vector"

class ISubject {
public:
	virtual void Attach(IObserver* observer);
	virtual void Detach(IObserver* observer);
protected:
	virtual void Notify(NotifyType Atype) = 0;
	std::vector<IObserver*> observers;
};