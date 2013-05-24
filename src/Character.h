#pragma once
#include "Object.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

OBJECT_DEF_START(Character)
	btKinematicCharacterController* controller;
OBJECT_DEF_END()
