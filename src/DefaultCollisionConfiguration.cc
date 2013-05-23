#include "DefaultCollisionConfiguration.h"

OBJECT_INIT_START(DefaultCollisionConfiguration)
OBJECT_INIT_END()

OBJECT_NEW_START(DefaultCollisionConfiguration)
	self->_btDefaultCollisionConfiguration = new btDefaultCollisionConfiguration();
OBJECT_NEW_END()

OBJECT_DELETE_START(DefaultCollisionConfiguration)
	delete _btDefaultCollisionConfiguration;
OBJECT_DELETE_END()
