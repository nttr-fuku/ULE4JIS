
#pragma once
#include "EmulationStrategy.h"

class USonJISKeyboardStrategy : public EmulationStrategy {
public:
	virtual ~USonJISKeyboardStrategy() {}
	virtual void getEmulationMap(EmulationMapType* dest);
};
