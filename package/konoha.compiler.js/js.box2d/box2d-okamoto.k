class B2Vec2 {
	float getX();
	float getY();
	void setZero();
	void set(float x, float y);
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
	int getType();
	void setType(int type);
	float getLocalPosition();
	void setLocalPosition(float lp);
	float getLocalRotation();
	void setLocalRotation(float lr);
	float getFriction();
	void setFriction(float f);
	float getDensity();
	void setDensity(float d);
	int getCategoryBits();
	void setCategoryBits(int cb);
	int getMaskBits();
	void setMaskBits(int mb);
	int getGroupIndex();
	void setGroupIndex(int gi);
	void computeMass(B2MassData massData);
}
@OverrideB2ShapeDef B2ShapeDef.new();

class B2BoxDef extends B2ShapeDef {
	B2Vec2 getExtents();
	void setExtents(B2Vec2 e);
}
@Override B2BoxDef B2BoxDef.new();
