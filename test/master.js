var Bullet = require('../index');

var bullet = new Bullet.Bullet;
console.log('bullet', bullet);

var defaultCollisionConfiguration = new Bullet.DefaultCollisionConfiguration;
console.log('defaultCollisionConfiguration', defaultCollisionConfiguration);

var collisionDispatcher = new Bullet.CollisionDispatcher(defaultCollisionConfiguration);
console.log('collisionDispatcher', collisionDispatcher);

var dbvtBroadphase = new Bullet.DbvtBroadphase;
console.log('dbvtBroadphase', dbvtBroadphase);

var sequentialImpulseConstraintSolver = new Bullet.SequentialImpulseConstraintSolver;
console.log('sequentialImpulseConstraintSolver', sequentialImpulseConstraintSolver);

var discreteDynamicsWorld = new Bullet.DiscreteDynamicsWorld(
	collisionDispatcher,
	dbvtBroadphase,
	sequentialImpulseConstraintSolver,
	defaultCollisionConfiguration
);
console.log('discreteDynamicsWorld', discreteDynamicsWorld);

discreteDynamicsWorld.setGravity(0, -9.81, 0);

/*
# # boxShape = new Bullet.BoxShape
# # console.log 'boxShape', boxShape

# # transform = new Bullet.Transform
# # console.log 'transform', transform

// API
	 RigidBody(mass)
		 applyImpulse(point, impulse)
		 getPosition()
		 setPosition(x, y, z)
		 setLinearVelocity(x, y, z)
		 setGravity(x, y, z)

	 DiscreteDynamicsWorld(dispatcher, broadphase, solver, configuration)
		 addRigidBody(rigid_body)
		 setGravity(x, y, z)
*/

var world = {};

var rows=20,cols=20;
for(var i = 0; i < rows; i++) {
	for(var j = 0; j < cols; j++) {
		var shape = new Bullet.BoxShape();
		console.log("1",shape.prototype);
		var block = new Bullet.RigidBody(1,shape);
		console.log("2",block);
		discreteDynamicsWorld.addRigidBody(block);
		console.log("3");
		block.setPosition(i * 5, 0, j * 5);
		console.log(block.getPosition());
		world[i+':'+j] = block;
	}
	console.log("4");
	console.log("added "+((i+1)*cols)+" of "+(rows*cols)+" blocks");
}
console.log("blocks added");

function tick() {
	discreteDynamicsWorld.stepSimulation(1/120);
	//b.applyImpulse 0, -0.01, 0, 0, 0.5, 0
}

var ticks = 1000;
for(var i = 0; i < ticks; i++) {
	tick();
	if(i%120 == 0) {
		b.setPosition(0, 0, 0);
	}
	if(i%100 == 0) {
		console.log("tick "+i+" of "+ticks);
	}
}

console.log('done');
