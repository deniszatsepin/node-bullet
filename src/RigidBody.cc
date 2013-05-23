#include "RigidBody.h"
#include "BoxShape.h"
#include "ConvexHullShape.h"

OBJECT_INIT_START(RigidBody)
	NODE_SET_PROTOTYPE_METHOD(constructor, "getPosition", GetPosition);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setPosition", SetPosition);
	NODE_SET_PROTOTYPE_METHOD(constructor, "getRotation", GetRotation);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setRotation", SetRotation);

	NODE_SET_PROTOTYPE_METHOD(constructor, "setLinearVelocity", SetLinearVelocity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setGravity", SetGravity);
	NODE_SET_PROTOTYPE_METHOD(constructor, "applyImpulse", ApplyImpulse);
	NODE_SET_PROTOTYPE_METHOD(constructor, "applyCentralImpulse", ApplyCentralImpulse);
OBJECT_INIT_END()

OBJECT_NEW_START(RigidBody)
	double mass = args[0]->ToNumber()->Value();
	Local<Object> shapeHandle = args[1]->ToObject();

	btCollisionShape* shape;
	if(BoxShape::constructor->HasInstance(shapeHandle)) {
		shape = ObjectWrap::Unwrap<BoxShape>(shapeHandle)->_btBoxShape;
	} else if(ConvexHullShape::constructor->HasInstance(shapeHandle)) {
		shape = ObjectWrap::Unwrap<ConvexHullShape>(shapeHandle)->_btConvexHullShape;
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



OBJECT_FUNCTION_START(RigidBody,GetPosition)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	btVector3 origin = transform.getOrigin();

	Handle<Object> o = Object::New();
	o->Set(String::New("x"), Number::New(origin.getX()));
	o->Set(String::New("y"), Number::New(origin.getY()));
	o->Set(String::New("z"), Number::New(origin.getZ()));
	return scope.Close(o);
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,SetPosition)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	transform.setOrigin(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
	self->_btRigidBody->setWorldTransform(transform);
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,GetRotation)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	btQuaternion orientation = transform.getRotation();

	Handle<Object> o = Object::New();
	o->Set(String::New("x"), Number::New(orientation.getX()));
	o->Set(String::New("y"), Number::New(orientation.getY()));
	o->Set(String::New("z"), Number::New(orientation.getZ()));
	o->Set(String::New("w"), Number::New(orientation.getW()));
	return scope.Close(o);
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,SetRotation)
	btTransform transform = self->_btRigidBody->getWorldTransform();
	transform.setRotation(btQuaternion(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value(),
		args[3]->ToNumber()->Value()
	));
	self->_btRigidBody->setWorldTransform(transform);
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()





OBJECT_FUNCTION_START(RigidBody,SetLinearVelocity)
	self->_btRigidBody->setLinearVelocity(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,SetGravity)
	self->_btRigidBody->setGravity(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,ApplyCentralImpulse)
	self->_btRigidBody->applyCentralImpulse(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,ApplyImpulse)
	self->_btRigidBody->applyImpulse(
		btVector3(
			args[0]->ToNumber()->Value(),
			args[1]->ToNumber()->Value(),
			args[2]->ToNumber()->Value()
		),
		btVector3(
			args[3]->ToNumber()->Value(),
			args[4]->ToNumber()->Value(),
			args[5]->ToNumber()->Value()
		)
	);
	return scope.Close(Undefined());
OBJECT_FUNCTION_END()
