#include "DbvtBroadphase.h"

OBJECT_INIT_START(DbvtBroadphase)
OBJECT_INIT_END()

OBJECT_NEW_START(DbvtBroadphase)
	self->_btDbvtBroadphase = new btDbvtBroadphase();

	// set up the ghost pair callback so that ghost objects
	// are handled correctly
	self->_ghostPairCallback = new btGhostPairCallback();
	self->_btDbvtBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(self->_ghostPairCallback);
OBJECT_NEW_END()

OBJECT_DELETE_START(DbvtBroadphase)
	delete _btDbvtBroadphase;
	delete _ghostPairCallback;
OBJECT_DELETE_END()
