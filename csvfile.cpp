#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{
    m_fileRef = new QFile("C:/QtProject/parseMVB/telematics.csv");
    if (m_fileRef->open((QIODevice::ReadOnly))) qDebug() << "Ouverture ok du fichier";

    m_fileMVB = new QFile("MVB_and_CAN-mapping-Essaie.csv");
    if (m_fileMVB->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";


}

void CSVFile::initCsvFile(){
    getName();
    emit m_fileRef->waitForReadyRead(10000);
    getData();
}

bool CSVFile::createFileDest(QString path){
    m_fileDest = new QFile(path);
    m_fileDest->open(QIODevice::ReadOnly);
    if (m_fileDest->isOpen())
        return true;
    else return false;
}

int in = 0;

bool isOverLimite(QPair<QString,bool> *newPair){

    //    if (newPair->first >= 20);

    return newPair->second;
}

int CSVFile::getMinMaxValue(QString c){



}

void CSVFile::checkBoolValue(int index, QString data){

    int pos = 0;

    //    QVariant(s).value<T>()


    QRegExpValidator rec(QRegExp("0|1|;"));
    QPair<int, int[5]> *checker = new QPair<int, int[5]>;
    if (rec.validate(data, pos) == QValidator::Acceptable){
        checker->first = index;
        int val = data.toInt()+1;
        checker->second[0] = 1;
        checker->second[1]++;               //itération à chaque true
        checker->second[2] = 100;           //valeur max
        checker->second[3] = 5;             //valeur min
    }
    if (rec.validate(data, pos) == QValidator::Invalid){
        checker->first = index;
        checker->second[0] = 0;
        checker->second[1] = 0;               //nombre
        checker->second[2] = 100;           //valeur max
        checker->second[3] = 5;             //valeur min
    }

    m_checker.append(*checker);
    delete checker;

    qDebug() << "out;";
}

void CSVFile::getName(){

    QByteArray str = m_fileRef->readLine();
    QString line = str;
    int index = 0;


    while(line.contains(';')){
        m_nameColumn.append(line.left(line.indexOf(';')));
        line = line.remove(0,line.indexOf(';')+1);
        index++;
    }
    m_nameColumn.append(line.left(line.indexOf('\r')));
    line = line.remove(0,line.indexOf('\r')+2);

    for (int i = 0; i < m_nameColumn.size();i++) qDebug() << m_nameColumn.at(i);

    emit si_setNameList(m_nameColumn);
    emit si_setNbrCol(m_fileRef->readLine().split(';').size());
}

void CSVFile::getData(){
    connect(m_fileRef, SIGNAL(readyRead()), this, SLOT(onReadyReadData()));                                                                          //Connect au slot de lecture
    if (m_fileRef->isReadable()) qDebug() << "ok";
}

void CSVFile::onReadyReadData(){

    QList<QByteArray> listSorted = m_fileRef->readLine().split(';');

//    while (!m_fileRef->atEnd()){
    while (!m_fileRef->bytesAvailable()){
        QByteArray str2 = m_fileRef->readLine();
        m_listByteArray = new QList<QByteArray>(m_fileRef->readLine().split(';'));
        m_listByteArray = &listSorted;
        for (int i = 0; i < m_listByteArray->size(); i++){
            emit si_newValue(m_nameColumn.at(i), m_listByteArray->at(i), i, i);
            //checkBoolValue(i, QString(m_listByteArray->at(i)));
        }

        //        for (int i = 0; i < m_indexBoolValue.size(); i++) qDebug() << "BOOL :" << m_indexBoolValue.at(i);

        QString str;
        for (int i = 0; i < m_listByteArray->size(); i++){
            for (int j = 0; j < m_listByteArray->at(i).size(); j++){
                str.append(m_listByteArray->at(i).at(j));
                //                emit si_newValue(m_nameColumn.at(i), str, i, j);
                //                qDebug() << indexA; indexA++;
            }
            //                  qDebug() << str;
            //checkBoolValue(i, str);
            str.clear();
        }
    }
    emit si_setListData(*m_listByteArray);
    setListValueTime();
}

// DCU_CCentrlOpen

void CSVFile::setListValueTime(){
    qDebug() << Q_FUNC_INFO;
    QStringList listTime;
    int indexTime = 0;
    qDebug() << *m_listByteArray;
    qDebug() << *m_listByteArray->at(1);

    for (int i = 0; i < m_nameColumn.size(); i++){
//        qDebug() << "TIIIIME" << m_listByteArray->at(i);
//        qDebug() << "loop" << m_nameColumn.size() << m_nameColumn.at(i);
        if (m_nameColumn.at(i).contains("recv_time")){
            indexTime = i;
//            qDebug() << m_nameColumn.at(i) << indexTime;
            break;
        }
    }
    for (int i = 0; i < m_listByteArray->at(indexTime).size(); i++){
        listTime.append(m_listByteArray->at(i));
    }
//    qDebug() << "time " << listTime;
}





