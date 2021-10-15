#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{

    fillListColumnName();
}


void CSVFile::fillListColumnName(){

    qDebug() << "Quel nom fichier source (chemin complet) ?";
    string strRef;
    cin >> strRef;
    m_fileRef = new QFile(QString::fromStdString(strRef));

    //    qDebug() << "Quel nom fichier destination (chemin complet) ?";
    //    string strDest;
    //    cin >> strDest;
    //    m_fileDest = new QFile(QString::fromStdString(strDest));



    m_fileRef->open((QIODevice::ReadWrite));
    if (!m_fileRef->isOpen()){
        qDebug() << m_fileRef->error();
        fillListColumnName();
    }

    fillColumnName();
}

void CSVFile::fillColumnName(){

    qDebug() << Q_FUNC_INFO;

    int index = 0;
    while (!m_fileRef->atEnd()){
        QByteArray line = m_fileRef->readLine();

        while(line.contains(';') && line.contains('\n')){
            QString *newColumn = new QString(line.left(line.indexOf(';')));
            line = line.remove(0,line.indexOf(';')+1);
            m_pairColumn.first = *newColumn;
            m_listColumnName.append(m_pairColumn);
            delete newColumn;
            index++;
        }

        qDebug() << "size list " << m_listColumnName.size();
        for (int i = 0; i < m_listColumnName.size(); i++) qDebug() << "column name: " << m_listColumnName.at(i);
    }
}





/*
        C:\QtProject\parseMVB\telematics.csv
*/

















