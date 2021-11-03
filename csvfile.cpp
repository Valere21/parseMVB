#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{
<<<<<<< HEAD
    m_fileRef = new QFile("C:/QtProject/parseMVB/telematics.csv");
=======
    m_fileRef = new QFile("C:/QtProject/parseLogMVB/telematics.csv");
>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53
    if (m_fileRef->open((QIODevice::ReadOnly))) qDebug() << "Ouverture ok du fichier";

    m_fileMVB = new QFile("MVB_and_CAN-mapping-Essaie.csv");
    if (m_fileMVB->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";
<<<<<<< HEAD

    getData();
    checkBoolValue();
}

bool CSVFile::createFileDest(QString path){
    m_fileDest = new QFile(path);
    m_fileDest->open(QIODevice::ReadOnly);
    if (m_fileDest->isOpen())
        return true;
    else return false;
}

void CSVFile::checkBoolValue(){

    bool flag = false;
    int pos = 0;
    for (int i = 0; i < m_nameColumn.size(); i++){
        QString array = m_nameColumn.at(i).right(m_nameColumn.at(i).indexOf(';')+1);
        qDebug() << array;
        qDebug() << m_nameColumn.at(i);

        QRegExpValidator rec(QRegExp("0|1|;"));
        if (rec.validate(array, pos))
                qDebug() << "TRUE " << array;
        else qDebug() << "it cannot be " << array;

    }
    qDebug() << "out;";
}

=======


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

void CSVFile::checkBoolValue(QString data,int index){

    int pos = 0;

        QRegExpValidator rec(QRegExp("0|1|;"));
        QPair<QString,bool> *newPair = new QPair<QString, bool>;
        newPair->first = m_nameColumn.at(index);

        if (rec.validate(data, pos) == QValidator::Acceptable){
            newPair->second = true;
//            qDebug() << "Acceptable" << index;
        }

//        if (rec.validate(data, pos) == QValidator::Intermediate) qDebug() << "Intermediate" << index;

        if (rec.validate(data, pos) == QValidator::Invalid){
            newPair->second = false;
//            qDebug() << "Invalid" << index;
        }

        m_indexBoolValue.append(*newPair);
        delete newPair;

//    qDebug() << "out;";
}

>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53


void CSVFile::getData(){

    QByteArray str = m_fileRef->readLine();
    QString line = str;
    int index = 0;
<<<<<<< HEAD
=======


>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53
    while(line.contains(';')){
        m_nameColumn.append(line.left(line.indexOf(';')));
        line = line.remove(0,line.indexOf(';')+1);
        index++;
    }
    m_nameColumn.append(line.left(line.indexOf('\r')));
    line = line.remove(0,line.indexOf('\r')+2);
<<<<<<< HEAD


    for (int i = 0; i<m_nameColumn.size();i++) qDebug() << m_nameColumn.at(i);

    while (!m_fileRef->atEnd()){
        QStringList list2 = QString(m_fileRef->readLine()).split(QLatin1Char(';'));
        for (int i = 0; i < list2.size(); i++){
            if (!(m_nameColumn.at(i).right(m_nameColumn.at(i).indexOf((';')+1)).isEmpty())) {
                QString newStr = m_nameColumn.at(i) + ';' + list2.at(i);
                m_nameColumn.replace(i, newStr);
            }
        }
    }
        qDebug() << m_nameColumn.at(m_nameColumn.size()-2);

=======


    for (int i = 0; i < m_nameColumn.size();i++) qDebug() << m_nameColumn.at(i);

    emit si_getNameList(m_nameColumn);
    emit si_getNbrCol((m_fileRef->readLine().split(';')).size());


    qDebug() << "real" << (m_fileRef->readLine().split(';')).size();
    qDebug() << m_fileRef->size();
    while (!m_fileRef->atEnd()){
        m_listByteArray = new QList<QByteArray>;
        QList<QByteArray> listSorted = m_fileRef->readLine().split(';');
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
            //            qDebug() << str;
            checkBoolValue(str, i);
            str.clear();
        }
    }
>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53
}

// DCU_CCentrlOpen






