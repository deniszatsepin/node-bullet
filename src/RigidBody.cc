#include "RigidBody.h"

#include <iostream>

Persistent<FunctionTemplate> RigidBody::constructor;

void
RigidBody::Initialize(Handle<Object> target) {
  HandleScope scope;

  constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(RigidBody::New));
  constructor->InstanceTemplate()->SetInternalFieldCount(1);
  constructor->SetClassName(String::NewSymbol("RigidBody"));
  
  NODE_SET_PROTOTYPE_METHOD(constructor, "getWorldTransform", GetWorldTransform);

  Local<ObjectTemplate> proto = constructor->PrototypeTemplate();

  target->Set(String::NewSymbol("RigidBody"), constructor->GetFunction());
}

Handle<Value>
RigidBody::New(const Arguments &args) {
  HandleScope scope;
  
  RigidBody* rigidBody = new RigidBody();
  rigidBody->Wrap(args.This());
  
  return scope.Close(args.This());
}

RigidBody::RigidBody(): ObjectWrap() {  
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(0.0, 0.0, 0.0));
  
  btScalar mass(1.0);
  
  btVector3 localInertia(0, 0, 0);
  
  btDefaultMotionState* defaultMotionState = new btDefaultMotionState(transform);
  
  btCollisionShape* collisionShape = new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0)));
  collisionShape->calculateLocalInertia(mass, localInertia);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, defaultMotionState, collisionShape, localInertia);
  _btRigidBody = new btRigidBody(rbInfo);
}

RigidBody::~RigidBody() {
  if (_btRigidBody) {
    //delete _btRigidBody;
  }
}

Handle<Value>
RigidBody::GetWorldTransform(const Arguments &args) {
  HandleScope scope;
  
  RigidBody* body = ObjectWrap::Unwrap<RigidBody>(args.This());
  
  btTransform transform;
  body->_btRigidBody->getMotionState()->getWorldTransform(transform);
  
  transform.setOrigin(btVector3(0.0, 0.0, 0.0));
  
  Handle<Number> x = Number::New(transform.getOrigin().getX());
  
  printf("%f", transform.getOrigin().x());
  
  return scope.Close(x);
}