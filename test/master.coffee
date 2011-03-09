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

discreteDynamicsWorld.setGravity 0, -10, 0

# # boxShape = new Bullet.BoxShape
# # console.log 'boxShape', boxShape

# # transform = new Bullet.Transform
# # console.log 'transform', transform

rigidBody = new Bullet.RigidBody
console.log 'rigidBody', rigidBody
discreteDynamicsWorld.addRigidBody rigidBody

# rigidBody2 = new Bullet.RigidBody
# console.log 'rigidBody', rigidBody2
# discreteDynamicsWorld.addRigidBody rigidBody2
# 
# rigidBody3 = new Bullet.RigidBody
# console.log 'rigidBody', rigidBody3
# discreteDynamicsWorld.addRigidBody rigidBody3

fps = 0

tick = ->
  fps++
  discreteDynamicsWorld.stepSimulation 1 / 60
  position = rigidBody.getPosition()
  # rigidBody.setPosition 0, position.y, 0
  process.nextTick tick
  
  console.log position

setInterval tick, 1000 / 10

# setInterval(->
#   console.log fps
#   # fps = 0
# , 1000)