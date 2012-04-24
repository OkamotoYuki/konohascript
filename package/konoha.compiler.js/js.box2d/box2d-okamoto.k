class B2Vec2 {
	float x;
	float y;

	void SetZero();
	void Set(float x, float y);
	B2Vec2 negative();
	B2Vec2 copy();
	void add(B2Vec2 v);
	void subtract(B2Vec2 v);
	void multiply(float a);
	void mulM(B2Mat22 m);
	void mulTM(B2Mat22 m);
	void crossVF(float s);
	void crossFV(float s);
	void minV(B2Vec2 b);
	void maxV(B2Vec2 b);
	void abs();
	void normalize();
	boolean isValid();
	B2Vec2 make(float x, float y);
}
B2Vec2 B2Vec2.new(float x, float y);

class B2ShapeDef {
	int type;
	float position;
	float localPosition;
	float localRotation;
	float localPosition;
	float friction;
	float density;
	int categoryBits;
	int maskBits;
	int groupIndex;

	void computeMass(B2MassData massData);
}
@Override B2ShapeDef B2ShapeDef.new();

class B2BoxDef extends B2ShapeDef {
	B2Vec2 extents;
}
@Override B2BoxDef B2BoxDef.new();

class B2JointDef {
	int type;
	B2Body body1;
	B2Body body2;
	boolean collideConnected;
}
@Overrride B2JointDef B2JointDef.new();

class B2RevoluteJointDef {
	B2Vec2 anchorPoint;
	float lowerAngle;
	float upperAngle;
	float motorSpeed;
	float motorTorqe;
	boolean enableLimit;
	boolean enableMotor;
}
@Overrride B2RevoluteJointDef B2RevoluteJointDef.new();

class B2PrismaticJointDef {
	B2Vec2 anchorPoint;
	B2Vec2 axis;
	float lowerAngle;
	float upperAngle;
	float motorSpeed;
	float motorTorqe;
	boolean enableLimit;
	boolean enableMotor;
}
@Overrride B2PrismaticJointDef B2PrismaticJointDef.new();

class B2AABB {
	B2Vec2 minVertex;
	B2Vec2 maxVertex;

	boolean isValid();
}
B2AABB B2AABB.new();

class B2World {
	int m_bodyCount;
	B2Body m_bodyDestroyList;
	B2Body m_bodyList;
	B2BroadPhase m_broadPhase;
	int contactCount;
	B2Contact m_contactList;
	B2ContactManager m_contactManager;
	B2CollisionFilter;
	B2Vec2 m_gragity;
	B2Body m_groundBody;
	int m_jointCount;
	B2Joint m_jointList;
	B2WorldListener m_listener;
//	m_stackAllocator;
	int s_enablePositionCorrection;
	int s_enableWarmStarting;

	void cleanBodyList();
	B2Body createBody(B2BodyDef bd);
	B2Joint createJoint(B2JointDef jd);
	void destroyBody();
	void destroyJoint();
	B2Body getBodyList();
	B2Contact getContactList();
	B2Body getGroundBody();
	B2Joint getJointList();
//	int Query();
	void setFilter(B2CollisionFilter filter);
	void setListener(B2WorldListener listener);
//	void step();
}
B2World.new(B2AABB, aabb, B2Vec2, gravity, boolean doSleep);

class B2Joint {
	B2Body m_body1;
	B2Body m_body2;
	boolean m_collideConnected;
	boolean m_islandFlag;
	B2Joint m_next;
	B2JointNode m_node1;
	B2JointNode m_node2;
	B2Joint m_prev;
	int m_type;
//	m_userData;

	B2Joint create(B2JointDef jd);
	void destroy(B2Joint joint);
	B2Vec2 getAnchor1();
	B2Vec2 getAnchor2();
	B2Body getBody1();
	B2Body getBody2();
	B2Joint getNext();
//	B2Vec2 getReactionForce();
//	int getReactionTorque();
	int GetType();
//	getUserData();
	void preparePositionSolver();
	void prepareVelocitySolver();
	boolean solvePositionConstraints();
	void solveVelocityConstraints(B2TimeStep step);

	int e_atLowerLimit;
	int e_atUpperLimit;
	int e_distanceJoint;
	int e_equalLimits;
	int e_gearJoint;
	int e_inactiveLimit;
	int e_mouseJoint;
	int e_prismaticJoint;
	int e_pulleyJoint;
	int e_revoluteJoint;
	int e_unknownJoint;
}
B2Joint.new(B2JointDef jd);
