#include "DiscreteDynamicsWorld.h"
#include "BulletCollision/CollisionDispatch/btInternalEdgeUtility.h"

extern ContactAddedCallback gContactAddedCallback;
static bool CustomMaterialCombinerCallback(btManifoldPoint& cp,	const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
{
	printf("FIX");
	btAdjustInternalEdgeContacts(cp,colObj1Wrap,colObj0Wrap, partId1,index1);
	//btAdjustInternalEdgeContacts(cp,colObj1,colObj0, partId1,index1, BT_TRIANGLE_CONVEX_BACKFACE_MODE);
	//btAdjustInternalEdgeContacts(cp,colObj1,colObj0, partId1,index1, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);

	return false;
}

OBJECT_INIT_START(DiscreteDynamicsWorld)
	gContactAddedCallback = CustomMaterialCombinerCallback;

	OBJECT_INIT_ACCESSOR(gravity)
	OBJECT_INIT_FUNCTION(addRigidBody);
	OBJECT_INIT_FUNCTION(removeRigidBody);
	OBJECT_INIT_FUNCTION(step);
	OBJECT_INIT_FUNCTION(sweep);
OBJECT_INIT_END()

OBJECT_NEW_START(DiscreteDynamicsWorld)
	self->_dispatcher = Persistent<Object>::New(args[0]->ToObject());
	self->_broadphase = Persistent<Object>::New(args[1]->ToObject());
	self->_solver = Persistent<Object>::New(args[2]->ToObject());
	self->_config = Persistent<Object>::New(args[3]->ToObject());

	self->world = new btDiscreteDynamicsWorld(
		CollisionDispatcher::Unwrap(self->_dispatcher)->_btCollisionDispatcher,
		DbvtBroadphase::Unwrap(self->_broadphase)->_btDbvtBroadphase,
		SequentialImpulseConstraintSolver::Unwrap(self->_solver)->_btSequentialImpulseConstraintSolver,
		DefaultCollisionConfiguration::Unwrap(self->_config)->_btDefaultCollisionConfiguration
	);

	self->world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
OBJECT_NEW_END()

OBJECT_DELETE_START(DiscreteDynamicsWorld)
	delete world;

	_dispatcher.Dispose();
	_broadphase.Dispose();
	_solver.Dispose();
	_config.Dispose();

	for(std::map< RigidBody*, Persistent<Object> >::iterator it=_bodies.begin(); it != _bodies.end(); ++it)
		it->second.Dispose();
OBJECT_DELETE_END()

OBJECT_GETTER_START(DiscreteDynamicsWorld,gravity)
	result = Util::vectorToObj(self->world->getGravity());
OBJECT_GETTER_END()
OBJECT_SETTER_START(DiscreteDynamicsWorld,gravity)
	self->world->setGravity(Util::objToVector(value));
OBJECT_SETTER_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,addRigidBody)
	Local<Object> obj = args[0]->ToObject();
	RigidBody* rigidBody = RigidBody::Unwrap(obj);
	self->world->addRigidBody(rigidBody->body);
	self->_bodies[rigidBody] = Persistent<Object>::New(obj);
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,removeRigidBody)
	RigidBody* rigidBody = RigidBody::Unwrap(args[0]);
	self->world->removeRigidBody(rigidBody->body);
	self->_bodies[rigidBody].Dispose();
	self->_bodies.erase(rigidBody);
OBJECT_FUNCTION_END()

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,step)
	self->world->stepSimulation(
		args[0]->ToNumber()->Value(),
		0
	);
OBJECT_FUNCTION_END()










// Sweeper
/*
struct ContactCallback : public btCollisionWorld::ContactResultCallback
{
public:
	bool contacted = false;

	virtual btScalar addSingleResult(
		btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObj0Wrap,
		int partId0,int index0,
		const btCollisionObjectWrapper* colObj1Wrap,
		int partId1,int index1
	) {
		contacted = true;
		return btScalar(1.0);
	}
};
*/
class SweepCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
	btCollisionObject* m_me;
	btVector3 m_up;
	btScalar m_minSlopeDot;
	btScalar m_maxSlopeDot;

public:
	SweepCallback()
	: btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
	{
		m_me = NULL;
		m_minSlopeDot = -2;
		m_maxSlopeDot = -2;
	}

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult,bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == m_me)
			return btScalar(1.0);

		btVector3 hitNormalWorld;
		if(normalInWorldSpace)
			hitNormalWorld = convexResult.m_hitNormalLocal;
		else
			hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis()*convexResult.m_hitNormalLocal;

		btScalar dotUp = m_up.dot(hitNormalWorld);
		if(m_minSlopeDot != -2 && m_maxSlopeDot != -2 && m_maxSlopeDot < m_minSlopeDot) {
			// excluded zone
			if(dotUp > m_maxSlopeDot && dotUp < m_minSlopeDot)
				return btScalar(1.0);
		} else {
			// min and max
			if(m_minSlopeDot != -2 && dotUp < m_minSlopeDot)
				return btScalar(1.0);
			if(m_maxSlopeDot != -2 && dotUp > m_maxSlopeDot)
				return btScalar(1.0);
		}

		return ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}
};

OBJECT_FUNCTION_START(DiscreteDynamicsWorld,sweep)
	RigidBody* rigidBody = RigidBody::Unwrap(args[0]);
	btVector3 startv = Util::objToVector(args[1]);
	btVector3 endv = Util::objToVector(args[2]);
	btVector3 up = Util::objToVector(args[3]);
	btScalar minSlopeDot = args[4]->ToNumber()->Value();
	btScalar maxSlopeDot = args[5]->ToNumber()->Value();
	
	btRigidBody* body = rigidBody->body;
	btConvexShape* shape = (btConvexShape*)body->getCollisionShape();

	btTransform start, end;
	start.setIdentity();
	start.setOrigin(startv);
	end.setIdentity();
	end.setOrigin(endv);
	
	// check for collisions at the start pos
/*	ContactCallback ccallback;
	btTransform orig = body->getWorldTransform();
	body->setWorldTransform(start);
	self->world->contactTest(body, ccallback);
	body->setWorldTransform(orig);
	if(ccallback.contacted) {

		// collision at the start position
		result = String::New("start");

	} else if(startv == endv) {

		result = String::New("end");

	} else {
*/
		SweepCallback callback;
		callback.m_me = body;
		callback.m_up = up;
		callback.m_minSlopeDot = minSlopeDot;
		callback.m_maxSlopeDot = maxSlopeDot;
		self->world->convexSweepTest(
			shape, start, end, callback,
			self->world->getDispatchInfo().m_allowedCcdPenetration
		);

		if(callback.hasHit()) {
			// collision in the sweep
			Handle<Object> o = Object::New();
			o->Set(String::New("dot"), Number::New(callback.m_hitNormalWorld.dot(up)));
			o->Set(String::New("fraction"), Number::New(callback.m_closestHitFraction));
			result = o;
		} else {
			// no collisions anywhere
			result = String::New("end");
		}
	
//	}
OBJECT_FUNCTION_END()

