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

class B2JointDef {
	int type;
//	body1;
//	body2;
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
