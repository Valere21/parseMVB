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

    if (newPair->first >= 20);

}


void CSVFile::checkBoolValue(QString data,int index){

    qDebug() << "DATAAAAAAAAAAAAAAAAAAAAAAA" << data;

    int pos = 0;
    QPair<QString,int> *checker = new QPair<QString,int>;
    checker->first = data;
    checker->second++;
    m_checker.append(*checker);


    QRegExpValidator rec(QRegExp("0|1|;"));
    QPair<int,int> *newPair = new QPair<int,int>;
    QString str = data;
    if (rec.validate(str, pos) == QValidator::Acceptable){
        newPair->second = true;
        //            qDebug() << "Acceptable" << index << "indicator" << in;
        //            qDebug() << data;
    }

    //        if (rec.validate(data, pos) == QValidator::Intermediate) qDebug() << "Intermediate" << index;

    if (rec.validate(str, pos) == QValidator::Invalid){
        newPair->second = false;
        //            qDebug() << "Invalid" << index << "indicator" << in;
        //            qDebug() << data;
    }

    m_indexBoolValue.append(*newPair);
    delete newPair;

    //    qDebug() << "out;";
}



void CSVFile::getData(){

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

    QList<QByteArray> listSorted = m_fileRef->readLine().split(';');

    emit si_getNameList(m_nameColumn);
    emit si_getNbrCol(listSorted.size());

    qDebug() << "real" << (m_fileRef->readLine().split(';')).size();
    qDebug() << m_fileRef->size();

    while (!m_fileRef->atEnd()){
        m_listByteArray = new QList<QByteArray>;
        m_listByteArray = &listSorted;

        for (int i = 0; i < m_listByteArray->size(); i++){
            emit si_newValue(m_nameColumn.at(i), m_listByteArray->at(i), i, i);
            checkBoolValue(m_listByteArray->at(i), i);
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
            checkBoolValue(str, i);
            str.clear();
        }
    }
}

// DCU_CCentrlOpen






