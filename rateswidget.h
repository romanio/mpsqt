#ifndef RATESWIDGET_H
#define RATESWIDGET_H

#include <QWidget>
//#include "/src/SharedSelector/SharedSelector.h"

//#include "../src/SharedSelector/SharedSelector.h"
//#include "../src/SharedData/SharedData.h"

namespace Ui {
    class RatesWidget;
}

class RatesWidget : public QWidget {
    Q_OBJECT
public:
    RatesWidget(QWidget *parent = 0);
    ~RatesWidget();

private:
    Ui::RatesWidget *ui;
 //   SharedSelector* m_select;
 //   SharedData* m_data;
private slots:
    void updateData();
    void selectionChange();
};

#endif // RATESWIDGET_H
