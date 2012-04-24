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

class B2CircleDef { //extends B2Shapedef
	int radius;
}
B2CircleDef B2CicleDef.new();

class B2BodyDef {
	boolean allowSleep;
	int angularDamping;
	int angularVelocity;
	boolean isSleeping;
	int linearDamping;
	B2Vec2 linearVelocity;
	B2Vec2 position;
	boolean preventRotation;
	int rotation;
//	Array<> shapes;
	dynamic userData;

	void AddShape(B2Shape s);
};
B2BodyDef B2BodyDef.new();

class B2Mat22 {
	B2Vec2 col1;
	B2Vec2 col2;

	void Abs();
	void AddM(B2Mat22 m);
	B2Mat22 Copy();
	B2Mat22 Invert(B2Mat22 out);
	void Set(int angle);
	void SetIdentify();
	void SetM(B2Mat22 m);
	void SetVV(B2Vec2 c1, B2Vec2 c2);
	void SetZero();
	B2Vec2 Solve(B2Vec2 out, int bX, int bY);
};
B2Mat22 B2Mat22.new();

class B2PolyDef { //extends b2ShapeDef
	int vertexCount;
//	Array<> vertices;
};
B2PolyDef B2PolyDef.new();

class B2Body {
	int e_allowSleepFlag = 0x0010;
	int e_destroyFlag = ux0020;
	int e_frozenFlag = 0x0002;
	int e_islandFlag = 0x0004;
	int e_sleepFlag = 0x0008;
	int e_staticFlag = 0x0001;
	int m_angularDamping;
	int m_angularVetocity;
	B2Vec2 m_center;
	B2ContactNode m_contactList;
	int m_flags;
	B2Vec2 m_force;
	int m_I;
	int m_invI;
	int m_invMass;
	B2JointNode m_jointList;
	int m_linearDamping;
	B2Vec2 m_linearVelocity;
	int m_mass;
	B2Body m_next;
	B2Vec2 m_position;
	B2Vec2 m_position0;
	B2Body m_prev;
	B2Mat22 m_R;
	int m_rotation;
	int m_rotation0;
	int m_shapeCount;
	B2Shape m_shapeList;
	int m_sleepTime;
	int m_torque;
	dynamic m_userData;
	B2World m_world;

	void AllowSleeping(boolean flag);
	void ApplyForce(B2Vec2 force, B2Vec2 point);
	void ApplyImpulse(B2Vec2 impulse, B2Vec2 point);
	void ApplyTorque(int torque);
	void Destroy();
	void Freeze();
	int GetAngularVelocity();
	B2Vec2 GetCenterPosition();
	B2ContactNode GetContactList();
	int GetInertia();
	B2JointNode GetJointList();
	B2Vec2 GetLinearVelocity();
	B2Vec2 GetLocalPoint(B2Vec2 worldPoint);
	B2Vec2 GetLocalVector(B2Vec2 worldVector);
	int GetMass();
	B2Body GetNext();
	B2Vec2 GetOriginPosition();
	int GetRotation();
	B2Mat22 GetRotationMatrix();
	B2Shape GetShapeList();
	dynamic GetUserData();
	B2Vec2 GetWorldPoint(B2Vec2 localPoint);
	B2Vec2 GetWorldVector(B2Vec2 localVector);
	boolean IsConnected(B2Body other);
	boolean IsFrozen();
	boolean IsSleeping();
	boolean IsStatic();
	void QuickSyncShapes();
	void SetAngularVelocity(int w);
	void SetCenterPosition(B2Vec2 position, int rotation);
	void SetLinearVelocity(B2Vec2 v);
	void SetOriginPosition(B2Vec2 position, int rotation);
	void SynchronizeShapes();
	void WakeUp();
}
B2Body B2Body.new(B2BodyDef bd, B2World world);

class B2Contact {
	int e_destroyFlag = 0x0002;
	int e_islandFlag = 0x0001;
	int m_flags;
	int m_friction;
	int m_manifoldCount;
	B2Contact m_next;
	B2ContactNode m_node1;
	B2ContactNode m_node2;
	B2Contact m_prev;
	int m_restitution;
	B2Shape m_shape1;
	B2Shape m_shape2;
	boolean s_initialized = false;
//	Array<> s_registers;

	void AddType(dynamic createFcn, dynamic destroyFcn, int type1, int type2);
	B2Contact Create(B2Shape shape1, B2Shape shape2, dynamic allocator);
	void Destroy(cB2Contact contact, dynamic allocator);
	void Evaluate();
	int GetManifoldCount();
//	Array<> GetManifolds();
	B2Contact GetNext();
	B2Shape GetShape1();
	B2Shape GetShape2();
	void InitializeRegisters();
}
B2Contact B2Contact.new(B2Shape s1 = null, B2Shape s2 = null);

class B2CollisionFilter {
	B2CollisionFilter B2_defaultFilter;
	boolean ShouldCollide(B2Shape shape1, B2Shape shape2);
}

class B2WorldListener {
	int b2_destroyBody = 1;
	int b2_freezeBody = 0;
	int NotifyBoundaryViolated(B2Body body);
	void NotifyJointDestroyed(B2Joint joint);
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
B2World B2World.new(B2AABB aabb, B2Vec2 gravity, boolean doSleep);

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
