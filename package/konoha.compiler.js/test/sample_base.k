using js.box2d.*;

B2Body createGround(world) {
	B2BoxDef groundSd = new ();
	groundSd.extents.set(1000, 50);
	groundSd.restitution = 0.2;
	B2BodyDef groundBd = new ();
	groundBd.AddShape(groundSd);
	groundBd.position.set(-500, 340);
	return world.createBody(groundBd)
}

B2Body createBall(world, x, y) {
	B2CircleDef ballSd = new ();
	ballSd.density = 1.0;
	ballSd.radius = 20;
	ballSd.restitution = 1.0;
	ballSd.friction = 0;
	B2BodyDef ballBd = new ();
	ballBd.addShape(ballSd);
	ballBd.position.set(x,y);
	return world.createBody(ballBd);
}

B2Body createBox(B2World world, float x, float y, float width, float height, float density) {
	B2BoxDef boxSd = new ();
	boxSd.density = density;
	boxSd.extents.set(width, height);
	B2BodyDef boxBd = new ();
	boxBd.addShape(boxSd);
	boxBd.position.set(x,y);
	return world.createBody(boxBd)
}

B2World createWorld() {
	B2AABB worldAABB = new ();
	worldAABB.minVertex.set(-1000, -1000);
	worldAABB.maxVertex.set(1000, 1000);
	B2Vec gravity = new (0, 300);
	boolean doSleep = true;
	B2World world = new B2World(worldAABB, gravity, doSleep);
	createGround(world);
	createBox(world, 0, 125, 10, 250);
	createBox(world, 500, 125, 10, 250);
	return world;
}
