function verifyArgs(args) {
    for (var i = 0; i < args.length; i++) {
        if (args[i].rawptr) {
            args[i] = args[i].rawptr;
        }
    }
    return args;
}

js.box2d = function() {}

js.box2d.b2CircleDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2CircleDef";
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

js.Box2d.b2BodyDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2BodyDef";
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

js.box2d.b2Mat22 = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2Mat22";
	this.prototype = new konoha.Object();

//Public Properties
	this.prototype.getCol1 = function() { // b2Vec2
		return new js.Box2d.b2Vec2(this.rawptr.col1);
	}
	this.prototype.setCol1 = function(arg) {
		this.rawptr.col1 = arg.rawptr;
	}
	this.prototype.getCol2 = function() { // b2Vec2
		return js.Box2d.b2Vec2(this.rawptr.col1);
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
		return new js.Box2d.b2Mat22(Copy.apply(this.rawptr, args));
	}
	this.prototype.Invert = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Mat22(Invert.apply(this.rawptr, args));
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
		return new js.Box2d.b2Vec2(Solve.apply(this.rawptr, args));
	}
	this._new = function() {
		this.rawptr = new b2Mat22();
		return this;
	}
}

js.Box2d.b2PolyDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2PolyDef";
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

js.Box2d.b2Body = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2Body";
	this.prototype = new konoha.Object();
//Public Properties
	this.getE_allowSleepFlag = function() {
		return this.rawptr.e_allowSleepFlag;
	}
	this.getE_destroyFlag = function() {
		return this.rawptr.e_destroyFlag;
	}
	this.getE_frozenFlag = function() {
		return this.rawptr.e_frozenFlag;
	}
	this.getE_islanFlag = function() {
		return this.rawptr.e_islangFlag;
	}
	this.getE_sleepFlag = function() {
		return this.rawptr.e_sleepFlag;
	}
	this.getE_staticFlag = function() {
		return this.rawptr.e_staticFlag;
	}
	this.getM_angularDamping = function() {
		return this.rawptr.angularDamping;
	}
	this.setM_angularDamping = function(arg) {
		this.rawptr.angularDamping = arg;
	}
	this.getM_angularVetocity = function() {
		return this.rawptr.angularVelocity;
	}
	this.setM_angularVetocity = function(arg) {
		this.rawptr.angularVelocity = arg;
	}
	this.getM_center = function() {
		return new js.Box2d.b2Vec2(this.rawptr.m_center);
	}
	this.setM_center = function(arg) {
		this.rawptr.m_center = arg.rawptr;
	}
	this.getM_contactList = function() {
		return new js.Box2d.b2ContactNode(this.rawptr.m_contactList);
	}
	this.setM_contactList = function(arg) {
		this.rawptr.m_contactList = arg.rawptr;
	}
	this.getM_flag = function() {
		return this.rawptr.m_flag;
	}
	this.setM_flag = function(arg) {
		this.rawptr.m_flag = arg;
	}
	this.getM_force = function() {
		return new b2Vec2(this.rawptr.m_force);
	}
	this.setM_force = function(arg) {
		this.rawptr.m_force = arg.rawptr;
	}
	this.getM_I = function() {
		return this.rawptr.m_I;
	}
	this.set = function(arg) {
		this.rawptr.m_I = arg;
	}
	this.getM_invI = function() {
		return this.rawptr.invI;
	}
	this.setM_invI = function(arg) {
		this.rawptr.m_invI = arg;
	}
	this.getM_invMass = function() {
		return this.rawptr.m_invMass;
	}
	this.setM_invMass = function(arg) {
		this.rawptr.m_invMass = arg;
	}
	this.getM_jointList = function() {
		return new js.Box2d.b2JointNode(this.rawptr.m_jointList);
	}
	this.setM_jointList = function(arg) {
		this.rawptr.m_jointList = arg.rawptr;
	}
	this.getM_linearDamping = function() {
		return this.rawptr.linearDamping;
	}
	this.setM_linearDamping = function(arg) {
		this.rawptr.linearDamping = arg;
	}
	this.getM_linearVelocity = function() {
		return new js.Box2d.b2Vec2(this.rawptr.m_linearVelocity);
	}
	this.setM_linearVelocity = function(arg) {
		this.rawptr.linearVelocity = arg.rawptr;
	}
	this.getM_mass = function() {
		return this.rawptr.m_mass;
	}
	this.setM_mass = function(arg) {
		this.rawptr.m_mass = arg;
	}
	this.getM_next = function() {
		return new b2Body(this.rawptr.m_next);
	}
	this.setM_next = function(arg) {
		this.rawptr.m_next = arg.rawptr;
	}
	this.getM_position = function() {
		return new b2Vec2(this.rawptr.position);
	}
	this.setM_position = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.getM_position0 = function() {
		return new b2Vec2(this.rawptr.position0);
	}
	this.setM_position0 = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.getM_prev = function() {
		return new b2Body(this.rawptr.m_prev);
	}
	this.setM_prev = function(arg) {
		this.rawptr.m_prev = arg.rawptr;
	}
	this.getM_R = function() {
		return new b2Mat22(this.rawptr.m_R);
	}
	this.setM_R = function(arg) {
		this.rawptr.m_R = arg.rawptr;
	}
	this.getM_rotation = function() {
		return this.rawptr.m_rotation;
	}
	this.setM_rotation = function(arg) {
		this.rawptr.m_rotation = arg;
	}
	this.getM_rotation0 = function() {
		return this.rawptr.m_rotation0;
	}
	this.setM_rotation0 = function(arg) {
		this.rawptr.m_rotation0 = arg;
	}
	this.getM_shapeCount = function() {
		return this.rawptr.m_shapeCount;
	}
	this.setM_shapeCount = function(arg) {
		this.rawptr.m_shapeCount = arg;
	}
	this.getM_shapeList = function() {
		return new js.Box2d.b2Shape(this.rawptr.m_shapeList);
	}
	this.setM_shapeList = function(arg) {
		this.rawptr.m_shapeList = arg.rawptr;
	}
	this.getM_sleepTime = function() {
		return this.rawptr.m_sleepTime;
	}
	this.setM_sleepTime = function(arg) {
		this.rawptr.m_sleepTime = arg;
	}
	this.getM_torque = function() {
		return this.rawptr.m_torque;
	}
	this.setM_torque = function(arg) {
		this.rawptr.m_torque = arg;
	}
	this.getM_userData = function() {
		return this.rawptr.m_userData;
	}
	this.setM_userData = function(arg) {
		this.rawptr.m_userData = arg;
	}
	this.getM_world = function() {
		return new js.Box2d.b2World(this.rawptr.m_world);
	}
	this.setM_world = function(arg) {
		this.rawptr.m_world = arg.rawptr;
	}

















//Public Functions
}


	// this.prototype = function() {
	// 	var args = verifyArgs(Array.prototype.slice.call(arguments));
	// 	return .apply(this.rawptr, args);
	// }

