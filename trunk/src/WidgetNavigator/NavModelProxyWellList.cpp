#include "NavModelProxyWellList.h"

NavModelProxyWellList::NavModelProxyWellList(QObject* parent) : QSortFilterProxyModel(parent)
{
	groupID = 0;
	m_data = SharedData::Instance();
}

NavModelProxyWellList::~NavModelProxyWellList()
{
	m_data->FreeInst();
}

bool NavModelProxyWellList::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	if (!QString(m_data->wellNames.at(source_row)).contains(filterRegExp())) return false;
	if (m_data->gwfr[groupID * m_data->wellCount  + source_row] == 0) return false;
	return true;
}

