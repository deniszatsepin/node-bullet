#include "DiscreteDynamicsWorld.h"

OBJECT_INIT_START(DiscreteDynamicsWorld)
	NODE_SET_PROTOTYPE_METHOD(constructor, "getGravity", GetGravity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setGravity", SetGravity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "addRigidBody", AddRigidBody);
	NODE_SET_PROTOTYPE_METHOD(constructor, "stepSimulation", StepSimulation);
OBJECT_INIT_END()

OBJECT_NEW_START(DiscreteDynamicsWorld)
	self->_dispatcher = Persistent<Object>::New(args[0]->ToObject());
	self->_broadphase = Persistent<Object>::New(args[1]->ToObject());
	self->_solver = Persistent<Object>::New(args[2]->ToObject());
	self->_config = Persistent<Object>::New(args[3]->ToObject());

	self->_btDiscreteDynamicsWorld = new btDiscreteDynamicsWorld(
		ObjectWrap::Unwrap<CollisionDispatcher>(self->_dispatcher)->_btCollisionDispatcher,
		ObjectWrap::Unwrap<DbvtBroadphase>(self->_broadphase)->_btDbvtBroadphase,
		ObjectWrap::Unwrap<SequentialImpulseConstraintSolver>(self->_solver)->_btSequentialImpulseConstraintSolver,
		ObjectWrap::Unwrap<DefaultCollisionConfiguration>(self->_config)->_btDefaultCollisionConfiguration
	);
OBJECT_NEW_END()

OBJECT_DELETE_START(DiscreteDynamicsWorld)
	delete _btDiscreteDynamicsWorld;

	_dispatcher.Dispose();
	_broadphase.Dispose();
	_solver.Dispose();
	_config.Dispose();

	for(std::list< Persistent<Object> >::iterator it=_bodies.begin(); it != _bodies.end(); ++it) {
		(*it).Dispose();
	}
OBJECT_DELETE_END()


OBJECT_FUNCTION_START(DiscreteDynamicsWorld,GetGravity)
	btVector3 gravity = self->_btDiscreteDynamicsWorld->getGravity();
	return scope.Close(Number::New(gravity.getY()));
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,SetGravity)
	self->_btDiscreteDynamicsWorld->setGravity(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,AddRigidBody)
	Local<Object> obj = args[0]->ToObject();
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(obj);

	self->_btDiscreteDynamicsWorld->addRigidBody(rigidBody->_btRigidBody);
	self->_bodies.push_back(Persistent<Object>::New(obj));

	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,StepSimulation)
	self->_btDiscreteDynamicsWorld->stepSimulation(
		args[0]->ToNumber()->Value(),
		0
	);
	
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()
