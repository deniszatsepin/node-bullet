#include "RigidBody.h"

Persistent<FunctionTemplate> RigidBody::constructor;

void
RigidBody::Initialize(Handle<Object> target) {
  HandleScope scope;

  constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(RigidBody::New));
  constructor->InstanceTemplate()->SetInternalFieldCount(1);
  constructor->SetClassName(String::NewSymbol("RigidBody"));
  
  NODE_SET_PROTOTYPE_METHOD(constructor, "getPosition", GetPosition);
  NODE_SET_PROTOTYPE_METHOD(constructor, "setPosition", SetPosition);

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
  btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0)));
  groundShape->calculateLocalInertia(mass, localInertia);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, defaultMotionState, groundShape, localInertia);
  _btRigidBody = new btRigidBody(rbInfo);
}

RigidBody::~RigidBody() {
  if (_btRigidBody) {
    //delete _btRigidBody;
  }
}

Handle<Value>
RigidBody::GetPosition(const Arguments &args) {
  HandleScope scope;
  
  RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
  
  btTransform transform;
  rigidBody->_btRigidBody->getMotionState()->getWorldTransform(transform);
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
  
  btTransform transform;
  rigidBody->_btRigidBody->getMotionState()->getWorldTransform(transform);
  // btVector3 origin = transform.getOrigin();
  transform.setOrigin(btVector3(x, y, z));
  rigidBody->_btRigidBody->setWorldTransform(transform);
  return scope.Close(Undefined());
}