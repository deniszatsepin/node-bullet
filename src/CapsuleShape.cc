#include "CapsuleShape.h"

OBJECT_INIT_START(CapsuleShape)
OBJECT_INIT_END()

OBJECT_NEW_START(CapsuleShape)
	self->shape = new btCapsuleShape(
		args[0]->ToNumber()->Value(),
		args[1]->ToNumber()->Value()
	);
OBJECT_NEW_END()

OBJECT_DELETE_START(CapsuleShape)
	delete shape;
OBJECT_DELETE_END()
