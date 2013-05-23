#include "ConvexHullShape.h"

OBJECT_INIT_START(ConvexHullShape)
OBJECT_INIT_END()

OBJECT_NEW_START(ConvexHullShape)
	self->_btConvexHullShape = new btConvexHullShape();
OBJECT_NEW_END()

OBJECT_DELETE_START(ConvexHullShape)
	delete _btConvexHullShape;
OBJECT_DELETE_END()
