#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(RigidBody)
	OBJECT_DEF_ACCESSOR(position);
	OBJECT_DEF_ACCESSOR(quaternion);
	OBJECT_DEF_ACCESSOR(velocity);
	OBJECT_DEF_ACCESSOR(gravity);
	OBJECT_DEF_ACCESSOR(kinematic);
	OBJECT_DEF_ACCESSOR(friction);

	OBJECT_DEF_FUNCTION(activate);
	OBJECT_DEF_FUNCTION(applyImpulse);
	OBJECT_DEF_FUNCTION(applyCentralImpulse);
	OBJECT_DEF_FUNCTION(setLinearFactor);
	OBJECT_DEF_FUNCTION(setAngularFactor);

	btRigidBody* body;
	Persistent<Object> _shape;
OBJECT_DEF_END()
