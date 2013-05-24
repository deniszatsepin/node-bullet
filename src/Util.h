#pragma once

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
using namespace v8;
using namespace node;

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Util {
	public:
	static Handle<Object> vectorToObj(btVector3 v);
	static btVector3 objToVector(Handle<Value> value);
	static Handle<Object> quaternionToObj(btQuaternion q);
	static btQuaternion objToQuaternion(Handle<Value> value);
};
