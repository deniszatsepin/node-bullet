#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(ConvexHullShape)
	OBJECT_DEF_FUNCTION(addPoint);

	btConvexHullShape* _btConvexHullShape;
OBJECT_DEF_END()
