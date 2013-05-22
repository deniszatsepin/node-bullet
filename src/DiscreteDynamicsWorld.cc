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

	DiscreteDynamicsWorld* discreteDynamicsWorld = new DiscreteDynamicsWorld(
		args[0]->ToObject(),
		args[1]->ToObject(),
		args[2]->ToObject(),
		args[3]->ToObject()
	);
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

	Local<Object> obj = args[0]->ToObject();
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(obj);

	DiscreteDynamicsWorld* discreteDynamicsWorld = ObjectWrap::Unwrap<DiscreteDynamicsWorld>(args.This());
	discreteDynamicsWorld->_btDiscreteDynamicsWorld->addRigidBody(rigidBody->_btRigidBody);

	_bodies.push_back(Persistent<Object>::New(obj));
	
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

DiscreteDynamicsWorld::DiscreteDynamicsWorld(
	Handle<Object> dispatcher,
	Handle<Object> broadphase,
	Handle<Object> solver,
	Handle<Object> config
): ObjectWrap() {
	_dispatcher = Persistent<Object>::New(dispatcher);
	_broadphase = Persistent<Object>::New(broadphase);
	_solver = Persistent<Object>::New(solver);
	_config = Persistent<Object>::New(config);

	_btDiscreteDynamicsWorld = new btDiscreteDynamicsWorld(
		ObjectWrap::Unwrap<CollisionDispatcher>(_dispatcher)->_btCollisionDispatcher,
		ObjectWrap::Unwrap<DbvtBroadphase>(_broadphase)->_btDbvtBroadphase,
		ObjectWrap::Unwrap<SequentialImpulseConstraintSolver>(_solver)->_btSequentialImpulseConstraintSolver,
		ObjectWrap::Unwrap<DefaultCollisionConfiguration>(_config)->_btDefaultCollisionConfiguration
	);
}

DiscreteDynamicsWorld::~DiscreteDynamicsWorld() {
	if(_btDiscreteDynamicsWorld)
		delete _btDiscreteDynamicsWorld;
	
	_dispatcher.Dispose();
	_broadphase.Dispose();
	_solver.Dispose();
	_config.Dispose();

	for(std::list<Persistent<Object>>::iterator it=_bodies.begin(); it != _bodies.end(); ++it) {
		(*it).Dispose();
	}
}
