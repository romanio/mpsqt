#ifndef WNAVIGATOR_H
#define WNAVIGATOR_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QTableView>
#include <QLineEdit>
#include <QAbstractTableModel>

#include "..\SharedData/SharedData.h"
#include "..\SharedSelector\SharedSelector.h"
#include "NavModelWellList.h"
#include "NavModelProxyWellList.h"

class WNavigator : public QDockWidget
{
	Q_OBJECT

public:
	WNavigator(QWidget *parent = 0);
	~WNavigator();
	void update();

private:
	QWidget* widgetContents;
	QVBoxLayout* verticalLayout;
	QLabel* labelWellFilter;
	QComboBox* comboGroups;
	QCheckBox* checkAllWells;
	QTableView* tableWellList;
	QLineEdit* lineFilter;
	SharedData* m_data;
        SharedSelector* m_select;
	NavModelWellList* modelWellList;
	NavModelProxyWellList* proxyWellList;
private slots:
	void selectGroup(int gID);
        void selectWell();
};

#endif // WNAVIGATOR_H
