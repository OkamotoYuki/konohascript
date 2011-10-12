//QBrush QBrush.new();
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQBrush *ret_v = new KQBrush();
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}

/*
//QBrush QBrush.new(int style);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	Qt::BrushStyle style = Int_to(Qt::BrushStyle, sfp[1]);
	KQBrush *ret_v = new KQBrush(style);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QColor color, int style);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QColor  color = *RawPtr_to(const QColor *, sfp[1]);
	Qt::BrushStyle style = Int_to(Qt::BrushStyle, sfp[2]);
	KQBrush *ret_v = new KQBrush(color, style);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(int color, int style);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	Qt::GlobalColor color = Int_to(Qt::GlobalColor, sfp[1]);
	Qt::BrushStyle style = Int_to(Qt::BrushStyle, sfp[2]);
	KQBrush *ret_v = new KQBrush(color, style);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QColor color, QPixmap pixmap);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QColor  color = *RawPtr_to(const QColor *, sfp[1]);
	const QPixmap  pixmap = *RawPtr_to(const QPixmap *, sfp[2]);
	KQBrush *ret_v = new KQBrush(color, pixmap);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(int color, QPixmap pixmap);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	Qt::GlobalColor color = Int_to(Qt::GlobalColor, sfp[1]);
	const QPixmap  pixmap = *RawPtr_to(const QPixmap *, sfp[2]);
	KQBrush *ret_v = new KQBrush(color, pixmap);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QPixmap pixmap);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QPixmap  pixmap = *RawPtr_to(const QPixmap *, sfp[1]);
	KQBrush *ret_v = new KQBrush(pixmap);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QImage image);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QImage  image = *RawPtr_to(const QImage *, sfp[1]);
	KQBrush *ret_v = new KQBrush(image);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QBrush other);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QBrush  other = *RawPtr_to(const QBrush *, sfp[1]);
	KQBrush *ret_v = new KQBrush(other);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
/*
//QBrush QBrush.new(QGradient gradient);
KMETHOD QBrush_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	const QGradient  gradient = *RawPtr_to(const QGradient *, sfp[1]);
	KQBrush *ret_v = new KQBrush(gradient);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->self = rptr;
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
//QColor QBrush.getColor();
KMETHOD QBrush_getColor(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QColor ret_v = qp->color();
		QColor *ret_v_ = new QColor(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QGradient QBrush.gradient();
KMETHOD QBrush_gradient(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QGradient* ret_v = qp->gradient();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QGradient*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//boolean QBrush.isOpaque();
KMETHOD QBrush_isOpaque(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		bool ret_v = qp->isOpaque();
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//QMatrix QBrush.getMatrix();
KMETHOD QBrush_getMatrix(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QMatrix ret_v = qp->matrix();
		QMatrix *ret_v_ = new QMatrix(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//void QBrush.setColor(QColor color);
KMETHOD QBrush_setColor(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QColor  color = *RawPtr_to(const QColor *, sfp[1]);
		qp->setColor(color);
	}
	RETURNvoid_();
}

/*
//void QBrush.setColor(int color);
KMETHOD QBrush_setColor(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		Qt::GlobalColor color = Int_to(Qt::GlobalColor, sfp[1]);
		qp->setColor(color);
	}
	RETURNvoid_();
}
*/
//void QBrush.setMatrix(QMatrix matrix);
KMETHOD QBrush_setMatrix(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QMatrix  matrix = *RawPtr_to(const QMatrix *, sfp[1]);
		qp->setMatrix(matrix);
	}
	RETURNvoid_();
}

//void QBrush.setStyle(int style);
KMETHOD QBrush_setStyle(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		Qt::BrushStyle style = Int_to(Qt::BrushStyle, sfp[1]);
		qp->setStyle(style);
	}
	RETURNvoid_();
}

//void QBrush.setTexture(QPixmap pixmap);
KMETHOD QBrush_setTexture(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QPixmap  pixmap = *RawPtr_to(const QPixmap *, sfp[1]);
		qp->setTexture(pixmap);
	}
	RETURNvoid_();
}

//void QBrush.setTextureImage(QImage image);
KMETHOD QBrush_setTextureImage(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QImage  image = *RawPtr_to(const QImage *, sfp[1]);
		qp->setTextureImage(image);
	}
	RETURNvoid_();
}

//void QBrush.setTransform(QTransform matrix);
KMETHOD QBrush_setTransform(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		const QTransform  matrix = *RawPtr_to(const QTransform *, sfp[1]);
		qp->setTransform(matrix);
	}
	RETURNvoid_();
}

//int QBrush.getStyle();
KMETHOD QBrush_getStyle(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		Qt::BrushStyle ret_v = qp->style();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//QPixmap QBrush.getTexture();
KMETHOD QBrush_getTexture(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		QPixmap ret_v = qp->texture();
		QPixmap *ret_v_ = new QPixmap(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QImage QBrush.getTextureImage();
KMETHOD QBrush_getTextureImage(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		QImage ret_v = qp->textureImage();
		QImage *ret_v_ = new QImage(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QTransform QBrush.getTransform();
KMETHOD QBrush_getTransform(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QBrush *  qp = RawPtr_to(QBrush *, sfp[0]);
	if (qp != NULL) {
		QTransform ret_v = qp->transform();
		QTransform *ret_v_ = new QTransform(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}


DummyQBrush::DummyQBrush()
{
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}

void DummyQBrush::setSelf(knh_RawPtr_t *ptr)
{
	DummyQBrush::self = ptr;
}

bool DummyQBrush::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = false;
		break;
	}
	return ret;
}

bool DummyQBrush::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQBrush::event_map->bigin();
	if ((itr = DummyQBrush::event_map->find(str)) == DummyQBrush::event_map->end()) {
		bool ret;
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQBrush::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQBrush::slot_map->bigin();
	if ((itr = DummyQBrush::event_map->find(str)) == DummyQBrush::slot_map->end()) {
		bool ret;
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}


KQBrush::KQBrush() : QBrush()
{
	self = NULL;
}

KMETHOD QBrush_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQBrush *qp = RawPtr_to(KQBrush *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QBrush]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->DummyQBrush::addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QBrush]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}

KMETHOD QBrush_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQBrush *qp = RawPtr_to(KQBrush *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QBrush]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->DummyQBrush::signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QBrush]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QBrush_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (p->rawptr != NULL) {
		KQBrush *qp = (KQBrush *)p->rawptr;
		(void)qp;
		//delete qp;
	}
}
static void QBrush_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
	if (p->rawptr != NULL) {
		KQBrush *qp = (KQBrush *)p->rawptr;
		(void)qp;
	}
}

static int QBrush_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (*static_cast<QBrush*>(p1->rawptr) == *static_cast<QBrush*>(p2->rawptr) ? 0 : 1);
}

DEFAPI(void) defQBrush(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QBrush";
	cdef->free = QBrush_free;
	cdef->reftrace = QBrush_reftrace;
	cdef->compareTo = QBrush_compareTo;
}

