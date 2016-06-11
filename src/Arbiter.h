#ifndef _ARBITER_H_
#define _ARBITER_H_

#include "interface/interface.h"
#include "Sir.h"

class Arbiter{
protected:
	vss_state::Global_State *global_state;

public:
	Arbiter();

	void allocateState(vss_state::Global_State*);
	int checkWorld();
};

#endif // _ARBITER_H_