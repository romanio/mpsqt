#include <QFileDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QAxObject>
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataLoader\TempestLoader.h"
#include "SharedData\SharedData.h"
#include "3DView\glwidget.h"
#include "..\rateswidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionOpenNewModel, SIGNAL(triggered()), this, SLOT(openNewModel()));
	connect(ui->action3DView, SIGNAL(triggered()), this, SLOT(add3DView()));
	connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabClose(int)));

	widgetNavigator = new WNavigator(this);
	addDockWidget(Qt::LeftDockWidgetArea, widgetNavigator);
	restoreSettings();
	widgetNavigator->show();

        // need to delete

        RatesWidget* rw = new RatesWidget(ui->tabWidget);
        ui->tabWidget->addTab(rw, "Rates&Totals");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::openNewModel()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open output file", m_lastPath, "Tempest file (*.mis);;All files (*)");
	if (fileName.isEmpty()) return;

	QFileInfo finfo(fileName); 	// Save path to next open file dialog...
	m_lastPath = finfo.absolutePath();

	SharedData* sdata = SharedData::Instance();

	TempestLoader* tmpldr = new TempestLoader();
	tmpldr->openFile(fileName); 	// ..and loading data
	delete tmpldr;
	sdata->FreeInst();
	widgetNavigator->update();
}

void MainWindow::saveSettings()
{
	QString inifile = QApplication::applicationDirPath() + "/" + "mpsqt.ini";
	QSettings settings(inifile, QSettings::IniFormat);

	settings.beginGroup("MainForm");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.setValue("lastpath", m_lastPath);
	settings.setValue("state", saveState(0));
	settings.endGroup();
}

void MainWindow::restoreSettings()
{
	QString inifile = QApplication::applicationDirPath() + "/" + "mpsqt.ini";
	QSettings settings(inifile, QSettings::IniFormat);

	settings.beginGroup("MainForm");
	resize(settings.value("size", QSize(400, 280)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	m_lastPath = settings.value("lastpath", "").toString();
	restoreState(settings.value("state").toByteArray());
	settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent* e)
{
	saveSettings();
	e->accept();
}

void MainWindow::add3DView()
{
	GLWidget* gl = new GLWidget();
	ui->tabWidget->addTab(gl, "3DView");
}

bool MainWindow::tabClose(int index)
{
	ui->tabWidget->removeTab(index);
	return true;
}
