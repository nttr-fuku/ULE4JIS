
#pragma once
#include "EmulationStrategy.h"

class USonJISRemoteStrategy : public EmulationStrategy {
public:
	virtual ~USonJISRemoteStrategy() {}
	virtual void getEmulationMap(EmulationMapType *dest);
};
