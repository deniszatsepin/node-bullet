#include "RigidBody.h"

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
RigidBody::GetWorldTransform(const Arguments &args) {
  HandleScope scope;
  
  // btTransform transform;
  // _btRigidBody->getMotionState()->getWorldTransform(transform);
  
  // printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
  
  //print positions of all objects
  
  RigidBody* rigidBody = ObjectWrap::Unwrap<RigidBody>(args.This());
  
  float x, y, z = 0;
  
  for (int j = rigidBody->_btDiscreteDynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
    btCollisionObject* obj = rigidBody->_btDiscreteDynamicsWorld->getCollisionObjectArray()[j];
    btRigidBody* body = btRigidBody::upcast(obj);
    if (body && body->getMotionState()) {
      btTransform trans;
      body->getMotionState()->getWorldTransform(trans);
      printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
      // Handle<Number> y = Number::New(trans.getOrigin().getY());
      // return scope.Close(y);
    }
  }
  Handle<Number> xx = Number::New(x);
  return scope.Close(xx);
}

