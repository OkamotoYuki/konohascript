class B2Vec2;
class B2Mat22;
class B2Shape;
class B2ShapeDef;
class B2BoxDef;
class B2PolyDef;
class B2Body;
class B2BodyDef;
class B2Contact;
class B2ContactNode;
class B2Joint;
class B2JointNode;
class B2JointDef;
class B2RevoluteJointDef;
class B2PrismaticJointDef;
class B2AABB;
class B2World;
class B2WorldListener;

class B2Vec2 {
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
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

class B2Mat22 {
	B2Vec2 getCol1();
	void setCol1(B2Vec2 col1);
	B2Vec2 getCol2();
	void setCol2(B2Vec2 col2)

	void abs();
	void addM(B2Mat22 m);
	B2Mat22 copy();
	B2Mat22 invert(B2Mat22 out);
	void set(int angle);
	void setIdentify();
	void setM(B2Mat22 m);
	void setVV(B2Vec2 c1, B2Vec2 c2);
	void setZero();
	B2Vec2 solve(B2Vec2 out, int bX, int bY);
};
B2Mat22 B2Mat22.new();

class B2Shape {
	B2Body getM_body();
	void setM_body(B2Body body);
	int getM_categoryBits();
	void setM_categoryBits(int categoryBits);
	float getM_friction();
	void setM_friction(float friction);
	int getM_groupIndex();
	void setM_groupIndex(int groupIndex);
	int getM_maskBits();
	void setM_maskBits(int maskBits);
	float getM_maxRadius();
	void setM_maxRadius(float maxRadius);
	B2Shape getM_next()
	void setM_next(B2Shape next);
	B2Vec2 getM_position();
	void setM_position(B2Vec2 position);
	int getM_proxyId();
	void setM_proxyId(int proxyId);
	B2Matt22 getM_R();
	void getM_R(B2Matt22 R);
	float getM_restitution();
	void setM_restitution(float restitution);
	int getM_type();
	void setM_type(int i);
	dynamic getM_usetData();
	void setM_userData(dynamic userData);

//	B2Shape create(B2ShapeDef def, B2Body body, B2Vec2 center);
//	void destroy(B2Shape shape);
//	void destroyProxy();
//	B2Body getBody();
//	float getMaxRadiusl();
//	B2Shape getNext();
//	B2Vec2 getPosition();
//	B2Mat22 getRotationMatrix();
//	int getType();
////	getUserData();
////	void polyCentroid();
////	void polyMass(B2MassData massData, Array vs, int count, float rho);
//	void quickSync(B2Vec position, B2Mat22 r);
////	void resetProxy(B2BroadPhase broadPhase);
//	void support(float dX, float dY, B2Vec2 out);
//	void synchronize(B2Vec2 position1, B2Mat22 r1, B2Vec2 position2, B2Mat22 r2);
//	boolean testPoint(B2Vec2 p);
}
//B2Shape B2Shape.new(B2ShapeDef def, B2Body body);

class B2ShapeDef {
	int getType();
	void setType(int type);
	float getPosition();
	void setPosition(float position);
	float getLocalPosition();
	void setLocalPosition(float localPosition);
	float getLocalRotation();
	void setLocalRotation();
	float getLocalPosition();
	void setLocalPosition(float localPosition);
	float getFriction();
	void setFriction(float friction);
	float getDensity();
	void setDensity(float density);
	int getCategoryBits();
	void setCategoryBits(int catetoryBits);
	int getMaskBits();
	void setMaskBits(int maskBits);
	int getGroupIndex();
	void setGroupIndex(int grouIndex);
	void computeMass(B2MassData massData);
}
@Override B2ShapeDef B2ShapeDef.new();

class B2BoxDef extends B2ShapeDef {
	B2Vec2 getExtends();
	void setExtends(B2Vec2 extends);
}
@Override B2BoxDef B2BoxDef.new();

class B2CircleDef { //extends B2Shapedef
	int getRadius();
	void setRadius(int radius);
}
B2CircleDef B2CircleDef.new();

class B2PolyDef { //extends b2ShapeDef
	int getVertexCount();
	void setVertexCount(int vertexCount);
//	Array<> vertices;
};
B2PolyDef B2PolyDef.new();

class B2Body {
	int getE_allowSleepFlag();
	int getE_destroyFlag();
	int getE_frozenFlag();
	int getE_islandFlag();
	int getE_sleepFlag();
	int getE_staticFlag();
	int getM_angularDamping();
	void setM_angularDamping(int angularDamping)
	int getM_angularVetocity();
	void setM_angularVetocity(int angularVetocity);
	B2Vec2 getM_center();
	void setM_center(B2Vec2 center);
	B2ContactNode getM_contactList();
	void setM_contactList(B2ContactNode contactList);
	int getM_flags();
	void setM_flags(int flags);
	B2Vec2 getM_force();
	void setM_force(B2Vec2 force);
	int getM_I();
	void setM_I(int i);
	int getM_InvI();
	void setM_InvI(int i);
	int getM_invMass()
	void setM_invMass(int invMass);
	B2JointNode getM_jointList();
	void setM_jointList(B2JointNode jointList);
	int getM_linearDamping();
	void setM_linearDamping(int linearDamping);
	B2Vec2 getM_linearVelocity();
	void setM_linearVelocity(B2Vec2 linearVelocity);
	int getM_mass();
	void setM_mass(int mass);
	B2Body getM_next();
	void setM_next(B2Body next);
	B2Vec2 getM_position();
	void setM_position(B2Vec2 position);
	B2Vec2 getM_position0();
	void setM_position0(B2Vec2 position0);
	B2Vec2 getM_prev();
	void setM_prev(B2Vec2 prev);
	B2Matt22 getM_R();
	void setM_R(B2Mat22 R);
	int getM_rotation();
	void getM_rotation(int rotation);
	int getM_rotation();
	void setM_rotation(int rotation);
	int getM_shapeCount();
	void setM_shapeCount(int shapeCount);
	B2Shape getM_shapeList();
	void setM_shapeList(B2Shape shapeList);
	int getM_sleepTime();
	void setM_sleepTime(int sleepTime);
	int getM_torque();
	void setM_torque(int torque);
	dynamic getM_userData();
	void setM_userData();
	B2World getM_world();
	void setM_world(B2World world);

	void allowSleeping(boolean flag);
	void applyForce(B2Vec2 force, B2Vec2 point);
	void applyImpulse(B2Vec2 impulse, B2Vec2 point);
	void applyTorque(int torque);
	void destroy();
	void freeze();
	int getAngularVelocity();
	B2Vec2 getCenterPosition();
	B2ContactNode getContactList();
	int getInertia();
	B2JointNode getJointList();
	B2Vec2 getLinearVelocity();
	B2Vec2 getLocalPoint(B2Vec2 worldPoint);
	B2Vec2 getLocalVector(B2Vec2 worldVector);
	int getMass();
	B2Body getNext();
	B2Vec2 getOriginPosition();
	int getRotation();
	B2Mat22 getRotationMatrix();
	B2Shape getShapeList();
	dynamic getUserData();
	B2Vec2 getWorldPoint(B2Vec2 localPoint);
	B2Vec2 getWorldVector(B2Vec2 localVector);
	boolean isConnected(B2Body other);
	boolean isFrozen();
	boolean isSleeping();
	boolean isStatic();
	void quickSyncShapes();
	void setAngularVelocity(int w);
	void setCenterPosition(B2Vec2 position, int rotation);
	void setLinearVelocity(B2Vec2 v);
	void setOriginPosition(B2Vec2 position, int rotation);
	void synchronizeShapes();
	void wakeUp();
}
B2Body B2Body.new(B2BodyDef bd, B2World world);

class B2BodyDef {
	boolean getAllowSleep();
	void setAllowSleep(boolean b);
	int getAngularDamping();
	void setAngularDamping(int i);
	int getAngularVelocity();
	void getAngularVelocity(int i);
	boolean getIsSleeping();
	void setIsSleeping(boolean b);
	int getLinearDamping();
	void getLinearDamping(int i);
	B2Vec2 getLinearVelocity();
	void setLinearVelocity(B2Vec2 b);
	B2Vec2 getPosition();
	void getPosition(B2Vec2 b);
	boolean getPreventRotation();
	void getPreventRotation(boolean b);
	int getRotation();
	void setRotation(int i);
//	Array<> shapes;
	dynamic getUserData();
	void setUserData(dynamic d);

	void addShape(B2Shape s);
};
B2BodyDef B2BodyDef.new();

class B2Contact {
//	int e_destroyFlag = 0x0002;
//	int e_islandFlag = 0x0001;
	int getM_flags();
	void setM_flags(int i);
	int getM_friction();
	void setM_friction(int i);
	int getM_manifoldCount();
	void getM_manifoldCount(int i);
	B2Contact getM_next();
	void setM_next(B2Contact c);
	B2ContactNode getM_node1();
	void setM_node1(B2ContactNode c);
	B2ContactNode getM_node2();
	void setM_node2(B2ContactNode c);
	B2Contact getM_prev();
	void setM_prev(B2Contact c);
	int getM_restitution();
	void setM_restitution(int i);
	B2Shape getM_shape1();
	void setM_shape1(B2Shape s);
	B2Shape getM_shape2();
	void setM_shape2(B2Shape b);
//	boolean s_initialized = false;
//	Array<> s_registers;

	void addType(dynamic createFcn, dynamic destroyFcn, int type1, int type2);
	B2Contact create(B2Shape shape1, B2Shape shape2, dynamic allocator);
	void destroy(cB2Contact contact, dynamic allocator);
	void evaluate();
	int getManifoldCount();
//	Array<> GetManifolds();
	B2Contact getNext();
	B2Shape getShape1();
	B2Shape getShape2();
	void initializeRegisters();
}
B2Contact B2Contact.new(B2Shape s1 = null, B2Shape s2 = null);

class B2ContactNode {
	B2Contact getContact();
	void setContact(B2Contact c);
	B2ContactNode getNext();
	void setNext(B2ContactNode c);
	B2Body getOther();
	void setOther(B2Body b);
	B2ContactNode getPrev();
	void getPrev(B2ContactNode c);
}
B2ContactNode B2ContactNode.new();

class B2CollisionFilter {
	B2CollisionFilter getB2_defaultFilter();
	void setB2_defaultFilter();
	boolean shouldCollide(B2Shape shape1, B2Shape shape2);
}

class B2Joint {
	B2Body getM_body1();
	void setM_body1(B2Body b);
	B2Body getM_body2();
	void setM_body2(B2Body b);
	boolean getM_collideConnected();
	void setM_collideConnected(boolean b);
	boolean getM_islandFlag();
	void setM_islandFlag(boolean b);
	B2Joint getM_next();
	void getM_next(B2Joint j);
	B2JointNode getM_node1();
	void setM_node1(B2JointNode j);
	B2JointNode getM_node2();
	void setM_node2(B2JointNode j);
	B2Joint getM_prev();
	void setM_prev(B2Joint j);
	int getM_type();
	void setM_type(int i);
//	M_userData;

	B2Joint create(B2JointDef jd);
	void destroy(B2Joint joint);
	B2Vec2 getAnchor1();
	B2Vec2 getAnchor2();
	B2Body getBody1();
	B2Body getBody2();
	B2Joint getNext();
//	B2Vec2 getReactionForce();
//	int getReactionTorque();
	int getType();
//	getUserData();
	void preparePositionSolver();
	void prepareVelocitySolver();
	boolean solvePositionConstraints();
	void solveVelocityConstraints(B2TimeStep step);

	// int e_atLowerLimit;
	// int e_atUpperLimit;
	// int e_distanceJoint;
	// int e_equalLimits;
	// int e_gearJoint;
	// int e_inactiveLimit;
	// int e_mouseJoint;
	// int e_prismaticJoint;
	// int e_pulleyJoint;
	// int e_revoluteJoint;
	// int e_unknownJoint;
}
B2Joint B2Joint.new(B2JointDef jd);

class B2JointNode {
	B2Joint getJoint();
	void setJoint(B2Joint j);
	B2JointNode getNext();
	void setNext(B2JointNode j);
	B2Body getOther();
	void setOther(B2Body b);
	B2JointNode getPrev();
	void setPrev(B2JointNode j);
}
B2JointNode B2JointNode.new();

class B2JointDef {
	int getType();
	void setType(int i);
	B2Body getBody1();
	void setBody1(B2Body b);
	B2Body getBody2();
	void setBody2(B2Body b);
	boolean getCollideConnected();
	void setCollideConnected(boolean b);
}
@Override B2JointDef B2JointDef.new();

class B2RevoluteJointDef {
	B2Vec2 getAnchorPoint();
	void setAnchorPoint(B2Vec2 v);
	float getLowerAngle();
	void setLowerAngle(float f);
	float getUpperAngle();
	void setUpperAngle(float f);
	float getMotorSpeed();
	void setMotorSpeed(float f);
	float getMotorTorqe();
	void setMotorTorqe(float f);
	boolean getEnableLimit();
	void setEnableLimit(float f);
	boolean getEnableMotor();
	void setEnableMotor(boolean b);
}
@Overrride B2RevoluteJointDef B2RevoluteJointDef.new();

class B2PrismaticJointDef {
	B2Vec2 getAnchorPoint();
	void setAnchorPoint(B2Vec2 v);
	B2Vec2 getAxis();
	void setAxis(B2Vec2 v);
	float getLowerAngle();
	void setLowerAngle(float f);
	float getUpperAngle();
	void setUpperAngle(float f);
	float getMotorSpeed();
	void setMotorSpeed(float f);
	float getMotorTorqe();
	void setMotorTorqe(float f);
	boolean getEnableLimit();
	void getEnableLimit(boolean b);
	boolean getEnableMotor();
	void setEnableMotor(boolean b);
}
@Overrride B2PrismaticJointDef B2PrismaticJointDef.new();

class B2AABB {
	boolean isValid();
	B2Vec2 getMinVertex();
	B2Vec2 setMinVertex();
	B2Vec2 getMaxVertex();
	B2Vec2 setMaxVertex();
}
B2AABB B2AABB.new();

class B2World {
	int getM_bodyCount();
	void setM_bodyCount(int i);
	B2Body getM_bodyDestroyList();
	void setM_bodyDestroyList(B2Body b);
	B2Body getM_bodyList();
	void setM_bodyList(B2Body b);
//	B2BroadPhase M_broadPhase;
	int getContactCount();
	void setContactCount(int i);
	B2Contact getM_contactList();
	void setM_contactList(B2Contact c);
//	B2ContactManager M_contactManager;
	B2CollisionFilter getM_filter();
	void setM_filter(B2CollisionFilter c);
	B2Vec2 getM_gragity();
	void setM_gragity(B2Vec2 v);
	B2Body getM_groundBody();
	void setM_groundBody(B2Body b);
	int getM_jointCount();
	void setM_jointCount(int i);
	B2Joint getM_jointList();
	void setM_jointList(B2Joint j);
	B2WorldListener getM_listener();
	void setM_listener(B2WorldListener w);
//	M_stackAllocator;
//	int s_enablePositionCorrection;
//	int s_enableWarmStarting;

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

class B2WorldListener {
	//	int b2_destroyBody = 1;
	//	int b2_freezeBody = 0;
	int notifyBoundaryViolated(B2Body body);
	void notifyJointDestroyed(B2Joint joint);
}
