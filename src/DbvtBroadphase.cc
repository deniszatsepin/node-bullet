#include "DbvtBroadphase.h"

OBJECT_INIT_START(DbvtBroadphase)
OBJECT_INIT_END()

OBJECT_NEW_START(DbvtBroadphase)
	self->_btDbvtBroadphase = new btDbvtBroadphase();
OBJECT_NEW_END()

OBJECT_DELETE_START(DbvtBroadphase)
	delete _btDbvtBroadphase;
OBJECT_DELETE_END()
