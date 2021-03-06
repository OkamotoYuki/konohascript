//@Virtual @Override int QStandardItemModel.getColumnCount(QModelIndex parent);
KMETHOD QStandardItemModel_getColumnCount(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[1]);
		int ret_v = qp->columnCount(parent);
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//@Virtual @Override QVariant QStandardItemModel.getData(QModelIndex index, int role);
KMETHOD QStandardItemModel_getData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  index = *RawPtr_to(const QModelIndex *, sfp[1]);
		int role = Int_to(int, sfp[2]);
		QVariant ret_v = qp->data(index, role);
		QVariant *ret_v_ = new QVariant(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override boolean QStandardItemModel.dropMimeData(QMimeData data, int action, int row, int column, QModelIndex parent);
KMETHOD QStandardItemModel_dropMimeData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QMimeData*  data = RawPtr_to(const QMimeData*, sfp[1]);
		Qt::DropAction action = Int_to(Qt::DropAction, sfp[2]);
		int row = Int_to(int, sfp[3]);
		int column = Int_to(int, sfp[4]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[5]);
		bool ret_v = qp->dropMimeData(data, action, row, column, parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override QtItemFlags QStandardItemModel.flags(QModelIndex index);
KMETHOD QStandardItemModel_flags(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  index = *RawPtr_to(const QModelIndex *, sfp[1]);
		Qt::ItemFlags ret_v = qp->flags(index);
		Qt::ItemFlags *ret_v_ = new Qt::ItemFlags(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override boolean QStandardItemModel.hasChildren(QModelIndex parent);
KMETHOD QStandardItemModel_hasChildren(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[1]);
		bool ret_v = qp->hasChildren(parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override QVariant QStandardItemModel.getHeaderData(int section, int orientation, int role);
KMETHOD QStandardItemModel_getHeaderData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int section = Int_to(int, sfp[1]);
		Qt::Orientation orientation = Int_to(Qt::Orientation, sfp[2]);
		int role = Int_to(int, sfp[3]);
		QVariant ret_v = qp->headerData(section, orientation, role);
		QVariant *ret_v_ = new QVariant(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override QModelIndex QStandardItemModel.index(int row, int column, QModelIndex parent);
KMETHOD QStandardItemModel_index(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int column = Int_to(int, sfp[2]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[3]);
		QModelIndex ret_v = qp->index(row, column, parent);
		QModelIndex *ret_v_ = new QModelIndex(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override boolean QStandardItemModel.insertColumns(int column, int count, QModelIndex parent);
KMETHOD QStandardItemModel_insertColumns(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		int count = Int_to(int, sfp[2]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[3]);
		bool ret_v = qp->insertColumns(column, count, parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override boolean QStandardItemModel.insertRows(int row, int count, QModelIndex parent);
KMETHOD QStandardItemModel_insertRows(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int count = Int_to(int, sfp[2]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[3]);
		bool ret_v = qp->insertRows(row, count, parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override QMimeData QStandardItemModel.mimeData(QModelIndexList indexes);
KMETHOD QStandardItemModel_mimeData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndexList  indexes = *RawPtr_to(const QModelIndexList *, sfp[1]);
		QMimeData* ret_v = qp->mimeData(indexes);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QMimeData*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override QModelIndex QStandardItemModel.parent(QModelIndex child);
KMETHOD QStandardItemModel_parent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  child = *RawPtr_to(const QModelIndex *, sfp[1]);
		QModelIndex ret_v = qp->parent(child);
		QModelIndex *ret_v_ = new QModelIndex(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override boolean QStandardItemModel.removeColumns(int column, int count, QModelIndex parent);
KMETHOD QStandardItemModel_removeColumns(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		int count = Int_to(int, sfp[2]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[3]);
		bool ret_v = qp->removeColumns(column, count, parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override boolean QStandardItemModel.removeRows(int row, int count, QModelIndex parent);
KMETHOD QStandardItemModel_removeRows(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int count = Int_to(int, sfp[2]);
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[3]);
		bool ret_v = qp->removeRows(row, count, parent);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override int QStandardItemModel.getRowCount(QModelIndex parent);
KMETHOD QStandardItemModel_getRowCount(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  parent = *RawPtr_to(const QModelIndex *, sfp[1]);
		int ret_v = qp->rowCount(parent);
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//@Virtual @Override boolean QStandardItemModel.setData(QModelIndex index, QVariant value, int role);
KMETHOD QStandardItemModel_setData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  index = *RawPtr_to(const QModelIndex *, sfp[1]);
		const QVariant  value = *RawPtr_to(const QVariant *, sfp[2]);
		int role = Int_to(int, sfp[3]);
		bool ret_v = qp->setData(index, value, role);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override boolean QStandardItemModel.setHeaderData(int section, int orientation, QVariant value, int role);
KMETHOD QStandardItemModel_setHeaderData(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int section = Int_to(int, sfp[1]);
		Qt::Orientation orientation = Int_to(Qt::Orientation, sfp[2]);
		const QVariant  value = *RawPtr_to(const QVariant *, sfp[3]);
		int role = Int_to(int, sfp[4]);
		bool ret_v = qp->setHeaderData(section, orientation, value, role);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//@Virtual @Override void QStandardItemModel.sort(int column, int order);
KMETHOD QStandardItemModel_sort(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		Qt::SortOrder order = Int_to(Qt::SortOrder, sfp[2]);
		qp->sort(column, order);
	}
	RETURNvoid_();
}

//@Virtual @Override QtDropActions QStandardItemModel.supportedDropActions();
KMETHOD QStandardItemModel_supportedDropActions(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		Qt::DropActions ret_v = qp->supportedDropActions();
		Qt::DropActions *ret_v_ = new Qt::DropActions(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItemModel QStandardItemModel.new(QObject parent);
KMETHOD QStandardItemModel_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QObject*  parent = RawPtr_to(QObject*, sfp[1]);
	KQStandardItemModel *ret_v = new KQStandardItemModel(parent);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}

/*
//QStandardItemModel QStandardItemModel.new(int rows, int columns, QObject parent);
KMETHOD QStandardItemModel_new(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	int rows = Int_to(int, sfp[1]);
	int columns = Int_to(int, sfp[2]);
	QObject*  parent = RawPtr_to(QObject*, sfp[3]);
	KQStandardItemModel *ret_v = new KQStandardItemModel(rows, columns, parent);
	knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v, NULL);
	ret_v->setSelf(rptr);
	RETURN_(rptr);
}
*/
//void QStandardItemModel.appendColumn(Array<QStandardItem> items);
KMETHOD QStandardItemModel_appendColumn(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		knh_Array_t *a = sfp[1].a;
		int asize = knh_Array_size(a);
		QList<QStandardItem*> items;
		for (int n = 0; n < asize; n++) {
			knh_RawPtr_t *p = (knh_RawPtr_t*)(a->list[n]);
			items.append((QStandardItem*)p->rawptr);
		}
		qp->appendColumn(items);
	}
	RETURNvoid_();
}

//void QStandardItemModel.appendRow(Array<QStandardItem> items);
KMETHOD QStandardItemModel_appendRow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		knh_Array_t *a = sfp[1].a;
		int asize = knh_Array_size(a);
		QList<QStandardItem*> items;
		for (int n = 0; n < asize; n++) {
			knh_RawPtr_t *p = (knh_RawPtr_t*)(a->list[n]);
			items.append((QStandardItem*)p->rawptr);
		}
		qp->appendRow(items);
	}
	RETURNvoid_();
}

/*
//void QStandardItemModel.appendRow(QStandardItem item);
KMETHOD QStandardItemModel_appendRow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		QStandardItem*  item = RawPtr_to(QStandardItem*, sfp[1]);
		qp->appendRow(item);
	}
	RETURNvoid_();
}
*/
//void QStandardItemModel.clear();
KMETHOD QStandardItemModel_clear(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		qp->clear();
	}
	RETURNvoid_();
}

//Array<QStandardItem> QStandardItemModel.findItems(String text, QtMatchFlags flags, int column);
KMETHOD QStandardItemModel_findItems(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QString text = String_to(const QString, sfp[1]);
		initFlag(flags, Qt::MatchFlags, sfp[2]);
		int column = Int_to(int, sfp[3]);
		QList<QStandardItem*> ret_v = qp->findItems(text, flags, column);
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QStandardItem"));
		for (int n = 0; n < list_size; n++) {
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v[n]);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//QStandardItem QStandardItemModel.getHorizontalHeaderItem(int column);
KMETHOD QStandardItemModel_getHorizontalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		QStandardItem* ret_v = qp->horizontalHeaderItem(column);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QModelIndex QStandardItemModel.indexFromItem(QStandardItem item);
KMETHOD QStandardItemModel_indexFromItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QStandardItem*  item = RawPtr_to(const QStandardItem*, sfp[1]);
		QModelIndex ret_v = qp->indexFromItem(item);
		QModelIndex *ret_v_ = new QModelIndex(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.invisibleRootItem();
KMETHOD QStandardItemModel_invisibleRootItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		QStandardItem* ret_v = qp->invisibleRootItem();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.getItem(int row, int column);
KMETHOD QStandardItemModel_getItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int column = Int_to(int, sfp[2]);
		QStandardItem* ret_v = qp->item(row, column);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.itemFromIndex(QModelIndex index);
KMETHOD QStandardItemModel_itemFromIndex(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QModelIndex  index = *RawPtr_to(const QModelIndex *, sfp[1]);
		QStandardItem* ret_v = qp->itemFromIndex(index);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.getItemPrototype();
KMETHOD QStandardItemModel_getItemPrototype(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QStandardItem* ret_v = qp->itemPrototype();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//void QStandardItemModel.setColumnCount(int columns);
KMETHOD QStandardItemModel_setColumnCount(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int columns = Int_to(int, sfp[1]);
		qp->setColumnCount(columns);
	}
	RETURNvoid_();
}

//void QStandardItemModel.setHorizontalHeaderItem(int column, QStandardItem item);
KMETHOD QStandardItemModel_setHorizontalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		QStandardItem*  item = RawPtr_to(QStandardItem*, sfp[2]);
		qp->setHorizontalHeaderItem(column, item);
	}
	RETURNvoid_();
}

//void QStandardItemModel.setItem(int row, int column, QStandardItem item);
KMETHOD QStandardItemModel_setItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int column = Int_to(int, sfp[2]);
		QStandardItem*  item = RawPtr_to(QStandardItem*, sfp[3]);
		qp->setItem(row, column, item);
	}
	RETURNvoid_();
}

/*
//void QStandardItemModel.setItem(int row, QStandardItem item);
KMETHOD QStandardItemModel_setItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		QStandardItem*  item = RawPtr_to(QStandardItem*, sfp[2]);
		qp->setItem(row, item);
	}
	RETURNvoid_();
}
*/
//void QStandardItemModel.setItemPrototype(QStandardItem item);
KMETHOD QStandardItemModel_setItemPrototype(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		const QStandardItem*  item = RawPtr_to(const QStandardItem*, sfp[1]);
		qp->setItemPrototype(item);
	}
	RETURNvoid_();
}

//void QStandardItemModel.setRowCount(int rows);
KMETHOD QStandardItemModel_setRowCount(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int rows = Int_to(int, sfp[1]);
		qp->setRowCount(rows);
	}
	RETURNvoid_();
}

//void QStandardItemModel.setSortRole(int role);
KMETHOD QStandardItemModel_setSortRole(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int role = Int_to(int, sfp[1]);
		qp->setSortRole(role);
	}
	RETURNvoid_();
}

//void QStandardItemModel.setVerticalHeaderItem(int row, QStandardItem item);
KMETHOD QStandardItemModel_setVerticalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		QStandardItem*  item = RawPtr_to(QStandardItem*, sfp[2]);
		qp->setVerticalHeaderItem(row, item);
	}
	RETURNvoid_();
}

//int QStandardItemModel.getSortRole();
KMETHOD QStandardItemModel_getSortRole(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int ret_v = qp->sortRole();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//Array<QStandardItem> QStandardItemModel.takeColumn(int column);
KMETHOD QStandardItemModel_takeColumn(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		QList<QStandardItem*> ret_v = qp->takeColumn(column);
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QStandardItem"));
		for (int n = 0; n < list_size; n++) {
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v[n]);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//QStandardItem QStandardItemModel.takeHorizontalHeaderItem(int column);
KMETHOD QStandardItemModel_takeHorizontalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int column = Int_to(int, sfp[1]);
		QStandardItem* ret_v = qp->takeHorizontalHeaderItem(column);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.takeItem(int row, int column);
KMETHOD QStandardItemModel_takeItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		int column = Int_to(int, sfp[2]);
		QStandardItem* ret_v = qp->takeItem(row, column);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//Array<QStandardItem> QStandardItemModel.takeRow(int row);
KMETHOD QStandardItemModel_takeRow(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		QList<QStandardItem*> ret_v = qp->takeRow(row);
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QStandardItem"));
		for (int n = 0; n < list_size; n++) {
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v[n]);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//QStandardItem QStandardItemModel.takeVerticalHeaderItem(int row);
KMETHOD QStandardItemModel_takeVerticalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		QStandardItem* ret_v = qp->takeVerticalHeaderItem(row);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QStandardItem QStandardItemModel.getVerticalHeaderItem(int row);
KMETHOD QStandardItemModel_getVerticalHeaderItem(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QStandardItemModel *  qp = RawPtr_to(QStandardItemModel *, sfp[0]);
	if (qp) {
		int row = Int_to(int, sfp[1]);
		QStandardItem* ret_v = qp->verticalHeaderItem(row);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QStandardItem*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}


DummyQStandardItemModel::DummyQStandardItemModel()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	item_changed_func = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
	slot_map->insert(map<string, knh_Func_t *>::value_type("item-changed", NULL));
}
DummyQStandardItemModel::~DummyQStandardItemModel()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQStandardItemModel::setSelf(knh_RawPtr_t *ptr)
{
	DummyQStandardItemModel::self = ptr;
	DummyQAbstractItemModel::setSelf(ptr);
}

bool DummyQStandardItemModel::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQAbstractItemModel::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQStandardItemModel::itemChangedSlot(QStandardItem* item)
{
	if (item_changed_func != NULL) {
		CTX lctx = knh_getCurrentContext();
		knh_sfp_t *lsfp = lctx->esp;
		KNH_SETv(lctx, lsfp[K_CALLDELTA+1].o, UPCAST(self));
		knh_RawPtr_t *p1 = new_QRawPtr(lctx, QStandardItem, item);
		KNH_SETv(lctx, lsfp[K_CALLDELTA+2].o, UPCAST(p1));
		knh_Func_invoke(lctx, item_changed_func, lsfp, 2);
		return true;
	}
	return false;
}

bool DummyQStandardItemModel::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQStandardItemModel::event_map->bigin();
	if ((itr = DummyQStandardItemModel::event_map->find(str)) == DummyQStandardItemModel::event_map->end()) {
		bool ret = false;
		ret = DummyQAbstractItemModel::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQStandardItemModel::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQStandardItemModel::slot_map->bigin();
	if ((itr = DummyQStandardItemModel::slot_map->find(str)) == DummyQStandardItemModel::slot_map->end()) {
		bool ret = false;
		ret = DummyQAbstractItemModel::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		item_changed_func = (*slot_map)["item-changed"];
		return true;
	}
}

knh_Object_t** DummyQStandardItemModel::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
//	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQStandardItemModel::reftrace p->rawptr=[%p]\n", p->rawptr);

	int list_size = 2;
	KNH_ENSUREREF(ctx, list_size);

	KNH_ADDNNREF(ctx, item_changed_func);

	KNH_SIZEREF(ctx);

	tail_ = DummyQAbstractItemModel::reftrace(ctx, p, tail_);

	return tail_;
}

void DummyQStandardItemModel::connection(QObject *o)
{
	QStandardItemModel *p = dynamic_cast<QStandardItemModel*>(o);
	if (p != NULL) {
		connect(p, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(itemChangedSlot(QStandardItem*)));
	}
	DummyQAbstractItemModel::connection(o);
}

KQStandardItemModel::KQStandardItemModel(QObject* parent) : QStandardItemModel(parent)
{
	magic_num = G_MAGIC_NUM;
	self = NULL;
	dummy = new DummyQStandardItemModel();
	dummy->connection((QObject*)this);
}

KQStandardItemModel::~KQStandardItemModel()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QStandardItemModel_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQStandardItemModel *qp = RawPtr_to(KQStandardItemModel *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QStandardItemModel]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QStandardItemModel]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QStandardItemModel_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQStandardItemModel *qp = RawPtr_to(KQStandardItemModel *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QStandardItemModel]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QStandardItemModel]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QStandardItemModel_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQStandardItemModel *qp = (KQStandardItemModel *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QStandardItemModel*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QStandardItemModel_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQStandardItemModel *qp = (KQStandardItemModel *)p->rawptr;
		KQStandardItemModel *qp = static_cast<KQStandardItemModel*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QStandardItemModel_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQStandardItemModel::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

bool KQStandardItemModel::event(QEvent *event)
{
	if (!dummy->eventDispatcher(event)) {
		QStandardItemModel::event(event);
		return false;
	}
//	QStandardItemModel::event(event);
	return true;
}



DEFAPI(void) defQStandardItemModel(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QStandardItemModel";
	cdef->free = QStandardItemModel_free;
	cdef->reftrace = QStandardItemModel_reftrace;
	cdef->compareTo = QStandardItemModel_compareTo;
}


