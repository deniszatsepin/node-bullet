#pragma once
#include "Object.h"
#include "DefaultCollisionConfiguration.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(CollisionDispatcher)
	btCollisionDispatcher* _btCollisionDispatcher;
	Persistent<Object> _config;
OBJECT_DEF_END()
