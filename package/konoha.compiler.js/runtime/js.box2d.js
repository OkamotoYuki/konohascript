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
js.box2d.B2Vec2.prototype.setZero = function() {
	this.rawptr.setZero();
}
js.box2d.B2Vec2.prototype.set = function() {
	var args = verifyArgs(arguments);
	this.rawptr.set(args[0], args[1]);
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
	return new js.box2d.B2Vec2(this.rawptr.Make(args[0], args[1]));
}

/* b2ShapeDef */
js.box2d.B2ShapeDef = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2ShapeDef.prototype = new konoha.Object();
js.box2d.B2ShapeDef.prototype.konohaclass = "js.box2d.ShapeDef";
js.box2d.B2ShapeDef.prototype._new = function() {
	this.rawptr = new b2ShapeDef();
	return this;
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

/* b2CircleDef */
js.box2d.B2CircleDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2CircleDef";
	this.prototype = new konoha.Object();
//	js.box2d.b2CircleDef.prototype = new konoha.Object();

//Public Properties
	this.prototype.getRadius = function() {
		return this.rawptr.radius;
	}
	this.prototype.setRadius = function(r) {
		this.rawptr.radius = r;
	}

//Public Methods
	this.prototype._new = function() {
		this.rawptr = new b2CircleDef();
		return this;
	}
}

/* b2CircleDef */
js.Box2d.b2BodyDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2BodyDef";
	this.prototype = new konoha.Object();

//Public Properties
	this.prototype.getAllowSleep = function() { //Boolean
		return this.rawptr.allowSleep;
	}
	this.prototype.setAllowSleep = function(arg) {
		this.rawptr.allowSleep = arg;
	}
	this.prototype.getAngularDamping = function() { //Number
		return this.rawptr.angularDamping;
	}
	this.prototype.setAngularDamping = function(arg) {
		this.rawptr.angularVelocity = arg.rawptr;
	}
 	this.prototype.getAngularVelocity = function() { //Number
		return this.rawptr.angularVelocity;
	}
	this.prototype.setAngularVelocity = function(arg) {
		this.rawptr.angularVelocity = arg;
	}
 	this.prototype.getIsSleeping = function() { //Boolean
		return this.rawptr.isSleeping;
	}
 	this.prototype.setIsSleeping = function(arg) {
		this.rawptr.isSleeping = arg;
	}
 	this.prototype.getLinearDamping = function() { // Number
 		return this.rawptr.linearDamping;
	}
 	this.prototype.setLinearDamping = function(arg) {
 		this.rawptr.linearDamping = arg;
	}
 	this.prototype.getLinearVelocity = function() { // b2Vec2
		return new js.Box2d.b2Vec2(this.rawptr.linearVelocity);
	}
	this.prototype.setLinearVelocity = function(arg) {
		this.rawptr.linearVelocity = arg.rawptr;
	}
 	this.prototype.getPosition = function() { // b2Vec2
		return new js.Box2d.b2Vec2(this.rawptr.position);
	}
	this.prototype.setPosition = function(arg) {
		this.rawptr.position = arg.rawptr;
	}
 	this.prototype.getPreventRotation = function() { // Boolean
		return this.rawptr.preventRotation;
	}
	this.prototype.setPreventRotation = function(arg) {
		this.rawptr.preventRotation = arg;
	}
	this.prototype.getRotation = function() { // Number
		return this.rawptr.rotation;
	}
	this.prototype.setRotation = function(arg) {
		this.rawptr.rotation = arg;
	}
	this.prototype.getShapes = function() { // Array
		return new konoha.Array(this.rawptr.shapes);
	}
	this.prototype.setShapes = function(arg) {
		this.rawptr.shapes = arg.rawptr;
	}
	this.prototype.getUserData = function() { // var
		return this.rawptr.userData;
	}
	this.prototype.setUserData = function(arg) {
		this.rawptr.userData = arg;
	}
//Pucilb Functions
	this.prototype._new = function() {
		this.rawptr = new b2BodyDef();
		return this;
	}
	this.prototype.AddShape = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return AddShape.apply(this.rawptr, args);
	}
	this.prototype._new = function() {
		this.rawptr = new b2BodyDef();
		return this;
	}
}

/* b2Mat22 */
js.box2d.B2Mat22 = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2Mat22";
	this.prototype = new konoha.Object();

//Public Properties
	this.prototype.getCol1 = function() { // b2Vec2
		return new js.Box2d.B2Vec2(this.rawptr.col1);
	}
	this.prototype.setCol1 = function(arg) {
		this.rawptr.col1 = arg.rawptr;
	}
	this.prototype.getCol2 = function() { // b2Vec2
		return js.Box2d.B2Vec2(this.rawptr.col1);
	}
	this.prototype.setCol2 = function(arg) {
		this.rawptr.col1 = arg.rawptr;
	}
//Public Methods
	this.prototype.Abs = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Abs.apply(this.rawptr, args);
	}
	this.prototype.AddM = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return AddM.apply(this.rawptr, args);
	}
	this.prototype.Copy = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Mat22(Copy.apply(this.rawptr, args));
	}
	this.prototype.Invert = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Mat22(Invert.apply(this.rawptr, args));
	}
	this.prototype.Set = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Set.apply(this.rawptr, args);
	}
	this.prototype.SetIdentify = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetIdentify.apply(this.rawptr, args);
	}
	this.prototype.SetM = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetM.apply(this.rawptr, args);
	}
	this.prototype.SetVV = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetVV.apply(this.rawptr, args);
	}
	this.prototype.SetZero = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetZero.apply(this.rawptr, args);
	}
	this.prototype.Solve = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(Solve.apply(this.rawptr, args));
	}
	this._new = function() {
		this.rawptr = new b2Mat22();
		return this;
	}
}

/* b2PolyDef */
js.Box2d.PolyDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2PolyDef";
	this.prototype = new konoha.Object();
//Public Properties
	this.prototype.getVertexCount = function() {
		return this.rawptr.vertexCount;
	}
	this.prototype.setVertexCount = function(arg) {
		this.rawptr.vertexCount = arg.rawptr;
	}
//Public Functions
	this.prototype._new = function() {
		this.rawptr = new b2PolyDef();
		return this;
	}
}

js.Box2d.B2Body = function(rawptr) {
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2Body";
//Public Properties
	this.prototype.getE_allowSleepFlag = function() {
		return this.rawptr.e_allowSleepFlag;
	}
	this.prototype.getE_destroyFlag = function() {
		return this.rawptr.e_destroyFlag;
	}
	this.prototype.getE_frozenFlag = function() {
		return this.rawptr.e_frozenFlag;
	}
	this.prototype.getE_islanFlag = function() {
		return this.rawptr.e_islangFlag;
	}
	this.prototype.getE_sleepFlag = function() {
		return this.rawptr.e_sleepFlag;
	}
	this.prototype.getE_staticFlag = function() {
		return this.rawptr.e_staticFlag;
	}
	this.prototype.getM_angularDamping = function() {
		return this.rawptr.angularDamping;
	}
	this.prototype.setM_angularDamping = function(arg) {
		this.rawptr.angularDamping = arg;
	}
	this.prototype.getM_angularVetocity = function() {
		return this.rawptr.angularVelocity;
	}
	this.prototype.setM_angularVetocity = function(arg) {
		this.rawptr.angularVelocity = arg;
	}
	this.prototype.getM_center = function() {
		return new js.Box2d.B2Vec2(this.rawptr.m_center);
	}
	this.prototype.setM_center = function(arg) {
		this.rawptr.m_center = arg.rawptr;
	}
	this.prototype.getM_contactList = function() {
		return new js.Box2d.B2ContactNode(this.rawptr.m_contactList);
	}
	this.prototype.setM_contactList = function(arg) {
		this.rawptr.m_contactList = arg.rawptr;
	}
	this.prototype.getM_flag = function() {
		return this.rawptr.m_flag;
	}
	this.prototype.setM_flag = function(arg) {
		this.rawptr.m_flag = arg;
	}
	this.prototype.getM_force = function() {
		return new js.box2d.B2Vec2(this.rawptr.m_force);
	}
	this.prototype.setM_force = function(arg) {
		this.rawptr.m_force = arg.rawptr;
	}
	this.prototype.getM_I = function() {
		return this.rawptr.m_I;
	}
	this.prototype.set = function(arg) {
		this.rawptr.m_I = arg;
	}
	this.prototype.getM_invI = function() {
		return this.rawptr.invI;
	}
	this.prototype.setM_invI = function(arg) {
		this.rawptr.m_invI = arg;
	}
	this.prototype.getM_invMass = function() {
		return this.rawptr.m_invMass;
	}
	this.prototype.setM_invMass = function(arg) {
		this.rawptr.m_invMass = arg;
	}
	this.prototype.getM_jointList = function() {
		return new js.Box2d.B2JointNode(this.rawptr.m_jointList);
	}
	this.prototype.setM_jointList = function(arg) {
		this.rawptr.m_jointList = arg.rawptr;
	}
	this.prototype.getM_linearDamping = function() {
		return this.rawptr.linearDamping;
	}
	this.prototype.setM_linearDamping = function(arg) {
		this.rawptr.linearDamping = arg;
	}
	this.prototype.getM_linearVelocity = function() {
		return new js.Box2d.B2Vec2(this.rawptr.m_linearVelocity);
	}
	this.prototype.setM_linearVelocity = function(arg) {
		this.rawptr.linearVelocity = arg.rawptr;
	}
	this.prototype.getM_mass = function() {
		return this.rawptr.m_mass;
	}
	this.prototype.setM_mass = function(arg) {
		this.rawptr.m_mass = arg;
	}
	this.prototype.getM_next = function() {
		return new js.box2d.B2Body(this.rawptr.m_next);
	}
	this.prototype.setM_next = function(arg) {
		this.rawptr.m_next = arg.rawptr;
	}
	this.prototype.getM_position = function() {
		return new js.box2d.B2Vec2(this.rawptr.position);
	}
	this.prototype.setM_position = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.prototype.getM_position0 = function() {
		return new js.box2d.B2Vec2(this.rawptr.position0);
	}
	this.prototype.setM_position0 = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.prototype.getM_prev = function() {
		return new js.box2d.B2Body(this.rawptr.m_prev);
	}
	this.prototype.setM_prev = function(arg) {
		this.rawptr.m_prev = arg.rawptr;
	}
	this.prototype.getM_R = function() {
		return new js.box2d.B2Mat22(this.rawptr.m_R);
	}
	this.prototype.setM_R = function(arg) {
		this.rawptr.m_R = arg.rawptr;
	}
	this.prototype.getM_rotation = function() {
		return this.rawptr.m_rotation;
	}
	this.prototype.setM_rotation = function(arg) {
		this.rawptr.m_rotation = arg;
	}
	this.prototype.getM_rotation0 = function() {
		return this.rawptr.m_rotation0;
	}
	this.prototype.setM_rotation0 = function(arg) {
		this.rawptr.m_rotation0 = arg;
	}
	this.prototype.getM_shapeCount = function() {
		return this.rawptr.m_shapeCount;
	}
	this.prototype.setM_shapeCount = function(arg) {
		this.rawptr.m_shapeCount = arg;
	}
	this.prototype.getM_shapeList = function() {
		return new js.Box2d.B2Shape(this.rawptr.m_shapeList);
	}
	this.prototype.setM_shapeList = function(arg) {
		this.rawptr.m_shapeList = arg.rawptr;
	}
	this.prototype.getM_sleepTime = function() {
		return this.rawptr.m_sleepTime;
	}
	this.prototype.setM_sleepTime = function(arg) {
		this.rawptr.m_sleepTime = arg;
	}
	this.prototype.getM_torque = function() {
		return this.rawptr.m_torque;
	}
	this.prototype.setM_torque = function(arg) {
		this.rawptr.m_torque = arg;
	}
	this.prototype.getM_userData = function() {
		return this.rawptr.m_userData;
	}
	this.prototype.setM_userData = function(arg) {
		this.rawptr.m_userData = arg;
	}
	this.prototype.getM_world = function() {
		return new js.Box2d.B2World(this.rawptr.m_world);
	}
	this.prototype.setM_world = function(arg) {
		this.rawptr.m_world = arg.rawptr;
	}

//Public Functions
	this.prototype.AllowSleeping = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return AllowSleeping.apply(this.rawptr, args);
	}
	this.prototype.ApplyForce = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return ApplyForce.apply(this.rawptr, args);
	}
	this.prototype.ApplyImpulse = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return ApplyImpulse.apply(this.rawptr, args);
	}
	this.prototype.ApplyTorque = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return ApplyTorque.apply(this.rawptr, args);
	}
	this.prototype.Destroy = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Destroy.apply(this.rawptr, args);
	}
	this.prototype.Freeze = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Freeze.apply(this.rawptr, args);
	}
	this.prototype.GetAngularVelocity = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetAngularVelocity.apply(this.rawptr, args);
	}
	this.prototype.GetCenterPosition = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetCenterPosition.apply(this.rawptr, args));
	}
	this.prototype.GetContactList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2ContactNode(GetContactList.apply(this.rawptr, args));
	}
	this.prototype.GetInertia = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetInertia.apply(this.rawptr, args));
	}
	this.prototype.GetJointList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2JointNode(GetJointList.apply(this.rawptr, args));
	}
	this.prototype.GetLinearVelocity = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetLinearVelocity.apply(this.rawptr, args));
	}
	this.prototype.GetLocalPoint = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetLocalPoint.apply(this.rawptr, args));
	}
	this.prototype.GetLocalVector = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetLocalVector.apply(this.rawptr, args));
	}
	this.prototype.GetMass = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetMass.apply(this.rawptr, args);
	}
	this.prototype.GetNext = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Body(GetNext.apply(this.rawptr, args));
	}
	this.prototype.GetOriginPosition = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetOriginPosition.apply(this.rawptr, args));
	}
	this.prototype.GetRotation = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetRotation.apply(this.rawptr, args);
	}
	this.prototype.GetRotationMatrix = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Mat22(GetRotationMatrix.apply(this.rawptr, args));
	}
	this.prototype.GetShapeList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Shape(GetShapeList.apply(this.rawptr, args));
	}
	this.prototype.GetUserData = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetUserData.apply(this.rawptr, args);
	}
	this.prototype.GetWorldPoint = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetWorldPoint.apply(this.rawptr, args));
	}
	this.prototype.GetWorldVector = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Vec2(GetWorldVector.apply(this.rawptr, args));
	}
	this.prototype.IsConnected = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return IsConnected.apply(this.rawptr, args);
	}
	this.prototype.IsFrozen = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return IsFrozen.apply(this.rawptr, args);
	}
	this.prototype.IsSleeping = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return IsSleeping.apply(this.rawptr, args);
	}
	this.prototype.IsStatic = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return IsStatic.apply(this.rawptr, args);
	}
	this.prototype.QuickSyncShapes = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return QuickSyncShapes.apply(this.rawptr, args);
	}
	this.prototype.SetAngularVelocity = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetAngularVelocity.apply(this.rawptr, args);
	}
	this.prototype.SetCenterPosition = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetCenterPosition.apply(this.rawptr, args);
	}
	this.prototype.SetLinearVelocity = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetLinearVelocity.apply(this.rawptr, args);
	}
	this.prototype.SetOriginPosition = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SetOriginPosition.apply(this.rawptr, args);
	}
	this.prototype.SynchronizeShapes = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return SynchronizeShapes.apply(this.rawptr, args);
	}
	this.prototype.WakeUp = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return WakeUp.apply(this.rawptr, args);
	}
	this.prototype._new = function() {
		this.rawptr = new b2Body(arguments[0], arguments[1]);
		return this;
	}
}

js.box2d.B2Contact = function(rawptr) {
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2Contact";
//Public Properties
	this.prototype.getE_destroyFlag = function() {
		return this.rawptr.e_destroyFlag;
	}
	this.prototype.getE_islandFlag = function() {
		return this.rawptr.e_islangFlag;
	}
	this.prototype.getM_flags = function() {
		return this.rawptr.m_flags;
	}
	this.prototype.setM_flags = function(arg) {
		this.rawptr.m_flags = arg;
	}
	this.prototype.getM_friction = function() {
		return this.rawptr.m_friction;
	}
	this.prototype.setM_friction = function(arg) {
		this.rawptr.m_friction = arg;
	}
	this.prototype.getM_manifoldCount = function() {
		return this.rawptr.m_manifoldCount;
	}
	this.prototype.setM_manifoldCount = function(arg) {
		this.rawptr.m_manifoldCount = arg;
	}
	this.prototype.getM_next = function() {
		return new js.Box2d.B2Contact(this.rawptr.m_next);
	}
	this.prototype.setM_next = function(arg) {
		this.rawptr.m_next = arg.rawptr;
	}
	this.prototype.getM_node1 = function() {
		return new js.Box2d.B2ContactNode(this.rawptr.m_node1);
	}
	this.prototype.setM_node1 = function(arg) {
		this.rawptr.m_node1 = arg.rawptr;
	}
	this.prototype.getM_node2 = function() {
		return new js.Box2d.B2ContactNode(this.rawptr.M_node2);
	}
	this.prototype.setM_node2 = function(arg) {
		this.rawptr.m_node2 = arg.rawptr;
	}
	this.prototype.getM_prev = function() {
		return new js.Box2d.B2Contact(this.rawptr.m_prev);
	}
	this.prototype.setM_prev = function(arg) {
		this.rawptr.m_prev = arg.rawptr;
	}
	this.prototype.getM_restitution = function() {
		return this.rawptr.m_restitution;
	}
	this.prototype.setM_restitution = function(arg) {
		this.rawptr = arg;
	}
	this.prototype.getM_shape1 = function() {
		return new js.Box2d.B2Shape(this.rawptr.m_shape1);
	}
	this.prototype.setM_shape1 = function(arg) {
		this.rawptr.m_shape1 = arg.rawptr;
	}
	this.prototype.getM_shape2 = function() {
		return new js.Box2d.B2Shape(this.rawptr.m_shape1);
	}
	this.prototype.setM_shape2 = function(arg) {
		this.rawptr.m_shape1 = arg.rawptr;
	}
	this.prototype.getS_initialized = function() {
		return this.rawptr.s_initialized;
	}
	this.prototype.getS_registers = function() {
		return this.rawptr.registers.rawptr;
	}
//Public Functions
	this.prototype._new = function() {
		this.rawptr = new b2Contact(arguments[0], arguments[1]);
		return this;
	}
	this.prototype.AddType = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return AddType.apply(this.rawptr, args);
	}
	this.prototype.Create = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Contact(Create.apply(this.rawptr, args));
	}
	this.prototype.Destroy = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Destroy.apply(this.rawptr, args);
	}
	this.prototype.Evaluate = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return Evaluate.apply(this.rawptr, args);
	}
	this.prototype.GetManifoldCount = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetManifoldCount.apply(this.rawptr, args);
	}
	this.prototype.GetNext = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Contact(GetNext.apply(this.rawptr, args));
	}
	this.prototype.GetShape1 = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Shape(GetShape1.apply(this.rawptr, args));
	}
	this.prototype.GetShape2 = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.B2Shape(GetShape2.apply(this.rawptr, args));
	}
	this.prototype.InitializeRegisters = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return InitializeRegisters.apply(this.rawptr, args);
	}
}

js.box2d.B2CollisionFilter = function(rawptr) {
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2CollisionFilter";

//Public Properties
	this.prototype.getB2_defaultFilter = function() {
		return new js.box2d.B2CollisionFilter(this.rawptr.b2_defaultFilter);
	}
//Public Methods
	this.prototype.ShouldCollide = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return ShouldCollide.apply(this.rawptr, args);
	}
}

js.box2d.B2WorldListener = function(rawptr) {
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.B2WorldListener";

//Public Properties
	this.prototype.getB2_destroyBody = function() {
		return this.rawptr.b2_destroyBody;
	}
	this.prototype.getB2_freezeBody = function() {
		return this.rawptr.b2_freezeBody;
	}
//Public Methods
	this.prototype.NotifyBoundaryViolated = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return NotifyBoundaryViolated.apply(this.rawptr, args);
	}
	this.prototype.NotifyJointDestroyed = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return NotifyJointDestroyed.apply(this.rawptr, args);
	}
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
js.box2d.B2JointDef.prototype.getUserData = function() {
	return this.rawptr.userData;
}
js.box2d.B2JointDef.prototype.setUserData = function() {
	var args = verifyArgs(arguments);
	this.rawptr.userData = args[0];
}
js.box2d.B2JointDef.prototype.getBody1 = function() {
	return this.rawptr.body1;
}
js.box2d.B2JointDef.prototype.setBody1 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.body1 = args[0];
}
js.box2d.B2JointDef.prototype.getBody2 = function() {
	return this.rawptr.body2;
}
js.box2d.B2JointDef.prototype.setBody2 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.body2 = args[0];
}
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

/* b2AABB */
js.box2d.B2AABB = function(rawptr) {
	this.rawptr = rawptr;
}
js.box2d.B2AABB.prototype = new konoha.Object();
js.box2d.B2AABB.prototype.konohaclass = "js.box2d.B2JointDef";
js.box2d.B2AABB.prototype._new = function() {
	this.rawptr = new b2AABB();
	return this;
}
js.box2d.B2AABB.prototype.getMinVertex = function() {
	return new js.box2d.B2Vec2(this.rawptr.minVertex);
}
js.box2d.B2AABB.prototype.setMinVertex = function() {
	var args = verifyArgs(arguments);
	this.rawptr.minVertex = args[0];
}
js.box2d.B2AABB.prototype.getMaxVertex = function() {
	return new js.box2d.B2Vec2(this.rawptr.maxVertex);
}
js.box2d.B2AABB.prototype.setMaxVertex = function() {
	var args = verifyArgs(arguments);
	this.rawptr.maxVertex = args[0];
}

/* b2World */
js.box2d.B2World = function(rawptr) {
	this.rawptr = rawptr
}
js.box2d.B2World.prototype = new konoha.Object();
js.box2d.B2World.prototype.konohaclass = "js.box2d.B2World";
js.box2d.B2World.prototype.getM_bodyCount = function() {
	return this.rawptr.m_bodyCount;
}
js.box2d.B2World.prototype.setM_bodyCount = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_bodyCount = args[0];
};
js.box2d.B2World.prototype.getM_bodyDestroyList = function() {
	return new js.box2d.B2Body(this.rawptr.m_bodyDestroyList);
}
js.box2d.B2World.prototype.setM_bodyDestroyList = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_bodyDestroyList = args[0];
};
js.box2d.B2World.prototype.getM_bodyList = function() {
	return new js.box2d.B2Body(this.rawptr.m_bodyList);
}
js.box2d.B2World.prototype.setM_bodyList = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_bodyList = args[0];
};
js.box2d.B2World.prototype.getM_broadPhase = function() {
	return new js.box2d.B2BroadPhase(this.rawptr.m_broadPhase);
}
js.box2d.B2World.prototype.setM_broadPhase = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_broadPhase = args[0];
};
js.box2d.B2World.prototype.getContactCount = function() {
	return this.rawptr.contactCount;
}
js.box2d.B2World.prototype.setContactCount = function() {
	var args = verifyArgs(arguments);
	this.rawptr.contactCount = args[0];
};
js.box2d.B2World.prototype.getM_contactList = function() {
	return new js.box2d.B2Contact(this.rawptr.m_contactList);
}
js.box2d.B2World.prototype.setM_contactList = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_contactList = args[0];
};
js.box2d.B2World.prototype.getM_contactManager = function() {
	return new js.box2d.B2ContactManager(this.rawptr.m_contactManager);
}
js.box2d.B2World.prototype.setM_contactManager = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_contactManager = args[0];
};
js.box2d.B2World.prototype.getM_filter = function() {
	return new js.box2d.B2CollisionFilter(this.rawptr.m_filter);
}
js.box2d.B2World.prototype.setM_filter = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_filter = args[0];
};
js.box2d.B2World.prototype.getM_gragity = function() {
	return new js.box2d.B2Vec2(this.rawptr.m_gragity);
}
js.box2d.B2World.prototype.setM_gragity = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_gragity = args[0];
};
js.box2d.B2World.prototype.getM_groundBody = function() {
	return new js.box2d.B2Body(this.rawptr.m_groundBody);
}
js.box2d.B2World.prototype.setM_groundBody = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_groundBody = args[0];
};
js.box2d.B2World.prototype.getM_jointCount = function() {
	return this.rawptr.m_jointCount;
}
js.box2d.B2World.prototype.setM_jointCount = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_jointCount = args[0];
};
js.box2d.B2World.prototype.getM_jointList = function() {
	return new js.box2d.B2Joint(this.rawptr.m_jointList);
}
js.box2d.B2World.prototype.setM_jointList = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_jointList = args[0];
};
js.box2d.B2World.prototype.getM_listener = function() {
	return new js.box2d.B2WorldListener(this.rawptr.m_listener);
}
js.box2d.B2World.prototype.setM_listener = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_listener = args[0];
};
js.box2d.B2World.prototype.getS_enablePositionCorrection = function() {
	return this.rawptr.s_enablePositionCorrection;
}
js.box2d.B2World.prototype.setS_enablePositionCorrection = function() {
	var args = verifyArgs(arguments);
	this.rawptr.s_enablePositionCorrection = args[0];
};
js.box2d.B2World.prototype.getS_enableWarmStarting = function() {
	return this.rawptr.s_enableWarmStarting;
}
js.box2d.B2World.prototype.setS_enableWarmStarting = function() {
	var args = verifyArgs(arguments);
	this.rawptr.s_enableWarmStarting = args[0];
};
js.box2d.B2World.prototype.cleanBodyList = function() {
	var args = verifyArgs(arguments);
	this.rawptr.CleanBodyList(args[0]);
}
js.box2d.B2World.prototype.createBody = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Body(this.rawptr.CreateBody(args[0]));
}
js.box2d.B2World.prototype.createJoint = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Joint(this.rawptr.CreateJoint(args[0]));
}
js.box2d.B2World.prototype.destroyBody = function() {
	var args = verifyArgs(arguments);
	this.rawptr.DestroyBody(args[0]);
}
js.box2d.B2World.prototype.destroyJoint = function() {
	var args = verifyArgs(arguments);
	this.rawptr.DestroyJoint(args[0]);
}
js.box2d.B2World.prototype.getBodyList = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Body(this.rawptr.GetBodyList(args[0]));
}
js.box2d.B2World.prototype.getContactList = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Contact(this.rawptr.GetContactList(args[0]));
}
js.box2d.B2World.prototype.getGroundBody = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Body(this.rawptr.GetGroundBody(args[0]));
}
js.box2d.B2World.prototype.getJointList = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Joint(this.rawptr.GetJointList(args[0]));
}
js.box2d.B2World.prototype.setFilter = function() {
	var args = verifyArgs(arguments);
	this.rawptr.SetFilter(args[0]);
}
js.box2d.B2World.prototype.setListener = function() {
	var args = verifyArgs(arguments);
	this.rawptr.SetListener(args[0]);
}

/* b2Joint */
js.box2d.B2Joint = function(rawptr) {
	this.rawptr = rawptr
}
js.box2d.B2Joint.prototype = new konoha.Object();
js.box2d.B2Joint.prototype.konohaclass = "js.box2d.B2Joint";
js.box2d.B2Joint.prototype.getM_body1 = function() {
	return new js.box2d.B2Body(this.rawptr.m_body1);
}
js.box2d.B2Joint.prototype.setM_body1 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_body1 = args[0];
};
js.box2d.B2Joint.prototype.getM_body2 = function() {
	return new js.box2d.B2Body(this.rawptr.m_body2);
}
js.box2d.B2Joint.prototype.setM_body2 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_body2 = args[0];
};
js.box2d.B2Joint.prototype.getM_collideConnected = function() {
	return this.rawptr.m_collideConnected;
}
js.box2d.B2Joint.prototype.setM_collideConnected = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_collideConnected = args[0];
};
js.box2d.B2Joint.prototype.getM_islandFlag = function() {
	return this.rawptr.m_islandFlag;
}
js.box2d.B2Joint.prototype.setM_islandFlag = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_islandFlag = args[0];
};
js.box2d.B2Joint.prototype.getM_next = function() {
	return new js.box2d.B2Joint(this.rawptr.m_next);
}
js.box2d.B2Joint.prototype.setM_next = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_next = args[0];
};
js.box2d.B2Joint.prototype.getM_node1 = function() {
	return new js.box2d.B2JointNode(this.rawptr.m_node1);
}
js.box2d.B2Joint.prototype.setM_node1 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_node1 = args[0];
};
js.box2d.B2Joint.prototype.getM_node2 = function() {
	return new js.box2d.B2JointNode(this.rawptr.m_node2);
}
js.box2d.B2Joint.prototype.setM_node2 = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_node2 = args[0];
};
js.box2d.B2Joint.prototype.getM_prev = function() {
	return new js.box2d.B2Joint(this.rawptr.m_prev);
}
js.box2d.B2Joint.prototype.setM_prev = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_prev = args[0];
};
js.box2d.B2Joint.prototype.getM_type = function() {
	return this.rawptr.m_type;
}
js.box2d.B2Joint.prototype.setM_type = function() {
	var args = verifyArgs(arguments);
	this.rawptr.m_type = args[0];
};
js.box2d.B2Joint.prototype.create = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Joint(this.rawptr.Create(args[0]));
}
js.box2d.B2Joint.prototype.destroy = function() {
	var args = verifyArgs(arguments);
	this.rawptr.Destroy(args[0]);
}
js.box2d.B2Joint.prototype.getAnchor1 = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Vec2(this.rawptr.GetAnchor1(args[0]));
}
js.box2d.B2Joint.prototype.getAnchor2 = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Vec2(this.rawptr.GetAnchor2(args[0]));
}
js.box2d.B2Joint.prototype.getBody1 = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Body(this.rawptr.GetBody1(args[0]));
}
js.box2d.B2Joint.prototype.getBody2 = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Body(this.rawptr.GetBody2(args[0]));
}
js.box2d.B2Joint.prototype.getNext = function() {
	var args = verifyArgs(arguments);
	return new js.box2d.B2Joint(this.rawptr.GetNext(args[0]));
}
js.box2d.B2Joint.prototype.GetType = function() {
	var args = verifyArgs(arguments);
	return this.rawptr.GetType(args[0]);
}
js.box2d.B2Joint.prototype.preparePositionSolver = function() {
	var args = verifyArgs(arguments);
	this.rawptr.PreparePositionSolver(args[0]);
}
js.box2d.B2Joint.prototype.prepareVelocitySolver = function() {
	var args = verifyArgs(arguments);
	this.rawptr.PrepareVelocitySolver(args[0]);
}
js.box2d.B2Joint.prototype.solvePositionConstraints = function() {
	var args = verifyArgs(arguments);
	return this.rawptr.SolvePositionConstraints(args[0]);
}
js.box2d.B2Joint.prototype.solveVelocityConstraints = function() {
	var args = verifyArgs(arguments);
	this.rawptr.SolveVelocityConstraints(args[0]);
}
js.box2d.B2Joint.prototype.getE_atLowerLimit = function() {
	return this.rawptr.e_atLowerLimit;
}
js.box2d.B2Joint.prototype.getE_atUpperLimit = function() {
	return this.rawptr.e_atUpperLimit;
}
js.box2d.B2Joint.prototype.getE_distanceJoint = function() {
	return this.rawptr.e_distanceJoint;
}
js.box2d.B2Joint.prototype.getE_equalLimits = function() {
	return this.rawptr.e_equalLimits;
}
js.box2d.B2Joint.prototype.getE_gearJoint = function() {
	return this.rawptr.e_gearJoint;
}
js.box2d.B2Joint.prototype.getE_inactiveLimit = function() {
	return this.rawptr.e_inactiveLimit;
}
js.box2d.B2Joint.prototype.getE_mouseJoint = function() {
	return this.rawptr.e_mouseJoint;
}
js.box2d.B2Joint.prototype.getE_prismaticJoint = function() {
	return this.rawptr.e_prismaticJoint;
}
js.box2d.B2Joint.prototype.getE_pulleyJoint = function() {
	return this.rawptr.e_pulleyJoint;
}
js.box2d.B2Joint.prototype.getE_revoluteJoint = function() {
	return this.rawptr.e_revoluteJoint;
}
js.box2d.B2Joint.prototype.getE_unknownJoint = function() {
	return this.rawptr.e_unknownJoint;
}
