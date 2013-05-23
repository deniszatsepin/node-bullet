#include "RigidBody.h"
#include "BoxShape.h"

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



Handle<Value>
RigidBody::GetPosition(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	btTransform transform = rigidBody->_btRigidBody->getWorldTransform();
	btVector3 origin = transform.getOrigin();
	
	Handle<Object> o = Object::New();
	Handle<Number> x_handle = Number::New(origin.getX());
	Handle<Number> y_handle = Number::New(origin.getY());
	Handle<Number> z_handle = Number::New(origin.getZ());
	o->Set(String::New("x"), x_handle);
	o->Set(String::New("y"), y_handle);
	o->Set(String::New("z"), z_handle);
	return scope.Close(o);
}

Handle<Value>
RigidBody::SetPosition(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	double x = args[0]->ToNumber()->Value();
	double y = args[1]->ToNumber()->Value();
	double z = args[2]->ToNumber()->Value();
	
	btTransform transform = rigidBody->_btRigidBody->getWorldTransform();
	transform.setOrigin(btVector3(x, y, z));
	rigidBody->_btRigidBody->setWorldTransform(transform);
	return scope.Close(Undefined());
}

Handle<Value>
RigidBody::SetLinearVelocity(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	double x = args[0]->ToNumber()->Value();
	double y = args[1]->ToNumber()->Value();
	double z = args[2]->ToNumber()->Value();
	
	rigidBody->_btRigidBody->setLinearVelocity(btVector3(x, y, z));
	return scope.Close(Undefined());
}

Handle<Value>
RigidBody::SetGravity(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	double x = args[0]->ToNumber()->Value();
	double y = args[1]->ToNumber()->Value();
	double z = args[2]->ToNumber()->Value();
	
	rigidBody->_btRigidBody->setGravity(btVector3(x, y, z));
	return scope.Close(Undefined());
}

Handle<Value>
RigidBody::ApplyCentralImpulse(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	double x = args[0]->ToNumber()->Value();
	double y = args[1]->ToNumber()->Value();
	double z = args[2]->ToNumber()->Value();
	
	rigidBody->_btRigidBody->applyCentralImpulse(btVector3(x, y, z));
	
	return scope.Close(Undefined());
}

Handle<Value>
RigidBody::ApplyImpulse(const Arguments &args) {
	HandleScope scope;
	
	RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
	
	double px = args[0]->ToNumber()->Value();
	double py = args[1]->ToNumber()->Value();
	double pz = args[2]->ToNumber()->Value();
	
	double ix = args[3]->ToNumber()->Value();
	double iy = args[4]->ToNumber()->Value();
	double iz = args[5]->ToNumber()->Value();
	
	rigidBody->_btRigidBody->applyImpulse(btVector3(px, py, pz), btVector3(ix, iy, iz));
	
	return scope.Close(Undefined());
}
