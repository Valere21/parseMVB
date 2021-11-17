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
    getData();
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

    QStringList listTime;
    int indexTime = 0;
    for (int i = 0; i < m_nameColumn.size(); i++){
        if (m_nameColumn.at(i).contains("recv_time")){
            indexTime = i;
            break;
        }
    }
    QList<QList<QByteArray>> list;
    QList<QByteArray> listRow;
    int indexRow = 0;
    while (!m_fileRef->atEnd()){
        m_listByteArray = new QList<QByteArray>(m_fileRef->readLine().split(';'));
        for (int i = 0; i < m_listByteArray->size(); i++){
            if (!listTime.contains(m_listByteArray->at(indexTime)))
                listTime.append(m_listByteArray->at(indexTime));
//            qDebug() << Q_FUNC_INFO << m_listByteArray->at(i);
            listRow.append(m_listByteArray->at(i));
            //qDebug() << "vaaalue" << m_listByteArray->at(i);
           // if (m_listByteArray->at(i).isEmpty()){qDebug() << "EMPTY"; emit si_newValue(m_nameColumn.at(i), " ", i, i);}
           // else emit si_newValue(m_nameColumn.at(i), m_listByteArray->at(i), i, i);
        }
        list.append(listRow);
        listRow.clear();
        indexRow++;
        QString str;
        for (int i = 0; i < m_listByteArray->size(); i++){
            for (int j = 0; j < m_listByteArray->at(i).size(); j++){
                str.append(m_listByteArray->at(i).at(j));
            }
            emit si_newValue(m_nameColumn.at(i), str, i, i);
            str.clear();
        }
    }
    qDebug() << " DATA LIST SIZE CSVFILE" <<  list.size();
    emit si_setListDataTime(listTime);
    emit si_setListData(list);
}


bool CSVFile::createFileDest(QString path){
    m_fileDest = new QFile(path);
    m_fileDest->open(QIODevice::ReadOnly);
    if (m_fileDest->isOpen())
        return true;
    else return false;
}




bool isOverLimite(QPair<QString,bool> *newPair){

    //    if (newPair->first >= 20);

    return newPair->second;
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



