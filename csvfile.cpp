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
<<<<<<< HEAD
    if (m_fileRef->open((QIODevice::ReadWrite))){
        qDebug() << "Ouverture ok du fichier";
    }

    while (m_fileRef->atEnd()){
        QString countLigne = m_fileRef->readLine();
        m_nbrLigne++;
        while (countLigne.contains(';')){
            countLigne.remove(';');
            m_nbrColonne++;
        }
    }

=======
    if (m_fileRef->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";
>>>>>>> 496eead1288650b2f287ad287a0c0f7142d34941

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
<<<<<<< HEAD




void CSVFile::fillColumnName(){
=======

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
>>>>>>> 496eead1288650b2f287ad287a0c0f7142d34941

}

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
    line = m_fileRef->readLine();
    recursiveRegistration(line, 0, 0);
    /*fillData(line);*/
    //    displayList(m_listColumnName);

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


<<<<<<< HEAD


void CSVFile::recursiveRegistration(QString line, int indexLine, int indexColumn){                                  //If it has been hard to write, it should be hard to read <3
    //    qDebug() << Q_FUNC_INFO << "indexLine " << indexLine << " & indexColumn " << indexColumn;
    //    qDebug() << line;

    if (line.contains(';') || line.contains('\n')){
        QString str;

        if (line.at(0) != ' ' || line.at(0) != ';') m_listColumnName.at(indexColumn).second.value(indexLine) = line.left(line.indexOf(';'));
        else str = "42";
        qDebug() << "1er if & " << str;

        line = line.remove(0, line.indexOf(';')+1);

        indexColumn++;
        recursiveRegistration(line, indexLine, indexColumn);
    }
    else {

        qDebug() << "2eme if";
        indexColumn = 0;
        qDebug() << "1 " << line;
        line = m_fileRef->readLine();
        qDebug() << "2 " << line;
        indexLine++;
    }

}




void CSVFile::fillData(QString line){

    qDebug() << Q_FUNC_INFO;

    int indexLigne = 0;
    while (!m_fileRef->atEnd()){

        qDebug() << "while end";

        line = m_fileRef->readLine();
        int indexColumn = 0;
        while(line.contains(';') || line.contains('\n')){
            qDebug() << "index " << indexLigne;
            m_pairColumn.second.value(indexLigne) = line.left(line.indexOf(';')-1);
            if (line.contains(';')) line = line.right(line.indexOf(';')+1);
            else if (!line.contains(';')) line.resize(0);
            m_listColumnName.value(indexColumn) = m_pairColumn;

            indexColumn++;
        }
        indexLigne++;
    }
    displayList(m_listColumnName);
}
=======
/*
>>>>>>> 496eead1288650b2f287ad287a0c0f7142d34941

C:\QtProject\parseMVB\telematics2.csv

<<<<<<< HEAD
/*
C:\QtProject\parseLogMVB\telematics.csv
=======
>>>>>>> 496eead1288650b2f287ad287a0c0f7142d34941
*/
