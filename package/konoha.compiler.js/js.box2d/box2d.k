class B2Vec2 {
	float x;
	float y;
	void SetZero();
	void Set(float x, float y);
	B2Vec2 negative();
	B2Vec2 copy();
	void add(B2Vec2 v);
	void subtract(B2Vec2 v);
//	multiply();
//	mulM();
//	mulTM();
	void crossVF(float s);
	void crossFV(float s);
	void minV(B2Vec2 b);
	void maxV(B2Vec2 b);
	void abs();
	void normalize();
//	isValid();
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

class B2JointDef {
	int type;
//	body1;
//	body2;
	boolean collideConnected;
}
@Overrride B2JointDef B2JointDef.new();

class B2RevoluteJointDef {
//	anchorPoint;
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
