#include "Transform.h"

OBJECT_INIT_START(Transform)
OBJECT_INIT_END()

OBJECT_NEW_START(Transform)
	self->_btTransform = new btTransform();
	// TODO move these out to methods
	self->_btTransform->setIdentity();
	self->_btTransform->setOrigin(btVector3(0, 0, 0));
OBJECT_NEW_END()

OBJECT_DELETE_START(Transform)
	delete _btTransform;
OBJECT_DELETE_END()
