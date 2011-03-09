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

world = new Object

for i in [0...16]
  for j in [0...16]
    block = new Bullet.RigidBody 0
    discreteDynamicsWorld.addRigidBody block
    block.setPosition i * 2, 0, j * 2
    # block.setGravity 0, 0, 0
    
    world["#{i}:#{j}"] = block

b = new Bullet.RigidBody 1
discreteDynamicsWorld.addRigidBody b
b.setPosition 0, 10, 0
# b.setGravity 0, -9.81, 0

tick = ->
  # fps++
  discreteDynamicsWorld.stepSimulation 1 / 120
  
  # output = ''
  
  # for i in [0...16]
  #   for j in [0...16]
  #     block = world["#{i}:#{j}"]
  #     
  #     position = block.getPosition()
  #     
  #     block.setPosition position.x, 0, position.y
  #     
  #     output += ' ' + position.y
  #   output += '\n'
  # 
  # console.log output
  
  position = b.getPosition()
  console.dir position
  
  b.applyCentralImpulse 0, 0.05, 0.05

setInterval tick, 1000 / 120