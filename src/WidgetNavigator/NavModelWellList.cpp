#include "NavModelWellList.h"

NavModelWellList::NavModelWellList(QObject* parent) : QAbstractTableModel(parent)
{
	m_data = SharedData::Instance();
}

NavModelWellList::~NavModelWellList()
{
	m_data->FreeInst();
}

void NavModelWellList::refresh()
{
	emit layoutChanged();
}

QVariant NavModelWellList::data(const QModelIndex& index, int role) const
{
	// If column is "Wellname" return wellname.
	// If column is "Status" return one of four state:
	// 1. Oil production total at last day > 0, status is "Production well"
	// 2. Water injection total at last day > 0, status is "Injection well"
	// 3. Oil prod. total and water inj. total > 0, status is "Production + Injection well"
	// 4. Oil prod. total and water inj. total = 0, status is "Not active well"

	if (!index.isValid()) return QVariant();

	QVariant value;
	if (index.column() == 0) value = QVariant(m_data->wellNames.at(index.row())); // Well name
	if (index.column() == 1)
	{
		value = "---";
		if (m_data->opt[(m_data->daysCount - 1) * m_data ->wellCount + index.row()] > 0)  value = "PROD";
		if (m_data->wit[(m_data->daysCount - 1) * m_data->wellCount + index.row()] > 0)  value = "INJE";
		if (m_data->opt[(m_data->daysCount - 1) * m_data->wellCount + index.row()] > 0 &&
		        m_data->wit[(m_data->daysCount - 1) * m_data->wellCount + index.row()] > 0) value = "PROD+INJE";
	}
	return (role == Qt::DisplayRole)?value : QVariant();
}

int NavModelWellList::rowCount(const QModelIndex& parent) const //
{
	if (!m_data->isAllocated) return 0;
	return m_data->wellCount;
}

int NavModelWellList::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant NavModelWellList::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole) return QVariant();

	QVariant value;

	if (section == 0) value = QVariant("Name");
	if (section == 1) value = QVariant("Status");

	return (orientation == Qt::Vertical)?QString():value;
}
