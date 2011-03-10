Bullet = require '../index'

bullet = new Bullet.Bullet
console.log 'bullet', bullet

defaultCollisionConfiguration = new Bullet.DefaultCollisionConfiguration
console.log 'defaultCollisionConfiguration', defaultCollisionConfiguration

collisionDispatcher = new Bullet.CollisionDispatcher defaultCollisionConfiguration
console.log 'collisionDispatcher', collisionDispatcher

dbvtBroadphase = new Bullet.DbvtBroadphase
console.log 'dbvtBroadphase', dbvtBroadphase

sequentialImpulseConstraintSolver = new Bullet.SequentialImpulseConstraintSolver
console.log 'sequentialImpulseConstraintSolver', sequentialImpulseConstraintSolver

discreteDynamicsWorld = new Bullet.DiscreteDynamicsWorld collisionDispatcher, dbvtBroadphase, sequentialImpulseConstraintSolver, defaultCollisionConfiguration
console.log 'discreteDynamicsWorld', discreteDynamicsWorld

discreteDynamicsWorld.setGravity 0, -9.81, 0

# # boxShape = new Bullet.BoxShape
# # console.log 'boxShape', boxShape

# # transform = new Bullet.Transform
# # console.log 'transform', transform

# API
#   RigidBody(mass)
#     applyImpulse(point, impulse)
#     getPosition()
#     setPosition(x, y, z)
#     setLinearVelocity(x, y, z)
#     setGravity(x, y, z)
#
#   DiscreteDynamicsWorld(dispatcher, broadphase, solver, configuration)
#     addRigidBody(rigid_body)
#     setGravity(x, y, z)


world = new Object

for i in [-32...32]
  for j in [-32...32]
    block = new Bullet.RigidBody 1
    discreteDynamicsWorld.addRigidBody block
    block.setPosition i * 2, 0, j * 2
    
    world["#{i}:#{j}"] = block

b = new Bullet.RigidBody 1
discreteDynamicsWorld.addRigidBody b
b.setPosition 0, 10, 0

tick = ->
  # fps++
  discreteDynamicsWorld.stepSimulation 1 / 120
  
  # b.applyImpulse 0, -0.01, 0, 0, 0.5, 0

setInterval tick, 1000 / 120

setInterval ->
  b.setPosition 0, 0, 0
, 1000

console.log 'test'