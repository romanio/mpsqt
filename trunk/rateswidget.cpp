// Test
#include "rateswidget.h"
#include "ui_rateswidget.h"

RatesWidget::RatesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RatesWidget)
{
    ui->setupUi(this);
//    m_select->Instance();
//    m_data->Instance();
 //   connect(m_data, SIGNAL(dataUpdate()), this, SLOT(updateData()));
 }

RatesWidget::~RatesWidget()
{
    delete ui;
 //   m_select->FreeInst();
 //   m_data->FreeInst();
}

void RatesWidget::updateData()
{
//    connect(m_select, SIGNAL(selectionChange()), this, SLOT(selectionChange()));
}

void RatesWidget::selectionChange()
{
    //ui->label->setText(QString::number(m_select->getWellID()));
}
