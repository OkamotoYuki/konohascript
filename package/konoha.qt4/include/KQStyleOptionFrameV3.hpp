#ifndef QSTYLEOPTIONFRAMEV3
#define QSTYLEOPTIONFRAMEV3
class DummyQStyleOptionFrameV3 : public DummyQStyleOptionFrameV2 {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQStyleOptionFrameV3();
	virtual ~DummyQStyleOptionFrameV3();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	knh_Object_t** reftrace(CTX ctx, knh_RawPtr_t *p FTRARG);
	void connection(QObject *o);
};

class KQStyleOptionFrameV3 : public QStyleOptionFrameV3 {
//	Q_OBJECT;
public:
	int magic_num;
	knh_RawPtr_t *self;
	DummyQStyleOptionFrameV3 *dummy;
	KQStyleOptionFrameV3();
	~KQStyleOptionFrameV3();
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QSTYLEOPTIONFRAMEV3


