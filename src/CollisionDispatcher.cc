#include "CollisionDispatcher.h"

OBJECT_INIT_START(CollisionDispatcher)
OBJECT_INIT_END()

OBJECT_NEW_START(CollisionDispatcher)
	self->_config = Persistent<Object>::New(args[0]->ToObject());
	self->_btCollisionDispatcher = new btCollisionDispatcher(
		ObjectWrap::Unwrap<DefaultCollisionConfiguration>(self->_config)->_btDefaultCollisionConfiguration
	);
OBJECT_NEW_END()

OBJECT_DELETE_START(CollisionDispatcher)
	delete _btCollisionDispatcher;
	_config.Dispose();
OBJECT_DELETE_END()
