#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    csvFile = new CSVFile;

    connect(csvFile, SIGNAL(si_newValue(QString, QString, int, int)), this, SLOT(sl_onNewValue(QString, QString, int, int)));
    connect(csvFile, SIGNAL(si_getNbrCol(int)), this, SLOT(sl_onGetNbrCol(int)));
    connect(csvFile, SIGNAL(si_getNbrCol(int)), this, SLOT(sl_onGetNbrRow(int)));
    connect(csvFile, SIGNAL(si_getNameList(QStringList)), this, SLOT(sl_onGetNameList(QStringList)));


    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget->setRowCount(5);

    this->show();

    csvFile->initCsvFile();
    qDebug() << "debug";
}

void Dialog::sl_onGetNbrCol(int nbrCol){
    qDebug() << "real 2" << nbrCol ;
    m_nbrCol = nbrCol;
        while (ui->tableWidget->columnCount() < nbrCol){
        ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+1);
        }

    ui->tableWidget->setColumnCount(m_nbrCol);
    ui->tableWidget->setHorizontalHeaderLabels(m_nameList);

    QStringList fctNameList = {
    "Booléen",
        "Moyenne",
        "Min",
        "Max",
        "Nombre de changements"
    };
            ui->tableWidget->setVerticalHeaderLabels(fctNameList);
}

void Dialog::sl_onGetNbrRow(int nbrRow){
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

    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((m_nbrCol+1)*(m_nbrRow+1)));
    newItem->setData(Qt::DisplayRole, newValue);
    ui->tableWidget->setItem(2, m_nbrCol, newItem);


}
