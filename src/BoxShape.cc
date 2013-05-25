#include "BoxShape.h"

OBJECT_INIT_START(BoxShape)
OBJECT_INIT_END()

OBJECT_NEW_START(BoxShape)
	self->_btBoxShape = new btBoxShape(Util::objToVector(args[0]));
OBJECT_NEW_END()

OBJECT_DELETE_START(BoxShape)
	delete _btBoxShape;
OBJECT_DELETE_END()
