//int QSwipeGesture.horizontalDirection();
KMETHOD QSwipeGesture_horizontalDirection(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QSwipeGesture *  qp = RawPtr_to(QSwipeGesture *, sfp[0]);
	if (qp) {
		QSwipeGesture::SwipeDirection ret_v = qp->horizontalDirection();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//void QSwipeGesture.setSwipeAngle(float value);
KMETHOD QSwipeGesture_setSwipeAngle(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QSwipeGesture *  qp = RawPtr_to(QSwipeGesture *, sfp[0]);
	if (qp) {
		qreal value = Float_to(qreal, sfp[1]);
		qp->setSwipeAngle(value);
	}
	RETURNvoid_();
}

//float QSwipeGesture.getSwipeAngle();
KMETHOD QSwipeGesture_getSwipeAngle(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QSwipeGesture *  qp = RawPtr_to(QSwipeGesture *, sfp[0]);
	if (qp) {
		qreal ret_v = qp->swipeAngle();
		RETURNf_(ret_v);
	} else {
		RETURNf_(0.0f);
	}
}

//int QSwipeGesture.verticalDirection();
KMETHOD QSwipeGesture_verticalDirection(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QSwipeGesture *  qp = RawPtr_to(QSwipeGesture *, sfp[0]);
	if (qp) {
		QSwipeGesture::SwipeDirection ret_v = qp->verticalDirection();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}


DummyQSwipeGesture::DummyQSwipeGesture()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}
DummyQSwipeGesture::~DummyQSwipeGesture()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQSwipeGesture::setSelf(knh_RawPtr_t *ptr)
{
	DummyQSwipeGesture::self = ptr;
	DummyQGesture::setSelf(ptr);
}

bool DummyQSwipeGesture::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQGesture::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQSwipeGesture::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQSwipeGesture::event_map->bigin();
	if ((itr = DummyQSwipeGesture::event_map->find(str)) == DummyQSwipeGesture::event_map->end()) {
		bool ret = false;
		ret = DummyQGesture::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQSwipeGesture::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQSwipeGesture::slot_map->bigin();
	if ((itr = DummyQSwipeGesture::slot_map->find(str)) == DummyQSwipeGesture::slot_map->end()) {
		bool ret = false;
		ret = DummyQGesture::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQSwipeGesture::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQSwipeGesture::reftrace p->rawptr=[%p]\n", p->rawptr);

	tail_ = DummyQGesture::reftrace(ctx, p, tail_);

	return tail_;
}

void DummyQSwipeGesture::connection(QObject *o)
{
	QSwipeGesture *p = dynamic_cast<QSwipeGesture*>(o);
	if (p != NULL) {
	}
	DummyQGesture::connection(o);
}

KQSwipeGesture::~KQSwipeGesture()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QSwipeGesture_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQSwipeGesture *qp = RawPtr_to(KQSwipeGesture *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QSwipeGesture]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QSwipeGesture]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QSwipeGesture_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQSwipeGesture *qp = RawPtr_to(KQSwipeGesture *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QSwipeGesture]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QSwipeGesture]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QSwipeGesture_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQSwipeGesture *qp = (KQSwipeGesture *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QSwipeGesture*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QSwipeGesture_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQSwipeGesture *qp = (KQSwipeGesture *)p->rawptr;
		KQSwipeGesture *qp = static_cast<KQSwipeGesture*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QSwipeGesture_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQSwipeGesture::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

bool KQSwipeGesture::event(QEvent *event)
{
	if (!dummy->eventDispatcher(event)) {
		QSwipeGesture::event(event);
		return false;
	}
//	QSwipeGesture::event(event);
	return true;
}

static knh_IntData_t QSwipeGestureConstInt[] = {
	{"NoDirection", QSwipeGesture::NoDirection},
	{"Left", QSwipeGesture::Left},
	{"Right", QSwipeGesture::Right},
	{"Up", QSwipeGesture::Up},
	{"Down", QSwipeGesture::Down},
	{NULL, 0}
};

DEFAPI(void) constQSwipeGesture(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi) {
	kapi->loadClassIntConst(ctx, cid, QSwipeGestureConstInt);
}


DEFAPI(void) defQSwipeGesture(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QSwipeGesture";
	cdef->free = QSwipeGesture_free;
	cdef->reftrace = QSwipeGesture_reftrace;
	cdef->compareTo = QSwipeGesture_compareTo;
}


