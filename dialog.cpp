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

void Dialog::on_checkBox_clicked()
{
getMin();
}
void Dialog::getBool(){

    int indexCol = 0;
    int indexRow = 0;
    int indexBool = 0;
    QList<QByteArray> listRow;

    while (indexRow < m_nameList.size()){
        while (indexCol < m_listData.size() && indexBool < 50){
            listRow = m_listData.at(indexRow);
            if (listRow.at(indexRow) == "0")
                indexBool++;
            indexCol++;
        }
        if (indexBool >= 50){
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg("0"));
            ui->tableWidget->setItem(indexRow, bool_column, newItem);
        }
        indexBool = 0;
        indexCol = 0;
        indexRow++;
    }
}

void Dialog::getMin(){
    int indexCol = 0;
    int indexRow = 0;
    int inde = 0;
    QList<QByteArray> listRow;

    while (indexRow < m_nameList.size()){
        while (indexCol < m_listData.size()){
            listRow = m_listData.at(indexRow);
            if (listRow.at(indexRow).toInt() <= m_minMaxCheck.first)
                m_minMaxCheck.first = listRow.at(indexRow).toInt();
            if (listRow.at(indexRow).toInt() >= m_minMaxCheck.second)
                m_minMaxCheck.second = listRow.at(indexRow).toInt();
                    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(m_minMaxCheck.first));
                    ui->tableWidget->setItem(indexRow, min_column, newItem);
                    QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("%1").arg(m_minMaxCheck.second));
                    ui->tableWidget->setItem(indexRow, max_column, newItem2);
                    indexCol++;
                    qDebug() << inde;
                    inde++;
        }
        indexCol = 0;
        indexRow++;
    }
}





