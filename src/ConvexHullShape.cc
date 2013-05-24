#include "ConvexHullShape.h"

OBJECT_INIT_START(ConvexHullShape)
	OBJECT_INIT_FUNCTION(addPoint);
OBJECT_INIT_END()

OBJECT_NEW_START(ConvexHullShape)
	self->_btConvexHullShape = new btConvexHullShape();
OBJECT_NEW_END()

OBJECT_DELETE_START(ConvexHullShape)
	delete _btConvexHullShape;
OBJECT_DELETE_END()

OBJECT_FUNCTION_START(ConvexHullShape,addPoint)
	self->_btConvexHullShape->addPoint(btVector3(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value(),
		args[2]->ToNumber()->Value()
	));
OBJECT_FUNCTION_END()
