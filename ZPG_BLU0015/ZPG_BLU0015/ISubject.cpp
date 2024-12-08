/* Vratislav Blunar - BLU0015 */
#include "ISubject.h"

void ISubject::Attach(IObserver* Aobserver) {
	observers.push_back(Aobserver);
}

void ISubject::Detach(IObserver* Aobserver) {
	observers.erase(std::remove(observers.begin(), observers.end(), Aobserver), observers.end());
}