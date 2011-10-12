#ifndef QMESSAGEBOX
#define QMESSAGEBOX
class DummyQMessageBox : public DummyQDialog {
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQMessageBox();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
};

class KQMessageBox : public QMessageBox, public DummyQMessageBox {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	KQMessageBox(QWidget* parent);
	bool event(QEvent *event);
};

#endif //QMESSAGEBOX

