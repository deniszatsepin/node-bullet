#ifndef __NODE_RIGIDBODY_H__
#define __NODE_RIGIDBODY_H__

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>

#include "btBulletDynamicsCommon.h"

class DiscreteDynamicsWorld;

// #include "DiscreteDynamicsWorld.h"

using namespace v8;
using namespace node;

class RigidBody: public node::ObjectWrap {
	public:
		static Persistent<FunctionTemplate> constructor;
		
		static void Initialize(Handle<Object> target);
		static Handle<Value> New(const Arguments &args);
		
		RigidBody(double a_mass);

		btRigidBody* _btRigidBody;
		btDiscreteDynamicsWorld* _btDiscreteDynamicsWorld;
		float _mass;
		
		static Handle<Value> GetPosition(const Arguments &args);
		static Handle<Value> SetPosition(const Arguments &args);
		
		static Handle<Value> SetLinearVelocity(const Arguments &args);
				
		static Handle<Value> SetGravity(const Arguments &args);
		
		static Handle<Value> ApplyImpulse(const Arguments &args);
		static Handle<Value> ApplyCentralImpulse(const Arguments &args);
		
	private:
		~RigidBody();
};

#endif
