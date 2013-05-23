#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(SequentialImpulseConstraintSolver)
	btSequentialImpulseConstraintSolver* _btSequentialImpulseConstraintSolver;
OBJECT_DEF_END()
