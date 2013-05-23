#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

#include <list>
#include "CollisionDispatcher.h"
#include "DbvtBroadphase.h"
#include "SequentialImpulseConstraintSolver.h"
#include "DefaultCollisionConfiguration.h"
#include "RigidBody.h"

OBJECT_DEF_START(DiscreteDynamicsWorld)
	OBJECT_DEF_FUNCTION(GetGravity);
	OBJECT_DEF_FUNCTION(SetGravity);
	OBJECT_DEF_FUNCTION(AddRigidBody);
	OBJECT_DEF_FUNCTION(StepSimulation);

	btDiscreteDynamicsWorld* _btDiscreteDynamicsWorld;
	Persistent<Object> _dispatcher;
	Persistent<Object> _broadphase;
	Persistent<Object> _solver;
	Persistent<Object> _config;
	std::list< Persistent<Object> > _bodies;
OBJECT_DEF_END()
