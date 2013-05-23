#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(RigidBody)
	static Handle<Value> GetPosition(const Arguments &args);
	static Handle<Value> SetPosition(const Arguments &args);
	static Handle<Value> SetLinearVelocity(const Arguments &args);
	static Handle<Value> SetGravity(const Arguments &args);
	static Handle<Value> ApplyImpulse(const Arguments &args);
	static Handle<Value> ApplyCentralImpulse(const Arguments &args);

	btRigidBody* _btRigidBody;
	Persistent<Object> _shape;
OBJECT_DEF_END()
