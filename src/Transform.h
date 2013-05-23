#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(Transform)
	btTransform* _btTransform;
OBJECT_DEF_END()
