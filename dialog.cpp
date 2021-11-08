#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    csvFile = new CSVFile;

    connect(csvFile, SIGNAL(si_newValue(QString, QString, int, int)), this, SLOT(sl_onNewValue(QString, QString, int, int)));
    connect(csvFile, SIGNAL(si_setNbrCol(int)), this, SLOT(sl_onSetNbrCol(int)));
    connect(csvFile, SIGNAL(si_setNbrRow(int)), this, SLOT(sl_onSetNbrRow(int)));
    connect(csvFile, SIGNAL(si_setNameList(QStringList)), this, SLOT(sl_onSetNameList(QStringList)));

    connect(csvFile, SIGNAL(si_setListData(QList<QByteArray>)), this, SLOT(sl_onGetListData(QList<QByteArray>)));


    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(6);
    this->show();

    csvFile->initCsvFile();
    qDebug() << "debug";
}
void Dialog::sl_onSetNbrCol(int nbrRow){

    m_nbrRow = nbrRow;
    while (ui->tableWidget->rowCount() < nbrRow){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    }

    //    ui->tableWidget->setColumnCount(m_nbrRow);


    QStringList fctNameList = {
        "Booléen",
        "Moyenne",
        "Min",
        "Max",
        "Nombre de changements",
        "Time"
    };
    ui->tableWidget->setVerticalHeaderLabels(m_nameList);
    ui->tableWidget->setHorizontalHeaderLabels(fctNameList);
}

void Dialog::sl_onSetNbrRow(int nbrRow){
    //    qDebug() << "real 2" << nbrRow;
    //    m_nbrRow = nbrRow;
    ////    while (ui->tableWidget->rowCount() < nbrRow){
    //    while (ui->tableWidget->rowCount() < 200){
    //    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    //    qDebug() << "ajout d'une ligne " << ui->tableWidget->rowCount();
    //    }
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sl_onNewValue(QString newName, QString newValue, int indexCol, int indexRow){

    //    qDebug() << "new value" << newValue;

    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((m_nbrRow+1)*(m_nbrCol+1)));
    newItem->setData(Qt::DisplayRole, newValue);
    ui->tableWidget->setItem(m_nbrRow, 2, newItem);


}

void Dialog::on_toolButton_clicked()
{
    if (!m_selecter) m_selecter = new SelectPeriod;

    connect(m_selecter, SIGNAL(si_closeSelectPeriod(QString,QString)), this, SLOT(sl_onClosePeriod(QString,QString)));

    qDebug() << "new" << m_selecter;
}

void Dialog::sl_onClosePeriod(QString fromDate, QString toDate){

    m_periodChoose.first = fromDate;
    m_periodChoose.second = toDate;

    if (m_selecter) delete  m_selecter;
    m_selecter = nullptr;
    qDebug() << "quit" << m_selecter;
    ui->plainTextEdit->clear();
    if (fromDate != " ")
        ui->plainTextEdit->insertPlainText(fromDate + "   -->  " + toDate);
}







void Dialog::on_toolButton_2_triggered(QAction *arg1)
{
    qDebug() << "triggered";
}

