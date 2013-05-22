#include "DiscreteDynamicsWorld.h"

#include <iostream>
using namespace std;

Persistent<FunctionTemplate> DiscreteDynamicsWorld::constructor;

void
DiscreteDynamicsWorld::Initialize(Handle<Object> target) {
	HandleScope scope;

	constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(DiscreteDynamicsWorld::New));
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(String::NewSymbol("DiscreteDynamicsWorld"));
	
	NODE_SET_PROTOTYPE_METHOD(constructor, "getGravity", GetGravity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setGravity", SetGravity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "addRigidBody", AddRigidBody);
	NODE_SET_PROTOTYPE_METHOD(constructor, "stepSimulation", StepSimulation);

	Local<ObjectTemplate> proto = constructor->PrototypeTemplate();

	target->Set(String::NewSymbol("DiscreteDynamicsWorld"), constructor->GetFunction());
	
	return;
}

Handle<Value>
DiscreteDynamicsWorld::New(const Arguments &args) {
	HandleScope scope;
	
	Local<Object> collisionDispatcherHandle = args[0]->ToObject();
	CollisionDispatcher* collisionDispatcher = ObjectWrap::Unwrap<CollisionDispatcher>(collisionDispatcherHandle);
	
	Local<Object> dbvtBroadphaseHandle = args[1]->ToObject();
	DbvtBroadphase* dbvtBroadphase = ObjectWrap::Unwrap<DbvtBroadphase>(dbvtBroadphaseHandle);
	
	Local<Object> sequentialImpulseConstraintSolverHandle = args[2]->ToObject();
	SequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver = ObjectWrap::Unwrap<SequentialImpulseConstraintSolver>(sequentialImpulseConstraintSolverHandle);
	
	Local<Object> defaultCollisionConfigurationHandle = args[3]->ToObject();
	DefaultCollisionConfiguration* defaultCollisionConfiguration = ObjectWrap::Unwrap<DefaultCollisionConfiguration>(defaultCollisionConfigurationHandle);
	
	DiscreteDynamicsWorld* discreteDynamicsWorld = new DiscreteDynamicsWorld(collisionDispatcher, dbvtBroadphase, sequentialImpulseConstraintSolver, defaultCollisionConfiguration);
	discreteDynamicsWorld->Wrap(args.This());
	
	return scope.Close(args.This());
}

Handle<Value>
DiscreteDynamicsWorld::GetGravity(const Arguments &args) {
	HandleScope scope;
	
	DiscreteDynamicsWorld* discreteDynamicsWorld = ObjectWrap::Unwrap<DiscreteDynamicsWorld>(args.This());
	btVector3 gravity = discreteDynamicsWorld->_btDiscreteDynamicsWorld->getGravity();
	
	Handle<Number> y = Number::New(gravity.getY());
	
	return scope.Close(y);
}

Handle<Value>
DiscreteDynamicsWorld::SetGravity(const Arguments &args) {
	HandleScope scope;
	
	double x = args[0]->ToNumber()->Value();
	double y = args[1]->ToNumber()->Value();
	double z = args[2]->ToNumber()->Value();
	
	DiscreteDynamicsWorld* discreteDynamicsWorld = ObjectWrap::Unwrap<DiscreteDynamicsWorld>(args.This());
	discreteDynamicsWorld->_btDiscreteDynamicsWorld->setGravity(btVector3(x, y, z));
	
	return scope.Close(Undefined());
}

Handle<Value>
DiscreteDynamicsWorld::AddRigidBody(const Arguments &args) {
	HandleScope scope;
	
	DiscreteDynamicsWorld* discreteDynamicsWorld = ObjectWrap::Unwrap<DiscreteDynamicsWorld>(args.This());
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args[0]->ToObject());
	
	discreteDynamicsWorld->_btDiscreteDynamicsWorld->addRigidBody(rigidBody->_btRigidBody);
	
	rigidBody->Ref();
	_bodies.push_back(rigidBody);
	
	return scope.Close(Undefined());
}

Handle<Value>
DiscreteDynamicsWorld::StepSimulation(const Arguments &args) {
	HandleScope scope;
	
	double delta = args[0]->ToNumber()->Value();
	
	DiscreteDynamicsWorld* discreteDynamicsWorld = ObjectWrap::Unwrap<DiscreteDynamicsWorld>(args.This());

	discreteDynamicsWorld->_btDiscreteDynamicsWorld->stepSimulation(delta);
	
	return scope.Close(Undefined());
}

DiscreteDynamicsWorld::DiscreteDynamicsWorld(CollisionDispatcher* collisionDispatcher, DbvtBroadphase* dbvtBroadphase, SequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver, DefaultCollisionConfiguration* defaultCollisionConfiguration): ObjectWrap() {	
	_dispatcher = collisionDispatcher;
	_dispatcher->Ref();

	_broadphase = dbvtBroadphase;
	_broadphase->Ref();

	_solver = sequentialImpulseConstraintSolver;
	_solver->Ref();

	_config = defaultCollisionConfiguration;
	_config->Ref();

	_btDiscreteDynamicsWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher->_btCollisionDispatcher,
		dbvtBroadphase->_btDbvtBroadphase,
		sequentialImpulseConstraintSolver->_btSequentialImpulseConstraintSolver,
		defaultCollisionConfiguration->_btDefaultCollisionConfiguration
	);
}

DiscreteDynamicsWorld::~DiscreteDynamicsWorld() {
	if(_btDiscreteDynamicsWorld)
		delete _btDiscreteDynamicsWorld;
	
	_dispatcher->Unref();
	_broadphase->Unref();
	_solver->Unref();
	_config->Unref();
	for(std::list<RigidBody*>::iterator it=_bodies.begin(); it != _bodies.end(); ++it) {
		(*it)->Unref();
	}
}
