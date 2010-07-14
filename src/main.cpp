#include <QtGui/QApplication>
#include "SharedData/SharedData.h"
#include "SharedSelector/SharedSelector.h"

#include "mainwindow.h"
#include <QPlastiqueStyle>

int main(int argc, char *argv[])
{
	QApplication::setStyle(new QPlastiqueStyle);
	// Create singleton
        SharedData* sharedData = SharedData::Instance();
        SharedSelector* sharedSelector = SharedSelector::Instance();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	a.exec();

        // Delete singletons
	sharedData->FreeInst();
        sharedSelector->FreeInst();
	return 0;
}
