#include "CylinderShape.h"

OBJECT_INIT_START(CylinderShape)
OBJECT_INIT_END()

OBJECT_NEW_START(CylinderShape)
	self->shape = new btCylinderShape(Util::objToVector(args[0]));
OBJECT_NEW_END()

OBJECT_DELETE_START(CylinderShape)
	delete shape;
OBJECT_DELETE_END()
