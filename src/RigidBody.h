#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(RigidBody)
	OBJECT_DEF_FUNCTION(GetPosition);
	OBJECT_DEF_FUNCTION(SetPosition);
	OBJECT_DEF_FUNCTION(GetRotation);
	OBJECT_DEF_FUNCTION(SetRotation);

	OBJECT_DEF_FUNCTION(SetLinearVelocity);
	OBJECT_DEF_FUNCTION(SetGravity);
	OBJECT_DEF_FUNCTION(ApplyImpulse);
	OBJECT_DEF_FUNCTION(ApplyCentralImpulse);

	btRigidBody* _btRigidBody;
	Persistent<Object> _shape;
OBJECT_DEF_END()
