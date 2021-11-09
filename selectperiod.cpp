#include "selectperiod.h"
#include "ui_selectperiod.h"
#include <QDebug>
SelectPeriod::SelectPeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPeriod)
{
    if (!m_period) m_period = new QPair<QDateTime,QDateTime>;

    ui->setupUi(this);
    show();
    qDebug() << m_listName.size();
    emit si_askGetListName();
    setList();
}

void SelectPeriod::setList(){
    qDebug() << m_listName.size();
    for (int i = 0; i < m_listName.size(); i++){
        qDebug() << "VALUE " << m_listName.at(i);
        ui->listWidget->addItem(m_listName.at(i));
    }
}

SelectPeriod::~SelectPeriod()
{
    delete m_period;
    delete ui;
}

void SelectPeriod::on_buttonBox_accepted()
{
    //    m_period->first = ui->dateTimeEdit->dateTime();
    //    m_period->second = ui->dateTimeEdit_2->dateTime();
    qDebug() << "date" << m_period->first << m_period->second;


    emit si_closeSelectPeriod(m_period->first.toString(Qt::SystemLocaleShortDate),m_period->second.toString(Qt::SystemLocaleShortDate));
}

void SelectPeriod::on_buttonBox_rejected()
{
    emit si_closeSelectPeriod(" "," ");
}


void SelectPeriod::on_pushButton_clicked()
{
    setList();
}

