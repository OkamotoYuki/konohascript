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

js.Box2d.PolyDef = function(rawptr) {
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




	// this.prototype = function() {
	// 	var args = verifyArgs(Array.prototype.slice.call(arguments));
	// 	return .apply(this.rawptr, args);
	// }


