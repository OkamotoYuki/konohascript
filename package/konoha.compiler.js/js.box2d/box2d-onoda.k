using js.box2d.*;

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

 	
//b2Body(bd:b2BodyDef, world:b2World)
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
