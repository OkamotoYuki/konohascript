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
}
