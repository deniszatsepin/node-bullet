#include "SphereShape.h"

OBJECT_INIT_START(SphereShape)
OBJECT_INIT_END()

OBJECT_NEW_START(SphereShape)
	self->shape = new btSphereShape(args[0]->ToNumber()->Value());
OBJECT_NEW_END()

OBJECT_DELETE_START(SphereShape)
	delete shape;
OBJECT_DELETE_END()
