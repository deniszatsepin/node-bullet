#include "Util.h"

Handle<Object> Util::vectorToObj(btVector3 v) {
	Handle<Object> o = Object::New();
	o->Set(String::New("x"), Number::New(v.getX()));
	o->Set(String::New("y"), Number::New(v.getY()));
	o->Set(String::New("z"), Number::New(v.getZ()));
	return o;
}

btVector3 Util::objToVector(Handle<Value> value) {
	Handle<Object> obj = value->ToObject();
	return btVector3(
		obj->Get(String::New("x"))->ToNumber()->Value(),
		obj->Get(String::New("y"))->ToNumber()->Value(),
		obj->Get(String::New("z"))->ToNumber()->Value()
	);
}

Handle<Object> Util::quaternionToObj(btQuaternion q) {
	Handle<Object> o = Object::New();
	o->Set(String::New("x"), Number::New(q.getX()));
	o->Set(String::New("y"), Number::New(q.getY()));
	o->Set(String::New("z"), Number::New(q.getZ()));
	o->Set(String::New("w"), Number::New(q.getW()));
	return o;
}

btQuaternion Util::objToQuaternion(Handle<Value> value) {
	Handle<Object> obj = value->ToObject();
	return btQuaternion(
		obj->Get(String::New("x"))->ToNumber()->Value(),
		obj->Get(String::New("y"))->ToNumber()->Value(),
		obj->Get(String::New("z"))->ToNumber()->Value(),
		obj->Get(String::New("w"))->ToNumber()->Value()
	);
}
