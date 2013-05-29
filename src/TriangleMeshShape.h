#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"

OBJECT_DEF_START(TriangleMeshShape)
	btBvhTriangleMeshShape* shape;
	btVector3* vertices;
	int* triangles;
	btTriangleIndexVertexArray* vertexArray;
OBJECT_DEF_END()
