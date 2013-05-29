#include "TriangleMeshShape.h"

OBJECT_INIT_START(TriangleMeshShape)
OBJECT_INIT_END()

OBJECT_NEW_START(TriangleMeshShape)
	if(!args[0]->IsArray()) return ThrowException(String::New("Invalid Argument"));
	if(!args[1]->IsArray()) return ThrowException(String::New("Invalid Argument"));

	Local<Array> verts = Local<Array>(Array::Cast(*args[0]));
	int vertCount = verts->Length()/3;
	Local<Array> tris = Local<Array>(Array::Cast(*args[1]));
	int triCount = tris->Length()/3;

	self->vertices = new btVector3[vertCount];
	for(int i = 0; i < vertCount; i++) {
		self->vertices[i].setValue(
			verts->Get(Integer::New(i*3))->ToNumber()->Value(),
			verts->Get(Integer::New(i*3+1))->ToNumber()->Value(),
			verts->Get(Integer::New(i*3+2))->ToNumber()->Value()
		);
	}
	self->triangles = new int[triCount*3];
	for(int i = 0; i < triCount; i++) {
		self->triangles[i*3] = tris->Get(Integer::New(i*3))->ToNumber()->Value();
		self->triangles[i*3+1] = tris->Get(Integer::New(i*3+1))->ToNumber()->Value();
		self->triangles[i*3+2] = tris->Get(Integer::New(i*3+2))->ToNumber()->Value();
	}

	self->vertexArray = new btTriangleIndexVertexArray(
		triCount, self->triangles, 3*sizeof(int),
		vertCount, (btScalar*)&self->vertices[0].x(), sizeof(btVector3)
	);

	self->shape = new btBvhTriangleMeshShape(self->vertexArray,true);
OBJECT_NEW_END()

OBJECT_DELETE_START(TriangleMeshShape)
	delete shape;
	delete vertexArray;
	delete[] triangles;
	delete[] vertices;
OBJECT_DELETE_END()
