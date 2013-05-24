#include "DiscreteDynamicsWorld.h"

OBJECT_INIT_START(DiscreteDynamicsWorld)
	OBJECT_INIT_ACCESSOR(gravity)
	OBJECT_INIT_FUNCTION(addRigidBody);
	OBJECT_INIT_FUNCTION(step);
OBJECT_INIT_END()

OBJECT_NEW_START(DiscreteDynamicsWorld)
	self->_dispatcher = Persistent<Object>::New(args[0]->ToObject());
	self->_broadphase = Persistent<Object>::New(args[1]->ToObject());
	self->_solver = Persistent<Object>::New(args[2]->ToObject());
	self->_config = Persistent<Object>::New(args[3]->ToObject());

	btDiscreteDynamicsWorld* world = new btDiscreteDynamicsWorld(
		CollisionDispatcher::Unwrap(self->_dispatcher)->_btCollisionDispatcher,
		DbvtBroadphase::Unwrap(self->_broadphase)->_btDbvtBroadphase,
		SequentialImpulseConstraintSolver::Unwrap(self->_solver)->_btSequentialImpulseConstraintSolver,
		DefaultCollisionConfiguration::Unwrap(self->_config)->_btDefaultCollisionConfiguration
	);
	self->_btDiscreteDynamicsWorld = world;
	
	world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
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

OBJECT_GETTER_START(DiscreteDynamicsWorld,gravity)
	result = Util::vectorToObj(self->_btDiscreteDynamicsWorld->getGravity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(DiscreteDynamicsWorld,gravity)
	self->_btDiscreteDynamicsWorld->setGravity(Util::objToVector(value));
OBJECT_SETTER_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,addRigidBody)
	Local<Object> obj = args[0]->ToObject();
	RigidBody* rigidBody = RigidBody::Unwrap(obj);

	self->_btDiscreteDynamicsWorld->addRigidBody(rigidBody->_btRigidBody);
	self->_bodies.push_back(Persistent<Object>::New(obj));
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,step)
	self->_btDiscreteDynamicsWorld->stepSimulation(
		args[0]->ToNumber()->Value(),
		0
	);
OBJECT_FUNCTION_END()
