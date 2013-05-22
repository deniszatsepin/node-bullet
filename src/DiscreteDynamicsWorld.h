#ifndef __NODE_DISCRETEDYNAMICSWORLD_H__
#define __NODE_DISCRETEDYNAMICSWORLD_H__

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include <list> 

#include "CollisionDispatcher.h"
#include "DbvtBroadphase.h"
#include "SequentialImpulseConstraintSolver.h"
#include "DefaultCollisionConfiguration.h"
#include "RigidBody.h"

#include "btBulletDynamicsCommon.h"

using namespace v8;
using namespace node;

class DiscreteDynamicsWorld: public node::ObjectWrap {
	public:
		static Persistent<FunctionTemplate> constructor;
		
		static void Initialize(Handle<Object> target);
		static Handle<Value> New(const Arguments &args);
		
		static Handle<Value> GetGravity(const Arguments &args);
		static Handle<Value> SetGravity(const Arguments &args);
		static Handle<Value> AddRigidBody(const Arguments &args);
		static Handle<Value> StepSimulation(const Arguments &args);
		static Handle<Value> Debug(const Arguments &args);
		
		DiscreteDynamicsWorld(
			Handle<Object> dispatcher,
			Handle<Object> broadphase,
			Handle<Object> solver,
			Handle<Object> config
		);

		btDiscreteDynamicsWorld* _btDiscreteDynamicsWorld;
		
		Persistent<Object> _dispatcher;
		Persistent<Object> _broadphase;
		Persistent<Object> _solver;
		Persistent<Object> _config;
		std::list< Persistent<Object> > _bodies;
		
	private:
		~DiscreteDynamicsWorld();
};

#endif
