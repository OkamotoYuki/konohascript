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
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2CircleDef";
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
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2BodyDef";

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
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2Mat22";

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
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2PolyDef";
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
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2Body";
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
		return new js.Box2d.b2Vec2(this.rawptr.m_center);
	}
	this.prototype.setM_center = function(arg) {
		this.rawptr.m_center = arg.rawptr;
	}
	this.prototype.getM_contactList = function() {
		return new js.Box2d.b2ContactNode(this.rawptr.m_contactList);
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
		return new b2Vec2(this.rawptr.m_force);
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
		return new js.Box2d.b2JointNode(this.rawptr.m_jointList);
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
		return new js.Box2d.b2Vec2(this.rawptr.m_linearVelocity);
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
		return new b2Body(this.rawptr.m_next);
	}
	this.prototype.setM_next = function(arg) {
		this.rawptr.m_next = arg.rawptr;
	}
	this.prototype.getM_position = function() {
		return new b2Vec2(this.rawptr.position);
	}
	this.prototype.setM_position = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.prototype.getM_position0 = function() {
		return new b2Vec2(this.rawptr.position0);
	}
	this.prototype.setM_position0 = function(arg) {
		this.rawptr.m_position = arg.rawptr;
	}
	this.prototype.getM_prev = function() {
		return new b2Body(this.rawptr.m_prev);
	}
	this.prototype.setM_prev = function(arg) {
		this.rawptr.m_prev = arg.rawptr;
	}
	this.prototype.getM_R = function() {
		return new b2Mat22(this.rawptr.m_R);
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
		return new js.Box2d.b2Shape(this.rawptr.m_shapeList);
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
		return new js.Box2d.b2World(this.rawptr.m_world);
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
		return new js.Box2d.b2Vec2(GetCenterPosition.apply(this.rawptr, args));
	}
	this.prototype.GetContactList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2ContactNode(GetContactList.apply(this.rawptr, args));
	}
	this.prototype.GetInertia = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetInertia.apply(this.rawptr, args));
	}
	this.prototype.GetJointList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2JointNode(GetJointList.apply(this.rawptr, args));
	}
	this.prototype.GetLinearVelocity = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetLinearVelocity.apply(this.rawptr, args));
	}
	this.prototype.GetLocalPoint = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetLocalPoint.apply(this.rawptr, args));
	}
	this.prototype.GetLocalVector = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetLocalVector.apply(this.rawptr, args));
	}
	this.prototype.GetMass = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetMass.apply(this.rawptr, args);
	}
	this.prototype.GetNext = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Body(GetNext.apply(this.rawptr, args));
	}
	this.prototype.GetOriginPosition = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetOriginPosition.apply(this.rawptr, args));
	}
	this.prototype.GetRotation = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetRotation.apply(this.rawptr, args);
	}
	this.prototype.GetRotationMatrix = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Mat22(GetRotationMatrix.apply(this.rawptr, args));
	}
	this.prototype.GetShapeList = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Shape(GetShapeList.apply(this.rawptr, args));
	}
	this.prototype.GetUserData = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return GetUserData.apply(this.rawptr, args);
	}
	this.prototype.GetWorldPoint = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetWorldPoint.apply(this.rawptr, args));
	}
	this.prototype.GetWorldVector = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Vec2(GetWorldVector.apply(this.rawptr, args));
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

js.Box2d.b2Contact = function(rawptr) {
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
		return new js.Box2d.b2Contact(this.rawptr.m_next);
	}
	this.prototype.setM_next = function(arg) {
		this.rawptr.m_next = arg.rawptr;
	}
	this.prototype.getM_node1 = function() {
		return new js.Box2d.b2ContactNode(this.rawptr.m_node1);
	}
	this.prototype.setM_node1 = function(arg) {
		this.rawptr.m_node1 = arg.rawptr;
	}
	this.prototype.getM_node2 = function() {
		return new js.Box2d.b2ContactNode(this.rawptr.M_node2);
	}
	this.prototype.setM_node2 = function(arg) {
		this.rawptr.m_node2 = arg.rawptr;
	}
	this.prototype.getM_prev = function() {
		return new js.Box2d.b2Contact(this.rawptr.m_prev);
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
		return new js.Box2d.b2Shape(this.rawptr.m_shape1);
	}
	this.prototype.setM_shape1 = function(arg) {
		this.rawptr.m_shape1 = arg.rawptr;
	}
	this.prototype.getM_shape2 = function() {
		return new js.Box2d.b2Shape(this.rawptr.m_shape1);
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
		return new js.Box2d.b2Contact(Create.apply(this.rawptr, args));
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
		return new js.Box2d.b2Contact(GetNext.apply(this.rawptr, args));
	}
	this.prototype.GetShape1 = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Shape(GetShape1.apply(this.rawptr, args));
	}
	this.prototype.GetShape2 = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return new js.Box2d.b2Shape(GetShape2.apply(this.rawptr, args));
	}
	this.prototype.InitializeRegisters = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return InitializeRegisters.apply(this.rawptr, args);
	}
}

js.Box2d.b2CollisionFilter = function(rawptr) {
	this.prototype = new konoha.Object();
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2CollisionFilter";

//Public Properties
	this.prototype.getB2_defaultFilter = function() {
		return new js.Box2d.b2CollisionFilter(this.rawptr.b2_defaultFilter);
	}
//Public Methods
	this.prototype.ShouldCollide = function() {
		var args = verifyArgs(Array.prototype.slice.call(arguments));
		return ShouldCollide.apply(this.rawptr, args);
	}
}
