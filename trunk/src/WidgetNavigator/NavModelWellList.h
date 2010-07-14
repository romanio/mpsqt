#ifndef NAVMODELWELLLIST_H
#define NAVMODELWELLLIST_H

#include <QAbstractTableModel>
#include "..\SharedData\SharedData.h"

class NavModelWellList : public QAbstractTableModel
{
public:
	NavModelWellList(QObject* parent = 0);
	~NavModelWellList();
	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	void refresh();
private:
	SharedData* m_data;
};

#endif //NAVMODELWELLLIST_H
