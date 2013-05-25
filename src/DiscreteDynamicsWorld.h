#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

#include <map>
#include "CollisionDispatcher.h"
#include "DbvtBroadphase.h"
#include "SequentialImpulseConstraintSolver.h"
#include "DefaultCollisionConfiguration.h"
#include "RigidBody.h"

OBJECT_DEF_START(DiscreteDynamicsWorld)
	OBJECT_DEF_ACCESSOR(gravity);
	OBJECT_DEF_FUNCTION(addRigidBody);
	OBJECT_DEF_FUNCTION(removeRigidBody);
	OBJECT_DEF_FUNCTION(step);
	OBJECT_DEF_FUNCTION(sweep);

	btDiscreteDynamicsWorld* world;

	Persistent<Object> _dispatcher;
	Persistent<Object> _broadphase;
	Persistent<Object> _solver;
	Persistent<Object> _config;
	std::map< RigidBody*, Persistent<Object> > _bodies;
OBJECT_DEF_END()
