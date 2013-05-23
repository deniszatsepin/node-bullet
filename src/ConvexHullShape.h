#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(ConvexHullShape)
	btConvexHullShape* _btConvexHullShape;
OBJECT_DEF_END()
