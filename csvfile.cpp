#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{
    m_fileRef = new QFile("C:/QtProject/parseMVB/telematics.csv");
    if (m_fileRef->open((QIODevice::ReadOnly))) qDebug() << "Ouverture ok du fichier";

    m_fileMVB = new QFile("MVB_and_CAN-mapping-Essaie.csv");
    if (m_fileMVB->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";

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
    for (int i = 0; i < m_nameColumn.size(); i++){
//        QByteArray array = m_nameColumn.at(i).toLatin1();
        QByteArray str = m_nameColumn.at(i).left(m_nameColumn.at(i).indexOf(';')).toLatin1();;
        if (!(!(str.contains('0')))){
            if (!(!(str.contains('0')))){

            }
        }
        QRegExp rec = (QRegExp("[\\.0-1:]*" ));
        if (rec.exactMatch(m_nameColumn.at(i))){
            qDebug() << m_nameColumn.at(i);
            flag = true;
        }
    }
    qDebug() << "out;";
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

}







