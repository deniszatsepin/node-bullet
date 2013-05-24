#include "RigidBody.h"
#include "BoxShape.h"
#include "ConvexHullShape.h"

OBJECT_INIT_START(RigidBody)
	OBJECT_INIT_ACCESSOR(position);
	OBJECT_INIT_ACCESSOR(quaternion);
	OBJECT_INIT_ACCESSOR(velocity);
	OBJECT_INIT_ACCESSOR(gravity);
	OBJECT_INIT_FUNCTION(applyImpulse);
	OBJECT_INIT_FUNCTION(applyCentralImpulse);
OBJECT_INIT_END()

OBJECT_NEW_START(RigidBody)
	double mass = args[0]->ToNumber()->Value();
	Local<Object> shapeHandle = args[1]->ToObject();

	btCollisionShape* shape;
	if(BoxShape::HasInstance(shapeHandle)) {
		shape = BoxShape::Unwrap(shapeHandle)->_btBoxShape;
	} else if(ConvexHullShape::HasInstance(shapeHandle)) {
		shape = ConvexHullShape::Unwrap(shapeHandle)->_btConvexHullShape;
	} else {
		ThrowException(Exception::TypeError(String::New("Unknown shape type")));
		return scope.Close(Undefined());
	}

	btVector3 localInertia(0, 0, 0);
	shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, NULL, shape, localInertia);
	self->_btRigidBody = new btRigidBody(rbInfo);
	self->_shape = Persistent<Object>::New(shapeHandle);
OBJECT_NEW_END()

OBJECT_DELETE_START(RigidBody)
	delete _btRigidBody;
	_shape.Dispose();
OBJECT_DELETE_END()



OBJECT_GETTER_START(RigidBody,position)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	btVector3 origin = transform.getOrigin();
	result = Util::vectorToObj(origin);
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,position)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	transform.setOrigin(Util::objToVector(value));
	self->_btRigidBody->setWorldTransform(transform);
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,quaternion)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	btQuaternion quaternion = transform.getRotation();
	result = Util::quaternionToObj(quaternion);
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,quaternion)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	transform.setRotation(Util::objToQuaternion(value));
	self->_btRigidBody->setWorldTransform(transform);
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,velocity)
	result = Util::vectorToObj(self->_btRigidBody->getLinearVelocity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,velocity)
	self->_btRigidBody->setLinearVelocity(Util::objToVector(value));
OBJECT_SETTER_END()


OBJECT_GETTER_START(RigidBody,gravity)
	result = Util::vectorToObj(self->_btRigidBody->getGravity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,gravity)
	self->_btRigidBody->setGravity(Util::objToVector(value));
OBJECT_SETTER_END()


OBJECT_FUNCTION_START(RigidBody,applyCentralImpulse)
	self->_btRigidBody->applyCentralImpulse(Util::objToVector(args[0]));
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,applyImpulse)
	self->_btRigidBody->applyImpulse(
		Util::objToVector(args[0]),
		Util::objToVector(args[1])
	);
OBJECT_FUNCTION_END()
