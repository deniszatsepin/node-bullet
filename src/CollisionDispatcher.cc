#include "CollisionDispatcher.h"

Persistent<FunctionTemplate> CollisionDispatcher::constructor;

void
CollisionDispatcher::Initialize(Handle<Object> target) {
	HandleScope scope;

	constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(CollisionDispatcher::New));
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(String::NewSymbol("CollisionDispatcher"));

	Local<ObjectTemplate> proto = constructor->PrototypeTemplate();

	target->Set(String::NewSymbol("CollisionDispatcher"), constructor->GetFunction());
}

Handle<Value>
CollisionDispatcher::New(const Arguments &args) {
	HandleScope scope;

	CollisionDispatcher* collisionDispatcher = new CollisionDispatcher(
		Local<DefaultCollisionConfiguration>::Cast(args[0])
	);
	collisionDispatcher->Wrap(args.This());
	
	return args.This();
}

CollisionDispatcher::CollisionDispatcher(
	Local<DefaultCollisionConfiguration> config
): ObjectWrap() {
	HandleScope scope;

	_config = Persistent<DefaultCollisionConfiguration>::New(config);
	_btCollisionDispatcher = new btCollisionDispatcher(
		ObjectWrap::Unwrap<DefaultCollisionConfiguration>(config)->_btDefaultCollisionConfiguration
	);
}

CollisionDispatcher::~CollisionDispatcher() {
	if(_btCollisionDispatcher)
		delete _btCollisionDispatcher;
	_config.Dispose();
}
