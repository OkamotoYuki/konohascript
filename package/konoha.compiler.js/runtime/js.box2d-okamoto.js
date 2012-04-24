var verifyArgs = function(args) {
	for(var i = 0; i < args.length; i++) {
		if(args[i].rawptr) {
			args[i] = args[i].rawptr;
		}
	}
	return args;
}

js.box2d = function() {}

/* b2Vec2 */
js.box2d.B2Vec2 = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2Vec2.prototype = new konoha.Object();
js.box2d.B2Vec2.prototype.konohaclass = "js.box2d.B2Vec2";
js.box2d.B2Vec2.prototype._new = function() {
	var args = verifyArgs(arguments);
	this.rawptr = new b2Vec2(args[0], args[1]);
	return this;
}
js.box2d.B2Vec2.prototype.getX() function() {
	return this.rawptr.x;
}
js.box2d.B2Vec2.prototype.getY() function() {
	return this.rawptr.y;
}
js.box2d.B2Vec2.prototype.SetZero = function() {
	this.rawptr.SetZero();
}
js.box2d.B2Vec2.prototype.Set = function() {
	var args = verifyArgs(arguments);
	this.rawptr.Set(args[0], args[1]);
}
js.box2d.B2Vec2.prototype.negative = function() {
	return new js.box2d.B2Vec2(this.rawptr.Negative());
}
js.box2d.B2Vec2.prototype.copy = function() {
	return new js.box2d.B2Vec2(this.rawptr.Copy());
}
js.box2d.B2Vec2.prototype.add = function() {
	var args = verifyArgs(arguments);
	this.rawptr.Add(args[0]);
}
js.box2d.B2Vec2.prototype.subtract = function() {
	var args = verifyArgs(arguments);
	this.rawptr.Subtract(args[0]);
}
js.box2d.B2Vec2.prototype.multiply = function() {
	var args = verifyArgs(arguments);
	this.rawptr.Multiply(args[0]);
}
js.box2d.B2Vec2.prototype.mulM = function() {
	var args = verifyArgs(arguments);
	this.rawptr.MulM(args[0]);
}
js.box2d.B2Vec2.prototype.mulTM = function() {
	var args = verifyArgs(arguments);
	this.rawptr.MulTM(args[0]);
}
js.box2d.B2Vec2.prototype.crossVF = function() {
	var args = verifyArgs(arguments);
	this.rawptr.CrossVF(args[0]);
}
js.box2d.B2Vec2.prototype.crossFV = function() {
	var args = verifyArgs(arguments);
	this.rawptr.CrossFV(args[0]);
}
js.box2d.B2Vec2.prototype.minV = function() {
	var args = verifyArgs(arguments);
	this.rawptr.MinV(args[0]);
}
js.box2d.B2Vec2.prototype.maxV = function() {
	var args = verifyArgs(arguments);
	this.rawptr.MaxV(args[0]);
}
js.box2d.B2Vec2.prototype.abs = function() {
	this.rawptr.Abs();
}
js.box2d.B2Vec2.prototype.length = function() {
	return this.rawptr.Length();
}
js.box2d.B2Vec2.prototype.normalize = function() {
	return this.rawptr.Normalize();
}
js.box2d.B2Vec2.prototype.isValid = function() {
	return this.rawptr.IsValid();
}
js.box2d.B2Vec2.prototype.make = function() {
	var args = verifyArgs(arguments);
	return js.box2d.B2Vec2(this.rawptr.Make(args[0], args[1]));
}

/* b2ShapeDef */
js.box2d.B2ShapeDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2ShapeDef.prototype = new konoha.Object();
js.box2d.B2ShapeDef.prototype.konohaclass = "js.box2d.ShapeDef";
js.box2d.B2ShapeDef.prototype._new = function() {
	this.rawptr = new b2ShapeDef();
	return new this;
}
js.box2d.B2ShapeDef.prototype.getType = function() {
	return this.rawptr.type;
}
js.box2d.B2ShapeDef.prototype.setType = function() {
	var args = verifyArgs(arguments);
	this.rawptr.type = args[0];
}
//js.box2d.B2ShapeDef.prototype.getUserData = function() {
//	return this.userData;
//}
//js.box2d.B2ShapeDef.prototype.setUserData = function() {
//	var args = verifyArgs(arguments);
//	this.rawptr.userData = args[0];
//}
js.box2d.B2ShapeDef.prototype.getLocalPosition = function() {
	return this.rawptr.localPosition;
}
js.box2d.B2ShapeDef.prototype.setLocalPosition = function() {
	var args = verifyArgs(arguments);
	this.rawptr.localPosition = args[0];
}
js.box2d.B2ShapeDef.prototype.getLocalRotation = function() {
	return this.rawptr.localRotation;
}
js.box2d.B2ShapeDef.prototype.setLocalRotation = function() {
	var args = verifyArgs(arguments);
	this.rawptr.localRotation = args[0];
}
js.box2d.B2ShapeDef.prototype.getFriction = function() {
	return this.rawptr.friction;
}
js.box2d.B2ShapeDef.prototype.setFriction = function() {
	var args = verifyArgs(arguments);
	this.rawptr.friction = args[0];
}
js.box2d.B2ShapeDef.prototype.getDensity = function() {
	return this.rawptr.density;
}
js.box2d.B2ShapeDef.prototype.setDensity = function() {
	var args = verifyArgs(arguments);
	this.rawptr.density = args[0];
}
js.box2d.B2ShapeDef.prototype.getCategoryBits = function() {
	return this.rawptr.categoryBits;
}
js.box2d.B2ShapeDef.prototype.setCategoryBits = function() {
	var args = verifyArgs(arguments);
	this.rawptr.categoryBits = args[0];
}
js.box2d.B2ShapeDef.prototype.getMaskBits = function() {
	return this.rawptr.maskBits;
}
js.box2d.B2ShapeDef.prototype.setMaskBits = function() {
	var args = verifyArgs(arguments);
	this.rawptr.maskBits = args[0];
}
js.box2d.B2ShapeDef.prototype.getGroupIndex = function() {
	return this.rawptr.groupIndex;
}
js.box2d.B2ShapeDef.prototype.setGroupIndex = function() {
	var args = verifyArgs(arguments);
	this.rawptr.groupIndex = args[0];
}
js.box2d.B2ShapeDef.prototype.computeMass = function() {
	var args = verifyArgs(arguments);
	this.rawptr.ComputeMass(args[0]);
}

/* b2BoxDef */
js.box2d.B2BoxDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2BoxDef.prototype = new js.box2d.B2ShapeDef();
js.box2d.B2BoxDef.prototype.konohaclass = "js.box2d.B2BoxDef";
js.box2d.B2BoxDef.prototype._new = function() {
	this.rawptr = new b2BoxDef();
	return this;
}
js.box2d.B2BoxDef.prototype.getExtents = function() {
	return new js.box2d.B2Vec2(this.rawptr.extents);
}
js.box2d.B2BoxDef.prototype.setExtents = function() {
	var args = verifyArgs(arguments);
	this.rawptr.extents = args[0];
}

/* b2JointDef */
js.box2d.B2JointDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2JointDef.prototype = new konoha.Object();
js.box2d.B2JointDef.prototype.konohaclass = "js.box2d.B2JointDef";
js.box2d.B2JointDef.prototype._new = function() {
	this.rawptr = new b2JointDef();
	return this;
}
js.box2d.B2JointDef.prototype.getType = function() {
	return this.rawptr.type;
}
js.box2d.B2JointDef.prototype.setType = function() {
	var args = verifyArgs(arguments);
	this.rawptr.type = args[0];
}
//js.box2d.B2JointDef.prototype.getUserData = function() {
//	return this.rawptr.userData;
//}
//js.box2d.B2JointDef.prototype.setUserData = function() {
//	var args = verifyArgs(arguments);
//	this.rawptr.userData = args[0];
//}
//js.box2d.B2JointDef.prototype.getBody1 = function() {
//	return this.rawptr.body1;
//}
//js.box2d.B2JointDef.prototype.setBody1 = function() {
//	var args = verifyArgs(arguments);
//	this.rawptr.body1 = args[0];
//}
//js.box2d.B2JointDef.prototype.getBody2 = function() {
//	return this.rawptr.body2;
//}
//js.box2d.B2JointDef.prototype.setBody2 = function() {
//	var args = verifyArgs(arguments);
//	this.rawptr.body2 = args[0];
//}
js.box2d.B2JointDef.prototype.getCollideConnected = function() {
	return this.rawptr.collideConnected;
}
js.box2d.B2JointDef.prototype.setCollideConnected = function() {
	var args = verifyArgs(arguments);
	this.rawptr.collideConnected = args[0];
}

/* b2RevoluteJointDef */
js.box2d.B2RevoluteJointDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2RevoluteJointDef.prototype = new js.box2d.B2JointDef();
js.box2d.B2RevoluteJointDef.prototype.konohaclass = "js.box2d.B2RevoluteJointDef";
js.box2d.B2RevoluteJointDef.prototype._new = function() {
	this.rawptr = new b2RevoluteJointDef();
	return this;
}
js.box2d.B2RevoluteJointDef.prototype.getAnchorPoint = function() {
	return new js.box2d.B2Vec2(this.rawptr.anchorPoint);
}
js.box2d.B2RevoluteJointDef.prototype.setAnchorPoint = function() {
	var args = verifyArgs(arguments);
	this.rawptr.anchorPoint = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getLowerAngle = function() {
	return this.rawptr.lowerAngle;
}
js.box2d.B2RevoluteJointDef.prototype.setLowerAngle = function() {
	var args = verifyArgs(arguments);
	this.rawptr.lowerAngle = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getUpperAngle = function() {
	return this.rawptr.upperAngle;
}
js.box2d.B2RevoluteJointDef.prototype.setUpperAngle = function() {
	var args = verifyArgs(arguments);
	this.rawptr.upperAngle = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getMotorTorque = function() {
	return this.rawptr.motorTorque;
}
js.box2d.B2RevoluteJointDef.prototype.setMotorTorque = function() {
	var args = verifyArgs(arguments);
	this.rawptr.motorTorque = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getMotorSpeed = function() {
	return this.rawptr.motorSpeed;
}
js.box2d.B2RevoluteJointDef.prototype.setMotorSpeed = function() {
	var args = verifyArgs(arguments);
	this.rawptr.motorSpeed = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getEnableLimit = function() {
	return this.rawptr.enableLimit;
}
js.box2d.B2RevoluteJointDef.prototype.setEnableLimit = function() {
	var args = verifyArgs(arguments);
	this.rawptr.enableLimit = args[0];
}
js.box2d.B2RevoluteJointDef.prototype.getEnableMotor = function() {
	return this.rawptr.enableMotor;
}
js.box2d.B2RevoluteJointDef.prototype.setEnableMotor = function() {
	var args = verifyArgs(arguments);
	this.rawptr.enableMotor = args[0];
}

/* b2PrismaticJointDef */
js.box2d.B2JointDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2PrismaticJointDef.prototype = new js.box2d.B2JointDef();
js.box2d.B2PrismaticJointDef.prototype.konohaclass = "js.box2d.B2JointDef";
js.box2d.B2PrismaticJointDef.prototype._new = function() {
	this.rawptr = new b2PrismaticJointDef();
	return this;
}
js.box2d.B2PrismaticJointDef.prototype.getAnchorPoint = function() {
	return new js.box2d.B2Vec2(this.rawptr.anchorPoint);
}
js.box2d.B2PrismaticJointDef.prototype.setAnchorPoint = function() {
	var args = verifyArgs(arguments);
	this.rawptr.anchorPoint = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getAxis = function() {
	return new js.box2d.B2Vec2(this.rawptr.axis);
}
js.box2d.B2PrismaticJointDef.prototype.setAnchorPoint = function() {
	var args = verifyArgs(arguments);
	this.rawptr.anchorPoint = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getLowerAngle = function() {
	return this.rawptr.lowerAngle;
}
js.box2d.B2PrismaticJointDef.prototype.setLowerAngle = function() {
	var args = verifyArgs(arguments);
	this.rawptr.lowerAngle = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getUpperAngle = function() {
	return this.rawptr.upperAngle;
}
js.box2d.B2PrismaticJointDef.prototype.setUpperAngle = function() {
	var args = verifyArgs(arguments);
	this.rawptr.upperAngle = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getMotorTorque = function() {
	return this.rawptr.motorTorque;
}
js.box2d.B2PrismaticJointDef.prototype.setMotorTorque = function() {
	var args = verifyArgs(arguments);
	this.rawptr.motorTorque = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getMotorSpeed = function() {
	return this.rawptr.motorSpeed;
}
js.box2d.B2PrismaticJointDef.prototype.setMotorSpeed = function() {
	var args = verifyArgs(arguments);
	this.rawptr.motorSpeed = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getEnableLimit = function() {
	return this.rawptr.enableLimit;
}
js.box2d.B2PrismaticJointDef.prototype.setEnableLimit = function() {
	var args = verifyArgs(arguments);
	this.rawptr.enableLimit = args[0];
}
js.box2d.B2PrismaticJointDef.prototype.getEnableMotor = function() {
	return this.rawptr.enableMotor;
}
js.box2d.B2PrismaticJointDef.prototype.setEnableMotor = function() {
	var args = verifyArgs(arguments);
	this.rawptr.enableMotor = args[0];
}
