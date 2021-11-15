#include "selectperiod.h"
#include "ui_selectperiod.h"
#include <QDebug>
SelectPeriod::SelectPeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPeriod)
{
    ui->setupUi(this);
    show();
    setList();
}

void SelectPeriod::setList(){
    qDebug() << m_timePeriod.size();
    for (int i = 0; i < m_timePeriod.size(); i++){
       // qDebug() << "VALUE " << m_timePeriod.at(i);
        ui->listWidget->addItem(i + ' ' + m_timePeriod.at(i));
        ui->listWidget_2->addItem(i + ' ' + m_timePeriod.at(i));
    }
}



SelectPeriod::~SelectPeriod()
{
    delete ui;
}

void SelectPeriod::on_buttonBox_accepted()
{
    //    m_period->first = ui->dateTimeEdit->dateTime();
    qDebug() << "DEBUG";
    //    m_period->second = ui->dateTimeEdit_2->dateTime();

}

void SelectPeriod::on_buttonBox_rejected()
{
    emit si_closeSelectPeriod(" "," ");
}


void SelectPeriod::on_pushButton_clicked()
{
    setList();
}


void SelectPeriod::on_listWidget_itemActivated(QListWidgetItem *item)
{
    QModelIndex index = ui->listWidget->currentIndex();
    emit si_setStartPeriod(index.data(Qt::DisplayRole).toString());
}


void SelectPeriod::on_listWidget_2_itemActivated(QListWidgetItem *item)
{
    QModelIndex index = ui->listWidget->currentIndex();
    emit si_setEndPeriod(index.data(Qt::DisplayRole).toString());
}

