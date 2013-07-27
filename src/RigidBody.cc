#include "RigidBody.h"
#include "BoxShape.h"
#include "SphereShape.h"
#include "CapsuleShape.h"
#include "CylinderShape.h"
#include "ConvexHullShape.h"
#include "TriangleMeshShape.h"

OBJECT_INIT_START(RigidBody)
	OBJECT_INIT_ACCESSOR(ccdMotionThreshold);
	OBJECT_INIT_ACCESSOR(ccdSweptSphereRadius);
	OBJECT_INIT_ACCESSOR(angularDamping);
	OBJECT_INIT_ACCESSOR(linearDamping);
	OBJECT_INIT_ACCESSOR(position);
	OBJECT_INIT_ACCESSOR(quaternion);
	OBJECT_INIT_ACCESSOR(velocity);
	OBJECT_INIT_ACCESSOR(gravity);
	OBJECT_INIT_ACCESSOR(kinematic);
	OBJECT_INIT_ACCESSOR(restitution);
	OBJECT_INIT_ACCESSOR(friction);

	OBJECT_INIT_FUNCTION(activate);
	OBJECT_INIT_FUNCTION(applyImpulse);
	OBJECT_INIT_FUNCTION(applyCentralImpulse);
	OBJECT_INIT_FUNCTION(setLinearFactor);
	OBJECT_INIT_FUNCTION(setAngularFactor);
OBJECT_INIT_END()

OBJECT_NEW_START(RigidBody)
	double mass = args[0]->ToNumber()->Value();
	Local<Object> shapeHandle = args[1]->ToObject();

	btCollisionShape* shape;
	bool customMaterialCallback = false;
	if(BoxShape::HasInstance(shapeHandle)) {
		shape = BoxShape::Unwrap(shapeHandle)->_btBoxShape;
	} else if(SphereShape::HasInstance(shapeHandle)) {
		shape = SphereShape::Unwrap(shapeHandle)->shape;
	} else if(CapsuleShape::HasInstance(shapeHandle)) {
		shape = CapsuleShape::Unwrap(shapeHandle)->shape;
	} else if(CylinderShape::HasInstance(shapeHandle)) {
		shape = CylinderShape::Unwrap(shapeHandle)->shape;
	} else if(ConvexHullShape::HasInstance(shapeHandle)) {
		shape = ConvexHullShape::Unwrap(shapeHandle)->_btConvexHullShape;
	} else if(TriangleMeshShape::HasInstance(shapeHandle)) {
		shape = TriangleMeshShape::Unwrap(shapeHandle)->shape;
		customMaterialCallback = true;
	} else {
		ThrowException(Exception::TypeError(String::New("Unknown shape type")));
		return scope.Close(Undefined());
	}

	btVector3 localInertia(0, 0, 0);
	shape->calculateLocalInertia(mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, NULL, shape, localInertia);
	self->body = new btRigidBody(rbInfo);
	self->_shape = Persistent<Object>::New(shapeHandle);

	if(customMaterialCallback) {
		self->body->setCollisionFlags(
			self->body->getCollisionFlags()
			| btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK
		);
	}

OBJECT_NEW_END()

OBJECT_DELETE_START(RigidBody)
	delete body;
	_shape.Dispose();
OBJECT_DELETE_END()


OBJECT_GETTER_START(RigidBody,ccdMotionThreshold)
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,ccdMotionThreshold)
	self->body->setCcdMotionThreshold(value->ToNumber()->Value());
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,ccdSweptSphereRadius)
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,ccdSweptSphereRadius)
	self->body->setCcdSweptSphereRadius(value->ToNumber()->Value());
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,angularDamping)
	result = Number::New(self->body->getAngularDamping());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,angularDamping)
	self->body->setDamping(self->body->getLinearDamping(),value->ToNumber()->Value());
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,linearDamping)
	result = Number::New(self->body->getLinearDamping());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,linearDamping)
	self->body->setDamping(value->ToNumber()->Value(),self->body->getAngularDamping());
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,position)
	btTransform transform = self->body->getWorldTransform();
	btVector3 origin = transform.getOrigin();
	result = Util::vectorToObj(origin);
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,position)
	btTransform transform = self->body->getWorldTransform();
	transform.setOrigin(Util::objToVector(value));
	self->body->setWorldTransform(transform);
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,quaternion)
	btTransform transform = self->body->getWorldTransform();
	btQuaternion quaternion = transform.getRotation();
	result = Util::quaternionToObj(quaternion);
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,quaternion)
	btTransform transform = self->body->getWorldTransform();
	transform.setRotation(Util::objToQuaternion(value));
	self->body->setWorldTransform(transform);
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,velocity)
	result = Util::vectorToObj(self->body->getLinearVelocity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,velocity)
	self->body->setLinearVelocity(Util::objToVector(value));
OBJECT_SETTER_END()


OBJECT_GETTER_START(RigidBody,gravity)
	result = Util::vectorToObj(self->body->getGravity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,gravity)
	self->body->setGravity(Util::objToVector(value));
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,kinematic)
	result = Boolean::New(
		(self->body->getCollisionFlags() & btCollisionObject::CF_KINEMATIC_OBJECT) != 0
	);
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,kinematic)
	bool state = value->ToBoolean()->Value();

	int flags = self->body->getCollisionFlags();
	if(state)
		flags |= btCollisionObject::CF_KINEMATIC_OBJECT;
	else
		flags &= ~(btCollisionObject::CF_KINEMATIC_OBJECT);

	self->body->setCollisionFlags(flags);
	if(!state) self->body->activate();
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,restitution)
	result = Number::New(self->body->getRestitution());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,restitution)
	self->body->setRestitution(value->ToNumber()->Value());
OBJECT_SETTER_END()

OBJECT_GETTER_START(RigidBody,friction)
	result = Number::New(self->body->getFriction());
OBJECT_GETTER_END()
OBJECT_SETTER_START(RigidBody,friction)
	self->body->setFriction(value->ToNumber()->Value());
OBJECT_SETTER_END()

OBJECT_FUNCTION_START(RigidBody,activate)
	self->body->activate();
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,applyCentralImpulse)
	self->body->applyCentralImpulse(Util::objToVector(args[0]));
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,applyImpulse)
	self->body->applyImpulse(
		Util::objToVector(args[0]),
		Util::objToVector(args[1])
	);
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(RigidBody,setLinearFactor)
	self->body->setLinearFactor(Util::objToVector(args[0]));
OBJECT_FUNCTION_END()
OBJECT_FUNCTION_START(RigidBody,setAngularFactor)
	self->body->setAngularFactor(Util::objToVector(args[0]));
OBJECT_FUNCTION_END()
