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
    if (m_fileRef->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";

    //    qDebug() << "Quel nom fichier destination (chemin complet) ?";
    //    string strDest;
    //    cin >> strDest;
    //    m_fileDest = new QFile(QString::fromStdString(strDest));

    //    int a = m_fileRef->size();



    fillColumnName();

}

void displayList(QList<QPair<QString,QList<QString>>> m_listColumnName){

    for (int i = 0; i < m_listColumnName.size(); i++)
        qDebug() << "list " << m_listColumnName.at(i).first << " & " << m_listColumnName.at(i).second;

}

void CSVFile::fillColumnName(){


    int index = 0;
    QString line = m_fileRef->readLine();

    while(line.contains(';') || line.contains('\n')){

        QString *newColumn = new QString;
        if (line.contains(';')){
            QString *newColumn = new QString(line.left(line.indexOf(';')));
            line = line.remove(0,line.indexOf(';')+1);
            m_pairColumn.first = *newColumn;
            m_listColumnName.append(m_pairColumn);
        }
        else {
            QString *newColumn = new QString(line.left(line.indexOf('\r')));
            line = line.remove(0,line.indexOf('\r')+2);
            m_pairColumn.first = *newColumn;
            m_listColumnName.append(m_pairColumn);
        }
        delete newColumn;
        index++;
    }
    for (int i = 0; i < m_listColumnName.size(); i++) qDebug() << "column name: " << m_listColumnName.at(i);

    fillData(line);
    //    displayList(m_listColumnName);

}


void CSVFile::fillData(QString line){

    int indexLigne = 0;
    while (!m_fileRef->atEnd()){
        line = m_fileRef->readLine();
        int indexColumn = 0;
        while(line.contains(';') || line.contains('\n')){
//            if (line.left(1) == ';') line.remove(0,1);
            if (line.contains(';')){
                m_pairColumn.second.value(indexColumn) = line.left(line.indexOf(';'));
                m_listColumnName.value(indexLigne) = m_pairColumn;
                qDebug() << m_listColumnName.at(indexLigne);
                line = line.remove(0,line.indexOf(';')+1);
            }
            else {
                m_pairColumn.second.value(indexColumn) = line.left(line.indexOf(';'));
                qDebug() << m_listColumnName.at(indexColumn).first << " & " << m_listColumnName.at(indexLigne).second;
                line = line.remove(0,line.indexOf(';')+1);
            }
            indexColumn++;
        }
        indexLigne++;
    }
}


/*

C:\QtProject\parseMVB\telematics2.csv

*/
