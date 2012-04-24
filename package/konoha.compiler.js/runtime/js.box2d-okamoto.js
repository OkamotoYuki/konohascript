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
js.box2d.B2PrismaticJointDef.prototype.konohaclass = "js.box2d.B2PrismaticJointDef";
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
