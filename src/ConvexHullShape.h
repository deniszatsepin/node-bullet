#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(ConvexHullShape)
	OBJECT_DEF_FUNCTION(AddPoint);

	btConvexHullShape* _btConvexHullShape;
OBJECT_DEF_END()
