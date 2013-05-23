#include "SequentialImpulseConstraintSolver.h"

OBJECT_INIT_START(SequentialImpulseConstraintSolver)
OBJECT_INIT_END()

OBJECT_NEW_START(SequentialImpulseConstraintSolver)
	self->_btSequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver();
OBJECT_NEW_END()

OBJECT_DELETE_START(SequentialImpulseConstraintSolver)
	delete _btSequentialImpulseConstraintSolver;
OBJECT_DELETE_END()
