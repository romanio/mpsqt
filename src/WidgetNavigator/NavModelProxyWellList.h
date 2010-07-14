#ifndef NAVMODELPROXYWELLLIST_H
#define NAVMODELPROXYWELLLIST_H
#include <QSortFilterProxyModel>
#include "..\SharedData\SharedData.h"

//
// Proxy for Navigator Well List
// Show wells contain group (select groupID to change)
// and filtering well names
//

class NavModelProxyWellList: public QSortFilterProxyModel
{
public:
	NavModelProxyWellList(QObject* parent = 0);
	~NavModelProxyWellList();
	int groupID;
private:
	SharedData* m_data;
protected:
	bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
};

#endif
