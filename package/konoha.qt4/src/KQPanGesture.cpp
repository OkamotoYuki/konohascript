//float QPanGesture.getAcceleration();
KMETHOD QPanGesture_getAcceleration(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		qreal ret_v = qp->acceleration();
		RETURNf_(ret_v);
	} else {
		RETURNf_(0.0f);
	}
}

//QPointF QPanGesture.delta();
KMETHOD QPanGesture_delta(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		QPointF ret_v = qp->delta();
		QPointF *ret_v_ = new QPointF(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QPointF QPanGesture.lastOffset();
KMETHOD QPanGesture_lastOffset(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		QPointF ret_v = qp->lastOffset();
		QPointF *ret_v_ = new QPointF(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QPointF QPanGesture.offset();
KMETHOD QPanGesture_offset(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		QPointF ret_v = qp->offset();
		QPointF *ret_v_ = new QPointF(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//void QPanGesture.setAcceleration(float value);
KMETHOD QPanGesture_setAcceleration(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		qreal value = Float_to(qreal, sfp[1]);
		qp->setAcceleration(value);
	}
	RETURNvoid_();
}

//void QPanGesture.setLastOffset(QPointF value);
KMETHOD QPanGesture_setLastOffset(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		const QPointF  value = *RawPtr_to(const QPointF *, sfp[1]);
		qp->setLastOffset(value);
	}
	RETURNvoid_();
}

//void QPanGesture.setOffset(QPointF value);
KMETHOD QPanGesture_setOffset(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QPanGesture *  qp = RawPtr_to(QPanGesture *, sfp[0]);
	if (qp) {
		const QPointF  value = *RawPtr_to(const QPointF *, sfp[1]);
		qp->setOffset(value);
	}
	RETURNvoid_();
}


DummyQPanGesture::DummyQPanGesture()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}
DummyQPanGesture::~DummyQPanGesture()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQPanGesture::setSelf(knh_RawPtr_t *ptr)
{
	DummyQPanGesture::self = ptr;
	DummyQGesture::setSelf(ptr);
}

bool DummyQPanGesture::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQGesture::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQPanGesture::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQPanGesture::event_map->bigin();
	if ((itr = DummyQPanGesture::event_map->find(str)) == DummyQPanGesture::event_map->end()) {
		bool ret = false;
		ret = DummyQGesture::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQPanGesture::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQPanGesture::slot_map->bigin();
	if ((itr = DummyQPanGesture::slot_map->find(str)) == DummyQPanGesture::slot_map->end()) {
		bool ret = false;
		ret = DummyQGesture::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQPanGesture::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQPanGesture::reftrace p->rawptr=[%p]\n", p->rawptr);

	tail_ = DummyQGesture::reftrace(ctx, p, tail_);

	return tail_;
}

void DummyQPanGesture::connection(QObject *o)
{
	QPanGesture *p = dynamic_cast<QPanGesture*>(o);
	if (p != NULL) {
	}
	DummyQGesture::connection(o);
}

KQPanGesture::~KQPanGesture()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QPanGesture_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQPanGesture *qp = RawPtr_to(KQPanGesture *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QPanGesture]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QPanGesture]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QPanGesture_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQPanGesture *qp = RawPtr_to(KQPanGesture *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QPanGesture]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QPanGesture]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QPanGesture_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQPanGesture *qp = (KQPanGesture *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QPanGesture*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QPanGesture_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQPanGesture *qp = (KQPanGesture *)p->rawptr;
		KQPanGesture *qp = static_cast<KQPanGesture*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QPanGesture_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQPanGesture::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

bool KQPanGesture::event(QEvent *event)
{
	if (!dummy->eventDispatcher(event)) {
		QPanGesture::event(event);
		return false;
	}
//	QPanGesture::event(event);
	return true;
}



DEFAPI(void) defQPanGesture(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QPanGesture";
	cdef->free = QPanGesture_free;
	cdef->reftrace = QPanGesture_reftrace;
	cdef->compareTo = QPanGesture_compareTo;
}


