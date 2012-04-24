class B2Vec2 {
	float x;
	float y;
	void setZero();
	void set(float x, float y);
	B2Vec2 negative();
	B2Vec2 copy();
	void add(B2Vec2 v);
	void subtract(B2Vec2 v);
	void multiply(float a);
	mulM(B2Mat22 m);
	mulTM(B2Mat22 m);
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

class b2CircleDef { //extends b2Shapedef
	int radius;
}
b2CircleDef b2CicleDef.new();

class b2BodyDef {
	boolean allowSleep;
	int angularDamping;
	int angularVelocity;
	boolean isSleeping;
	int linearDamping;
	b2Vec2 linearVelocity;
	b2Vec2 position;
	boolean preventRotation;
	int rotation;
//	Array<> shapes;
	dynamic userData;

	void AddShape(b2Shape s);
};
b2BodyDef b2BodyDef.new();

class b2Mat22 {
	b2Vec2 col1;
	b2Vec2 col2;

	void Abs();
	void AddM(b2Mat22 m);
	b2Mat22 Copy();
	b2Mat22 Invert(b2Mat22 out);
	void Set(int angle);
	void SetIdentify();
	void SetM(b2Mat22 m);
	void SetVV(b2Vec2 c1, b2Vec2 c2);
	void SetZero();
	b2Vec2 Solve(b2Vec2 out, int bX, int bY);
};
b2Mat22 b2Mat22.new();

class b2PolyDef { //extends b2ShapeDef
	int vertexCount;
//	Array<> vertices;
};
b2PolyDef b2PolyDef.new();

class b2Body {
	int e_allowSleepFlag = 0x0010;
	int e_destroyFlag = ux0020;
	int e_frozenFlag = 0x0002;
	int e_islandFlag = 0x0004;
	int e_sleepFlag = 0x0008;
	int e_staticFlag = 0x0001;
	int m_angularDamping;
	int m_angularVetocity;
	b2Vec2 m_center;
	b2ContactNode m_contactList;
	int m_flags;
	b2Vec2 m_force;
	int m_I;
	int m_invI;
	int m_invMass;
	b2JointNode m_jointList;
	int m_linearDamping;
	b2Vec2 m_linearVelocity;
	int m_mass;
	b2Body m_next;
	b2Vec2 m_position;
	b2Vec2 m_position0;
	b2Body m_prev;
	b2Mat22 m_R;
	int m_rotation;
	int m_rotation0;
	int m_shapeCount;
	b2Shape m_shapeList;
	int m_sleepTime;
	int m_torque;
	dynamic m_userData;
	b2World m_world;

	void AllowSleeping(boolean flag);
	void ApplyForce(b2Vec2 force, b2Vec2 point);
	void ApplyImpulse(b2Vec2 impulse, b2Vec2 point);
	void ApplyTorque(int torque);
	void Destroy();
	void Freeze();
	int GetAngularVelocity();
	b2Vec2 GetCenterPosition();
	b2ContactNode GetContactList();
	int GetInertia();
	b2JointNode GetJointList();
	b2Vec2 GetLinearVelocity();
	b2Vec2 GetLocalPoint(b2Vec2 worldPoint);
	b2Vec2 GetLocalVector(b2Vec2 worldVector);
	int GetMass();
	b2Body GetNext();
	b2Vec2 GetOriginPosition();
	int GetRotation();
	b2Mat22 GetRotationMatrix();
	b2Shape GetShapeList();
	dynamic GetUserData();
	b2Vec2 GetWorldPoint(b2Vec2 localPoint);
	b2Vec2 GetWorldVector(b2Vec2 localVector);
	boolean IsConnected(b2Body other);
	boolean IsFrozen();
	boolean IsSleeping();
	boolean IsStatic();
	void QuickSyncShapes();
	void SetAngularVelocity(int w);
	void SetCenterPosition(b2Vec2 position, int rotation);
	void SetLinearVelocity(b2Vec2 v);
	void SetOriginPosition(b2Vec2 position, int rotation);
	void SynchronizeShapes();
	void WakeUp();
}
b2Body b2Body.new(b2BodyDef bd, b2World world);

class b2Contact {
	int e_destroyFlag = 0x0002;
	int e_islandFlag = 0x0001;
	int m_flags;
	int m_friction;
	int m_manifoldCount;
	b2Contact m_next;
	b2ContactNode m_node1;
	b2ContactNode m_node2;
	b2Contact m_prev;
	int m_restitution;
	b2Shape m_shape1;
	b2Shape m_shape2;
	boolean s_initialized = false;
//	Array<> s_registers;

	void AddType(dynamic createFcn, dynamic destroyFcn, int type1, int type2);
	b2Contact Create(b2Shape shape1, b2Shape shape2, dynamic allocator);
	void Destroy(cb2Contact contact, dynamic allocator);
	void Evaluate();
	int GetManifoldCount();
//	Array<> GetManifolds();
	b2Contact GetNext();
	b2Shape GetShape1();
	b2Shape GetShape2();
	void InitializeRegisters();
}
b2Contact b2Contact.new(b2Shape s1 = null, b2Shape s2 = null);

class b2CollisionFilter {
	b2CollisionFilter b2_defaultFilter;
	boolean ShouldCollide(b2Shape shape1, b2Shape shape2);
}

class b2WorldListener {
	int b2_destroyBody = 1;
	int b2_freezeBody = 0;
	int NotifyBoundaryViolated(b2Body body);
	void NotifyJointDestroyed(b2Joint joint);
}

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
	boolean isValid();
	B2Vec2 minVertex;
	B2Vec2 maxVertex;
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
