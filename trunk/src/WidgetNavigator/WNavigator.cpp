#include "WNavigator.h"
#include <QHeaderView>

WNavigator::WNavigator(QWidget *parent) : QDockWidget(parent)
{
	setWindowTitle("Navigator");
	setObjectName("NavigatorWidget");
	setAutoFillBackground(false);
	setFeatures(QDockWidget::AllDockWidgetFeatures);

	widgetContents = new QWidget();
	verticalLayout = new QVBoxLayout(widgetContents);
	verticalLayout->setSpacing(6);
	verticalLayout->setMargin(11);

	comboGroups = new QComboBox(widgetContents);

	verticalLayout->addWidget(comboGroups);

	checkAllWells = new QCheckBox(widgetContents);
	checkAllWells->setCheckable(true);
	checkAllWells->setChecked(true);
	checkAllWells->setText("All wells in group");

	verticalLayout->addWidget(checkAllWells);

	tableWellList = new QTableView(widgetContents);
	tableWellList->setEnabled(false);
	tableWellList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWellList->setAlternatingRowColors(true);
	tableWellList->setSelectionMode(QAbstractItemView::SingleSelection);
	tableWellList->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWellList->setSortingEnabled(true);

	// Horizontal header
	tableWellList->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tableWellList->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

	// Vertical header
	tableWellList->verticalHeader()->setVisible(false);
	tableWellList->verticalHeader()->setDefaultSectionSize(18);

	modelWellList = new NavModelWellList(tableWellList);
	proxyWellList = new NavModelProxyWellList(tableWellList);

	verticalLayout->addWidget(tableWellList);

	labelWellFilter = new QLabel(widgetContents);
	labelWellFilter->setText("Well name filter");
	labelWellFilter->setEnabled(false);
	verticalLayout->addWidget(labelWellFilter);

	lineFilter = new QLineEdit(widgetContents);
	lineFilter->setEnabled(false);
	verticalLayout->addWidget(lineFilter);

	setWidget(widgetContents);

	// SIGNALS
	connect(checkAllWells, SIGNAL(toggled(bool)), tableWellList, SLOT(setDisabled(bool)));
	connect(checkAllWells, SIGNAL(toggled(bool)), labelWellFilter, SLOT(setDisabled(bool)));
	connect(checkAllWells, SIGNAL(toggled(bool)), lineFilter, SLOT(setDisabled(bool)));

	m_data = SharedData::Instance();
        m_select = SharedSelector::Instance();
}

WNavigator::~WNavigator()
{
	m_data->FreeInst();
        m_select->FreeInst();
}

void WNavigator::update()
{
	proxyWellList->setSourceModel(modelWellList);
	proxyWellList->setDynamicSortFilter(true);
	proxyWellList->setFilterKeyColumn(0);

	tableWellList->setModel(proxyWellList);
	connect(lineFilter, SIGNAL(textChanged(QString)), proxyWellList, SLOT(setFilterWildcard(QString)));

	comboGroups->clear();
	for (int ig = 0; ig < m_data->groupCount; ++ig)
		comboGroups->addItem(m_data->groupNames.at(ig));

	connect(comboGroups, SIGNAL(currentIndexChanged(int)), this, SLOT(selectGroup(int)));
        connect(tableWellList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectWell()));
//    connect(checkAllWells, SIGNAL(stateChanged(int)), this, SLOT(checkedChange()));
}

void WNavigator::selectWell()
{
    if (tableWellList->selectionModel()->selectedRows(0).count() == 0) return;
    QModelIndex item = tableWellList->selectionModel()->selectedRows(0).at(0);
    QString wname = tableWellList->model()->data(item).toString();
    int windex = m_data->wellNames.indexOf(wname);
    m_select->setWellID(windex);
}

void WNavigator::selectGroup(int gID)
{
        m_select->setGroupID(gID);
	proxyWellList->groupID = gID;
	modelWellList->refresh();
}
