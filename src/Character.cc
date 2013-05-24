#include "Character.h"
/*
OBJECT_INIT_START(Character)
OBJECT_INIT_END()

OBJECT_NEW_START(Character)
	self->_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);
	btScalar characterHeight=1.75;
	btScalar characterWidth =1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.35);
	m_character = new btKinematicCharacterController (m_ghostObject,capsule,stepHeight);
OBJECT_NEW_END()

OBJECT_DELETE_START(Character)
	delete _btSequentialImpulseConstraintSolver;
OBJECT_DELETE_END()
*/