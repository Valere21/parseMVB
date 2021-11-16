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
    connect(csvFile, SIGNAL(si_setListDataTime(QStringList)), this, SLOT(sl_onGetListDataTime(QStringList)));
    connect(csvFile, SIGNAL(si_setListData(QList<QList<QByteArray>>)), this, SLOT(sl_onGetListData(QList<QList<QByteArray>>)));


    ui->setupUi(this);
    this->show();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setColumnCount(6);

    csvFile->initCsvFile();
    m_indexTime = getTimeIndexPeriod();
}

int Dialog::getTimeIndexPeriod(){
    int index = 0;
    while (m_nameList.at(index) != "recv_time") index++;
    return index;

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

}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sl_onNewValue(QString newName, QString newValue, int indexCol, int indexRow){

    //  qDebug() << "new value" << newValue;
    m_listData.value(indexRow);
    m_listData.value(indexRow).value(indexCol) = newValue.toUtf8();
    //qDebug() << "System D" << m_listData.at(indexRow).at(indexCol);

    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((m_nbrRow+1)*(m_nbrCol+1)));
    newItem->setData(Qt::DisplayRole, newValue);
    ui->tableWidget->setItem(m_nbrRow, 2, newItem);

}


void Dialog::on_toolButton_clicked()
{
    if (m_selecter){
        delete  m_selecter;
        m_selecter = nullptr;
    }
    m_selecter = new SelectPeriod;
    m_selecter->setNameList(m_nameList);
    m_selecter->setDataTimeList(m_listDataTime);
    connect(m_selecter, SIGNAL(si_closeSelectPeriod(QString,QString)), this, SLOT(sl_onClosePeriod(QString,QString)));
    connect(m_selecter, SIGNAL(si_askGetListName()), this, SLOT(sl_onAskNameList()));
    connect(m_selecter, SIGNAL(si_askGetListDate()), this, SLOT(sl_onAskDateList()));

    connect(m_selecter, SIGNAL(si_setStartPeriod(QString)), this, SLOT(sl_onStartPeriod(QString)));
    connect(m_selecter, SIGNAL(si_setEndPeriod(QString)), this, SLOT(sl_onEndPeriod(QString)));
    connect(m_selecter, SIGNAL(si_acceptSelectPeriod()), this, SLOT(sl_onAcceptSelectPeriod()));


    setNameListDialog();

    qDebug() << "new" << m_selecter;
}

void Dialog::sl_onAcceptSelectPeriod(){
    qDebug() << "Accepted";
}

void Dialog::sl_onClosePeriod(QString fromDate, QString toDate){

    //    m_periodChoose.first = fromDate;
    //    m_periodChoose.second = toDate;

    //    qDebug() << "quit" << m_selecter;
    //    ui->plainTextEdit->clear();
    //    if (fromDate != " ")
    //        ui->plainTextEdit->insertPlainText(fromDate + "   -->  " + toDate);
}

void Dialog::sl_onStartPeriod(QString start){
    int index = 0;
    while (m_listDataTime.at(index) != start) index++;
    m_periodChoose.first = index;
    qDebug() << "FIRST" << start;
}

void Dialog::sl_onEndPeriod(QString end){
    int index = 0;
    while (m_listDataTime.at(index) != end) index++;
    m_periodChoose.second = index;
    qDebug() << "END" << end;
}

void Dialog::sl_onGetListDataTime(QStringList listTime){
    qDebug() << "GET LIST TIME " << listTime.size();
    m_listDataTime = listTime;
    //    m_selecter->m_ti
}

void Dialog::sl_onSetNameList(QStringList listName){
    m_nameList = listName;
}

void Dialog::sl_onAskNameList(){
    setNameListDialog();
    qDebug() << Q_FUNC_INFO;
}

void Dialog::sl_onAskDateList(){
    setDateListDialog();
}


void Dialog::on_pushButton_clicked()
{
    if (!m_periodChoose.first) m_periodChoose.first = 0;
    if (!m_periodChoose.second) m_periodChoose.second = 0;
}


void Dialog::on_checkBox_3_stateChanged(int arg1)
{
    //    qDebug() << "checker" << m_listData.at(5).at(0);
    qDebug() << "mlistData" << m_listData.size();
    if (arg1) qDebug() << "act";
    if (arg1){
        getBool();
    }


    if (!arg1) qDebug() << "diact";
}

enum {
    checkRow,
    checkCol
};

bool flag = false;
bool checkExitRecursiveCheck(int indexRow, int indexCol, int indexSizeRow, int indexSizeCol, int checker){
    switch (checker){
    case checkCol :{
        if (indexCol >= indexSizeCol)
            flag = false;
        else flag = true;
    }
    case checkRow:{
        if (indexRow >= indexSizeRow)
            flag = false;
        else flag =true;
    }
    }
    if (flag == false) qDebug() << "False " << indexCol << indexRow;
    return flag;
}

void Dialog::recursiveCheck(int index, int indexRow, int indexColumn, int indexTime){
    QList<QByteArray> list = m_listData.at(indexRow);
    QString str = list.at(indexColumn);
    if (index >= 50){
        qDebug() << "get out of here";
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg("0"));
        ui->tableWidget->setItem(indexRow, bool_column, newItem);
        index = 0;
        indexRow = indexRow + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkRow);
        indexColumn = indexColumn  + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkCol);
        recursiveCheck(index,indexRow, indexColumn,indexTime);
        return;
    }

    else if (index < 50){
        if (indexTime < m_periodChoose.second){
            if (str == '0'){
                qDebug() << "bool " << m_nameList.at(indexRow) << indexColumn;
                index++;
                indexRow = indexRow + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkRow);
                indexColumn = indexColumn  + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkCol);
                recursiveCheck(index,indexRow, indexColumn,indexTime);
            }
            else {
                qDebug() << "non bool" << str << m_nameList.at(indexRow);
                index++;
                indexRow = indexRow + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkRow);
                indexColumn = indexColumn  + checkExitRecursiveCheck(indexRow, indexColumn, m_listData.size(), list.size(), checkCol);
                recursiveCheck(index,indexRow, indexColumn,indexTime);
            }
        }
        else qDebug() << "equal" << m_periodChoose.second << indexTime;
    }
    qDebug() << "out";

    return;
}
void Dialog::getBool(){
//    if (m_periodChoose.first && m_periodChoose.second){
//        ui->plainTextEdit->clear();
//        qDebug() << Q_FUNC_INFO << m_periodChoose.first << m_periodChoose.second;
//        recursiveCheck(0, 0, 0, m_periodChoose.first);
//    }
//    else {
//        ui->plainTextEdit->clear();
//        ui->plainTextEdit->insertPlainText("VEUILLEZ CHOISIR UNE PERIODE DE TEMPS");
//    }

    int indexCol = 0;
    int indexRow = 0;
    int indexBool = 0;
    QList<QByteArray> listRow;

    while (indexCol < m_nameList.size()){
        while (indexRow < m_listData.size() && indexBool < 50){
            listRow = m_listData.at(indexRow);
            if (listRow.at(indexCol) == "0"){
//                qDebug() << "bool simple, col" << m_nameList.at(indexCol) << "ligne " << indexRow;
                indexBool++;
            }
            indexRow++;
        }
        if (indexBool >= 50) qDebug() << "boooool" << m_nameList.at(indexCol);
        indexBool = 0;
        indexRow = 0;
        indexCol++;
    }
    qDebug() << Q_FUNC_INFO;
}

















