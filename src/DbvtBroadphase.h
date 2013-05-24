#pragma once
#include "Object.h"

OBJECT_DEF_START(DbvtBroadphase)
	btDbvtBroadphase* _btDbvtBroadphase;
	btGhostPairCallback* _ghostPairCallback;
OBJECT_DEF_END()
