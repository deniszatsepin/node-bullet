#include "RigidBody.h"
#include "BoxShape.h"
#include "ConvexHullShape.h"

OBJECT_INIT_START(RigidBody)
	NODE_SET_PROTOTYPE_METHOD(constructor, "getPosition", GetPosition);
	NODE_SET_PROTOTYPE_METHOD(constructor, "setPosition", SetPosition);
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
	Handle<Number> x_handle = Number::New(origin.getX());
	Handle<Number> y_handle = Number::New(origin.getY());
	Handle<Number> z_handle = Number::New(origin.getZ());
	o->Set(String::New("x"), x_handle);
	o->Set(String::New("y"), y_handle);
	o->Set(String::New("z"), z_handle);
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
