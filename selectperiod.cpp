#include "selectperiod.h"
#include "ui_selectperiod.h"
#include <QDebug>
SelectPeriod::SelectPeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPeriod)
{
    if (!m_period) m_period = new QPair<QDateTime,QDateTime>;

    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    show();
}

SelectPeriod::~SelectPeriod()
{
    delete m_period;
    delete ui;
}

void SelectPeriod::on_buttonBox_accepted()
{
    m_period->first = ui->dateTimeEdit->dateTime();
    m_period->second = ui->dateTimeEdit_2->dateTime();
    qDebug() << "date" << m_period->first << m_period->second;

    emit si_closeSelectPeriod(m_period->first.toString(Qt::SystemLocaleShortDate),m_period->second.toString(Qt::SystemLocaleShortDate));
}

void SelectPeriod::on_buttonBox_rejected()
{
    emit si_closeSelectPeriod(" "," ");
}
