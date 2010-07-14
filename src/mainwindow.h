#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WidgetNavigator/WNavigator.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent* e);

private:
	void saveSettings();
	void restoreSettings();

	Ui::MainWindow *ui;
	QString m_lastPath;
	WNavigator* widgetNavigator;
private slots:
	void openNewModel();
	void add3DView();
	bool tabClose(int index);
};

#endif // MAINWINDOW_H
