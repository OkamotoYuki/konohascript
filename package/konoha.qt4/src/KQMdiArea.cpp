//@Virtual @Override QSize QMdiArea.minimumSizeHint();
KMETHOD QMdiArea_minimumSizeHint(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QSize ret_v = qp->minimumSizeHint();
		QSize *ret_v_ = new QSize(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override QSize QMdiArea.sizeHint();
KMETHOD QMdiArea_sizeHint(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QSize ret_v = qp->sizeHint();
		QSize *ret_v_ = new QSize(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QMdiArea QMdiArea.new(QWidget parent);
KMETHOD QMdiArea_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QWidget*  parent = RawPtr_to(QWidget*, sfp[1]);
	KQMdiArea *ret_v = new KQMdiArea(parent);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}

//int QMdiArea.getActivationOrder();
KMETHOD QMdiArea_getActivationOrder(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::WindowOrder ret_v = qp->activationOrder();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//QMdiSubWindow QMdiArea.getActiveSubWindow();
KMETHOD QMdiArea_getActiveSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiSubWindow* ret_v = qp->activeSubWindow();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QMdiSubWindow*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QMdiSubWindow QMdiArea.addSubWindow(QWidget widget, int windowFlags);
KMETHOD QMdiArea_addSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QWidget*  widget = RawPtr_to(QWidget*, sfp[1]);
		Qt::WindowFlags windowFlags = Int_to(Qt::WindowFlags, sfp[2]);
		QMdiSubWindow* ret_v = qp->addSubWindow(widget, windowFlags);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QMdiSubWindow*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QBrush QMdiArea.getBackground();
KMETHOD QMdiArea_getBackground(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QBrush ret_v = qp->background();
		QBrush *ret_v_ = new QBrush(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QMdiSubWindow QMdiArea.currentSubWindow();
KMETHOD QMdiArea_currentSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiSubWindow* ret_v = qp->currentSubWindow();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QMdiSubWindow*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//boolean QMdiArea.getDocumentMode();
KMETHOD QMdiArea_getDocumentMode(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		bool ret_v = qp->documentMode();
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//void QMdiArea.removeSubWindow(QWidget widget);
KMETHOD QMdiArea_removeSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QWidget*  widget = RawPtr_to(QWidget*, sfp[1]);
		qp->removeSubWindow(widget);
	}
	RETURNvoid_();
}

//void QMdiArea.setActivationOrder(int order);
KMETHOD QMdiArea_setActivationOrder(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::WindowOrder order = Int_to(QMdiArea::WindowOrder, sfp[1]);
		qp->setActivationOrder(order);
	}
	RETURNvoid_();
}

//void QMdiArea.setBackground(QBrush background);
KMETHOD QMdiArea_setBackground(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		const QBrush  background = *RawPtr_to(const QBrush *, sfp[1]);
		qp->setBackground(background);
	}
	RETURNvoid_();
}

//void QMdiArea.setDocumentMode(boolean enabled);
KMETHOD QMdiArea_setDocumentMode(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		bool enabled = Boolean_to(bool, sfp[1]);
		qp->setDocumentMode(enabled);
	}
	RETURNvoid_();
}

//void QMdiArea.setOption(int option, boolean on);
KMETHOD QMdiArea_setOption(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::AreaOption option = Int_to(QMdiArea::AreaOption, sfp[1]);
		bool on = Boolean_to(bool, sfp[2]);
		qp->setOption(option, on);
	}
	RETURNvoid_();
}

//void QMdiArea.setTabPosition(int position);
KMETHOD QMdiArea_setTabPosition(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QTabWidget::TabPosition position = Int_to(QTabWidget::TabPosition, sfp[1]);
		qp->setTabPosition(position);
	}
	RETURNvoid_();
}

//void QMdiArea.setTabShape(int shape);
KMETHOD QMdiArea_setTabShape(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QTabWidget::TabShape shape = Int_to(QTabWidget::TabShape, sfp[1]);
		qp->setTabShape(shape);
	}
	RETURNvoid_();
}

//void QMdiArea.setViewMode(int mode);
KMETHOD QMdiArea_setViewMode(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::ViewMode mode = Int_to(QMdiArea::ViewMode, sfp[1]);
		qp->setViewMode(mode);
	}
	RETURNvoid_();
}

//Array<QMdiSubWindow> QMdiArea.subWindowList(int order);
KMETHOD QMdiArea_subWindowList(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::WindowOrder order = Int_to(QMdiArea::WindowOrder, sfp[1]);
		QList<QMdiSubWindow*>ret_v = qp->subWindowList(order);
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QMdiSubWindow"));
		for (int n = 0; n < list_size; n++) {
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v[n]);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//int QMdiArea.getTabPosition();
KMETHOD QMdiArea_getTabPosition(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QTabWidget::TabPosition ret_v = qp->tabPosition();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//int QMdiArea.getTabShape();
KMETHOD QMdiArea_getTabShape(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QTabWidget::TabShape ret_v = qp->tabShape();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//boolean QMdiArea.testOption(int option);
KMETHOD QMdiArea_testOption(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::AreaOption option = Int_to(QMdiArea::AreaOption, sfp[1]);
		bool ret_v = qp->testOption(option);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//int QMdiArea.getViewMode();
KMETHOD QMdiArea_getViewMode(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiArea::ViewMode ret_v = qp->viewMode();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//void QMdiArea.activateNextSubWindow();
KMETHOD QMdiArea_activateNextSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->activateNextSubWindow();
	}
	RETURNvoid_();
}

//void QMdiArea.activatePreviousSubWindow();
KMETHOD QMdiArea_activatePreviousSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->activatePreviousSubWindow();
	}
	RETURNvoid_();
}

//void QMdiArea.cascadeSubWindows();
KMETHOD QMdiArea_cascadeSubWindows(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->cascadeSubWindows();
	}
	RETURNvoid_();
}

//void QMdiArea.closeActiveSubWindow();
KMETHOD QMdiArea_closeActiveSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->closeActiveSubWindow();
	}
	RETURNvoid_();
}

//void QMdiArea.closeAllSubWindows();
KMETHOD QMdiArea_closeAllSubWindows(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->closeAllSubWindows();
	}
	RETURNvoid_();
}

//void QMdiArea.setActiveSubWindow(QMdiSubWindow window);
KMETHOD QMdiArea_setActiveSubWindow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		QMdiSubWindow*  window = RawPtr_to(QMdiSubWindow*, sfp[1]);
		qp->setActiveSubWindow(window);
	}
	RETURNvoid_();
}

//void QMdiArea.tileSubWindows();
KMETHOD QMdiArea_tileSubWindows(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMdiArea *  qp = RawPtr_to(QMdiArea *, sfp[0]);
	if (qp != NULL) {
		qp->tileSubWindows();
	}
	RETURNvoid_();
}


DummyQMdiArea::DummyQMdiArea()
{
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}

void DummyQMdiArea::setSelf(knh_RawPtr_t *ptr)
{
	DummyQMdiArea::self = ptr;
	DummyQAbstractScrollArea::setSelf(ptr);
}

bool DummyQMdiArea::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQAbstractScrollArea::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQMdiArea::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQMdiArea::event_map->bigin();
	if ((itr = DummyQMdiArea::event_map->find(str)) == DummyQMdiArea::event_map->end()) {
		bool ret;
		ret = DummyQAbstractScrollArea::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQMdiArea::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQMdiArea::slot_map->bigin();
	if ((itr = DummyQMdiArea::event_map->find(str)) == DummyQMdiArea::slot_map->end()) {
		bool ret;
		ret = DummyQAbstractScrollArea::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}


KQMdiArea::KQMdiArea(QWidget* parent) : QMdiArea(parent)
{
	self = NULL;
}

KMETHOD QMdiArea_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQMdiArea *qp = RawPtr_to(KQMdiArea *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QMdiArea]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->DummyQMdiArea::addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QMdiArea]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}

KMETHOD QMdiArea_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQMdiArea *qp = RawPtr_to(KQMdiArea *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QMdiArea]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->DummyQMdiArea::signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QMdiArea]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QMdiArea_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (p->rawptr != NULL) {
		KQMdiArea *qp = (KQMdiArea *)p->rawptr;
		(void)qp;
		//delete qp;
	}
}
static void QMdiArea_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
	if (p->rawptr != NULL) {
		KQMdiArea *qp = (KQMdiArea *)p->rawptr;
		(void)qp;
	}
}

static int QMdiArea_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

bool KQMdiArea::event(QEvent *event)
{
	if (!DummyQMdiArea::eventDispatcher(event)) {
		QMdiArea::event(event);
		return false;
	}
	return true;
}

DEFAPI(void) defQMdiArea(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QMdiArea";
	cdef->free = QMdiArea_free;
	cdef->reftrace = QMdiArea_reftrace;
	cdef->compareTo = QMdiArea_compareTo;
}

static knh_IntData_t QMdiAreaConstInt[] = {
	{"DontMaximizeSubWindowOnActivation", QMdiArea::DontMaximizeSubWindowOnActivation},
	{"SubWindowView", QMdiArea::SubWindowView},
	{"TabbedView", QMdiArea::TabbedView},
	{"CreationOrder", QMdiArea::CreationOrder},
	{"StackingOrder", QMdiArea::StackingOrder},
	{"ActivationHistoryOrder", QMdiArea::ActivationHistoryOrder},
	{NULL, 0}
};

DEFAPI(void) constQMdiArea(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi) {
	kapi->loadClassIntConst(ctx, cid, QMdiAreaConstInt);
}
