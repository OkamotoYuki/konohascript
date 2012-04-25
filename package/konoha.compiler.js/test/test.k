using js.box2d.*;

void main()
{
	B2AABB worldAABB = new ();
	worldAABB.minVertex.set(-1000, -1000);
	worldAABB.maxVertex.set(1000, 1000);
	B2Vec2 gravity = new B2Vec2(0, 300);
	boolean doSleep = true;
	var world = new B2World(worldAABB, gravity, doSleep);
}
