#pragma once

#include <vector>
#include <cassert>
#include "observer.h"

class subject {
public:
	virtual ~subject()=0;
	void addObserver(observer* obs) {
		observers.push_back(obs);
		obs->setSubject(this);
	}
	void removeObserver(observer* obs) {
		assert(false);
	}
protected:
	virtual void update() {
		for (auto* obs : observers) {
			obs->update();
		}
	}
	std::vector<observer*> observers;

};

