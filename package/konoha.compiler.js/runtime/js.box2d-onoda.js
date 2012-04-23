js.box2d = function() {}

js.box2d.b2CircleDef = function(rawptr) {
	this.rawptr = rawptr;
	this.konohaclass = "js.box2d.b2CircleDef";
	this.prototype = new konoha.Object();
//	js.box2d.b2CircleDef.prototype = new konoha.Object();

//Public Properties
	this.getRadius = function() {
		return this.rawptr.radius;
	}
	this.setRadius = function(r) {
		this.rawptr.radius = r;
	}

//Public Methods
}
var a = new js.Box2d.b2CircleDef(rawptr);
a.rawptr = b2CircleDef(geho, hgoe);

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
 	// this.prototype.getLinearVelocity = function() { // b2Vec2
	// 	return this.rawptr.linearVelocity;
	// }
	this.prototype.setLinearVelocity = function(arg) {
		this.rawptr.linearVelocity = arg;
	}
 	// this.prototype.getPosition = function() { // b2Vec2
	// 	return this.rawptr.position;
	// }
	this.prototype.setPosition = function(arg) {
		this.rawptr.position = arg;
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
		this.rawptr.shapes = arg->rawptr;
	}
	this.prototype.getUserData = function() { // var
		return this.rawptr.userData;
	}
	this.prototype.setUserData = function(arg) {
		this.rawptr.userData = arg;
	}
}

	// this.prototype = function() {
	// 	var args = verifyArgs(Array.prototype.slice.call(arguments));
	// 	return .apply(this.rawptr, args);
	// }



js.Box2d.b2Mat22 = function() {}
js.Box2d.b2Vec = function() {}
js.Box2d.PolyDef = function() {}




