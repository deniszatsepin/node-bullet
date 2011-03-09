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

// Handle<Value> GetX(Local<String> property, const AccessorInfo &info) {
//   Local<Object> self = info.Holder();
//   Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
//   void* ptr = wrap->Value();
//   int value = static_cast<Point*>(ptr)->x_;
//   return Integer::New(value);
// }
// 
// void SetX(Local<String> property, Local<Value> value, const AccessorInfo& info) {
//   Local<Object> self = info.Holder();
//   Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
//   void* ptr = wrap->Value();
//   static_cast<Point*>(ptr)->x_ = value->Int32Value();
// }

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
  Handle<Object> o = Object::New();
  Handle<Number> x_handle = Number::New(100);
  Handle<Number> y_handle = Number::New(150);
  Handle<Number> z_handle = Number::New(200);
  o->Set(String::New("x"), x_handle);
  o->Set(String::New("y"), y_handle);
  o->Set(String::New("z"), z_handle);
  return scope.Close(o);
}