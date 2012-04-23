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
