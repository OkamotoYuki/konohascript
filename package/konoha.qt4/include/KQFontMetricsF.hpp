#ifndef QFONTMETRICSF
#define QFONTMETRICSF
class DummyQFontMetricsF {
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQFontMetricsF();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
};

class KQFontMetricsF : public QFontMetricsF, public DummyQFontMetricsF {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	KQFontMetricsF(const QFont font);
};

#endif //QFONTMETRICSF

