#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{

    QFile *m_fileRef = new QFile("C://Users//Valere.gay-heuzey//OneDrive - RATP Dev//Documents//RATP DEV//RailNova//telematics.csv");
    m_fileRef->open(QIODevice::ReadWrite);
    getCSVRef("C://Users//Valere.gay-heuzey//OneDrive - RATP Dev//Documents//RATP DEV//RailNova//telematics.csv");
    fillListColumnName();
}


void CSVFile::getCSVRef(QString path){

    QFile *m_fileRef = new QFile(path);

    if (!m_fileRef->open(QIODevice::ReadWrite))
        return;
    int indexNnbrLine = 0;
    while (!m_fileRef->atEnd()) {
        QByteArray line = m_fileRef->readLine();
        indexNnbrLine++;
    }

    indexNnbrLine++;
    //        qDebug() << line;


    qDebug() << "nombre de lignes:" <<indexNnbrLine;
    fillListColumnName();
}



void CSVFile::fillListColumnName(){

    QFile *m_fileRef = new QFile("C://Users//Valere.gay-heuzey//OneDrive - RATP Dev//Documents//RATP DEV//RailNova//telematics.csv");
    m_fileRef->open((QIODevice::ReadWrite));
    QByteArray line = m_fileRef->readLine();

    line = line.remove(line.indexOf('\n'), line.size());
    while (!(line.isEmpty())){
        m_listColumnName.append(line.mid(0, line.indexOf(';')));
        qDebug() << line << "aahh";
        if (line.contains(';')) line.remove(0,line.indexOf(';'));
        else break;
    }
    qDebug() << "stop";
    qDebug() << m_listColumnName.at(1);
}
