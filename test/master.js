var Bullet = require('../index');

var bullet = new Bullet.Bullet;
var collisionConfig = new Bullet.DefaultCollisionConfiguration;
var collisionDispatcher = new Bullet.CollisionDispatcher(collisionConfig);
var broadphase = new Bullet.DbvtBroadphase;
var solver = new Bullet.SequentialImpulseConstraintSolver;

var world = new Bullet.DiscreteDynamicsWorld(
	collisionDispatcher,
	broadphase,
	solver,
	collisionConfig
);

world.gravity = {x:0, y:-9.81, z:0};

var blocks = {};

var rows=20,cols=20;
for(var i = 0; i < rows; i++) {
	for(var j = 0; j < cols; j++) {
		var shape = new Bullet.BoxShape();
		var block = new Bullet.RigidBody(1,shape);
		world.addRigidBody(block);
		block.position = {x:i*1, y:0, z:j*1};
		console.log(block.position);
		blocks[i+':'+j] = block;
	}
	console.log("added "+((i+1)*cols)+" of "+(rows*cols)+" blocks");
}
console.log("blocks added");

var ticks = 1000;
for(var i = 0; i < ticks; i++) {
	world.step(1/120);
	if(i%100 == 0) console.log("tick "+i+" of "+ticks);
	console.log(blocks['10:10'].position);
}

console.log('done');
