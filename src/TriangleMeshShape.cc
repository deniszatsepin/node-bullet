#include "ConvexHullShape.h"

OBJECT_INIT_START(TriangleMeshShape)
OBJECT_INIT_END()

OBJECT_NEW_START(TriangleMeshShape)
	Local<Array> verts = args[0]->ToArray();
	int vertCount = verts->Length()/3;
	Local<Array> tris = args[1]->ToArray();
	int triCount = tris->Length()/3;

	self->vertices = new btVector3[vertCount];
	for(int i = 0; i < vertCount; i++) {
		vertices[i].setValue(
			verts->Get(Integer::New(i*3))->ToNumber()->Value(),
			verts->Get(Integer::New(i*3+1))->ToNumber()->Value(),
			verts->Get(Integer::New(i*3+2))->ToNumber()->Value()
		);
	}
	self->triangles = new int[triCount*3];
	for(int i = 0; i < triCount; i++) {
		triangles[i*3] = tris->Get(Integer::New(i*3))->ToNumber()->Value();
		triangles[i*3+1] = tris->Get(Integer::New(i*3+1))->ToNumber()->Value();
		triangles[i*3+2] = tris->Get(Integer::New(i*3+2))->ToNumber()->Value();
	}

	self->vertexArray = new btTriangleIndexVertexArray(
		triCount, self->triangles, 3*sizeof(int),
		vertCount, (btScalar*)&self->vertices[0].x(), sizeof(btVector3)
	);

	self->shape = new btBvhTriangleMeshShape(self->vertexArray,true);
OBJECT_NEW_END()

OBJECT_DELETE_START(ConvexHullShape)
	delete shape;
	delete vertexArray;
	delete[] triangles;
	delete[] vertices;
OBJECT_DELETE_END()
