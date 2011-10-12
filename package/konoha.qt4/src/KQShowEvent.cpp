//QShowEvent QShowEvent.new();
KMETHOD QShowEvent_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQShowEvent *ret_v = new KQShowEvent();
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}


DummyQShowEvent::DummyQShowEvent()
{
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}

void DummyQShowEvent::setSelf(knh_RawPtr_t *ptr)
{
	DummyQShowEvent::self = ptr;
	DummyQEvent::setSelf(ptr);
}

bool DummyQShowEvent::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQEvent::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQShowEvent::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQShowEvent::event_map->bigin();
	if ((itr = DummyQShowEvent::event_map->find(str)) == DummyQShowEvent::event_map->end()) {
		bool ret;
		ret = DummyQEvent::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQShowEvent::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQShowEvent::slot_map->bigin();
	if ((itr = DummyQShowEvent::event_map->find(str)) == DummyQShowEvent::slot_map->end()) {
		bool ret;
		ret = DummyQEvent::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}


KQShowEvent::KQShowEvent() : QShowEvent()
{
	self = NULL;
}

KMETHOD QShowEvent_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQShowEvent *qp = RawPtr_to(KQShowEvent *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QShowEvent]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->DummyQShowEvent::addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QShowEvent]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}

KMETHOD QShowEvent_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQShowEvent *qp = RawPtr_to(KQShowEvent *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QShowEvent]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->DummyQShowEvent::signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QShowEvent]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QShowEvent_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (p->rawptr != NULL) {
		KQShowEvent *qp = (KQShowEvent *)p->rawptr;
		(void)qp;
		//delete qp;
	}
}
static void QShowEvent_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
	if (p->rawptr != NULL) {
		KQShowEvent *qp = (KQShowEvent *)p->rawptr;
		(void)qp;
	}
}

static int QShowEvent_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

DEFAPI(void) defQShowEvent(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QShowEvent";
	cdef->free = QShowEvent_free;
	cdef->reftrace = QShowEvent_reftrace;
	cdef->compareTo = QShowEvent_compareTo;
}

