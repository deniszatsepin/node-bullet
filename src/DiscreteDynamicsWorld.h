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
	static Handle<Value> GetGravity(const Arguments &args);
	static Handle<Value> SetGravity(const Arguments &args);
	static Handle<Value> AddRigidBody(const Arguments &args);
	static Handle<Value> StepSimulation(const Arguments &args);

	btDiscreteDynamicsWorld* _btDiscreteDynamicsWorld;
	Persistent<Object> _dispatcher;
	Persistent<Object> _broadphase;
	Persistent<Object> _solver;
	Persistent<Object> _config;
	std::list< Persistent<Object> > _bodies;
OBJECT_DEF_END()
