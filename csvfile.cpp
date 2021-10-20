#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{
    fillListColumnName();
}


void CSVFile::fillListColumnName(){

    //    qDebug() << "Quel nom fichier source (chemin complet) ?";
    string strRef;
    //    cin >> strRef;

    m_fileRef = new QFile(QString::fromStdString("C://QtProject//parseMVB//telematics2.csv"));


    //    m_fileRef = new QFile(QString::fromStdString(strRef));

    if (m_fileRef->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";

    //    while (!m_fileRef->atEnd()){
    //        QString countLigne = m_fileRef->readLine();
    //        m_nbrLigne++;
    //        while (countLigne.contains(';')){
    //            countLigne.remove(';');
    //            m_nbrColonne++;
    //        }
    //        qDebug() << "NBR " << m_nbrColonne;
    //        break;
    //    }


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

        m_pairColumn = new QPair<QString, QList<QString>>;
        if (line.contains(';')){
            m_pairColumn->first = line.left(line.indexOf(';'));
            m_pairColumn->second.value(0) = "NaN";

            line = line.remove(0,line.indexOf(';')+1);
            m_listColumnName.append(*m_pairColumn);

        }
        else {
            m_pairColumn->first = line.left(line.indexOf('\r'));
            line = line.remove(0,line.indexOf('\r')+2);
            m_listColumnName.append(*m_pairColumn);
        }
        delete m_pairColumn;
        index++;
    }
    for (int i = 0; i < m_listColumnName.size(); i++) qDebug() << "column name: " << m_listColumnName.at(i);


    line = m_fileRef->readLine();
    recursiveRegistration(line,0,0);
    //    fillData(line);
    //    displayList(m_listColumnName);

}

void CSVFile::recursiveRegistration(QString line, int indexLine, int indexColumn){                                  //If it has been hard to write, it should be hard to read <3

    //    qDebug() << Q_FUNC_INFO << "indexLine " << indexLine << " & indexColumn " << indexColumn;
    //    qDebug() << line;
    while (line.contains(';') || line.contains('\n')){

        m_pairColumn = new QPair<QString, QList<QString>>;

        QString *newValue = new QString;
        if (line.contains(';')){
            *newValue = line.left(line.indexOf(';'));
            line = line.remove(0, line.indexOf(';')+1);
            m_pairColumn->second.append(*newValue);
            m_listColumnName.value(indexColumn) = *m_pairColumn;
        }
        else if (line.contains('\n')) {
            *newValue = line.left(line.indexOf('\n'));
            line = line.remove(0, line.indexOf('\n')+1);
            m_pairColumn->second.append(*newValue);
            m_listColumnName.value(indexColumn) = *m_pairColumn;
        }
        delete m_pairColumn;

                qDebug() << "new value  " << m_listColumnName.at(indexColumn).first << m_listColumnName.at(indexColumn).second << *newValue;
        indexColumn++;
        delete newValue;
    }
    indexLine++;

    if (m_listColumnName.size() < m_nbrLigne)
        recursiveRegistration(line, indexLine, indexColumn);

    qDebug() << "NEW" << m_nbrColonne;

    for (int i = 0; i < m_nbrColonne; i++){
        qDebug() << Qt::endl;
        qDebug() << "NEW";
        qDebug() << Qt::endl;

        for (int j = 0; j < m_nbrLigne; j++){
            qDebug() << "check de ses morts" << m_listColumnName.at(i).first << m_listColumnName.at(j).second;
        }
    }
}



//void CSVFile::fillData(QString line){

//    qDebug() << Q_FUNC_INFO;

//    int indexLigne = 0;
//    while (!m_fileRef->atEnd()){

//        qDebug() << "while end";

//        line = m_fileRef->readLine();
//        int indexColumn = 0;
//        while(line.contains(';') || line.contains('\n')){
//            qDebug() << "index " << indexLigne;
//            m_pairColumn.second.value(indexLigne) = line.left(line.indexOf(';')-1);
//            if (line.contains(';')) line = line.right(line.indexOf(';')+1);
//            else if (!line.contains(';')) line.resize(0);
//            m_listColumnName.value(indexColumn) = m_pairColumn;

//            indexColumn++;
//        }
//        indexLigne++;
//    }
//    displayList(m_listColumnName);
//}

/*
C:\QtProject\parseMVB\telematics2.csv
*/




// --- Work for static declaration ---

//void CSVFile::fillColumnName(){


//    int index = 0;
//    QString line = m_fileRef->readLine();

//    while(line.contains(';') || line.contains('\n')){

//        m_pairColumn = *new QPair<QString, QList<QString>>;
//        QString *newColumn = new QString;
//        if (line.contains(';')){
//            QString *newColumn = new QString(line.left(line.indexOf(';')));
//            m_pairColumn
//            line = line.remove(0,line.indexOf(';')+1);
//            m_pairColumn.first = *newColumn;
//            m_listColumnName.append(m_pairColumn);
//        }
//        else {
//            QString *newColumn = new QString(line.left(line.indexOf('\r')));
//            line = line.remove(0,line.indexOf('\r')+2);
//            m_pairColumn.first = *newColumn;
//            m_listColumnName.append(m_pairColumn);
//        }
//        delete m_pairColumn
//        delete newColumn;
//        index++;
//    }
//    for (int i = 0; i < m_listColumnName.size(); i++) qDebug() << "column name: " << m_listColumnName.at(i);


//    line = m_fileRef->readLine();
//    recursiveRegistration(line,0,0);
//    //    fillData(line);
//    //    displayList(m_listColumnName);

//}

//void CSVFile::recursiveRegistration(QString line, int indexLine, int indexColumn){                                  //If it has been hard to write, it should be hard to read <3

//    //    qDebug() << Q_FUNC_INFO << "indexLine " << indexLine << " & indexColumn " << indexColumn;
//    //    qDebug() << line;
//    while (line.contains(';') || line.contains('\n')){

//        QString *newValue = new QString;
//        if (line.contains(';')){
//            *newValue = line.left(line.indexOf(';'));
//            line = line.remove(0, line.indexOf(';')+1);
//            m_listColumnName.at(indexColumn).second.value(indexLine) = *newValue;
////            qDebug() << m_listColumnName.at(indexColumn).second.at(indexLine);
//        }
//        else if (line.contains('\n')) {
//            *newValue = line.left(line.indexOf('\n'));
//            line = line.remove(0, line.indexOf('\n')+1);
//            m_listColumnName.at(indexColumn).second.value(indexLine) = *newValue;
//        }


//        qDebug() << "new value  " << *newValue << m_listColumnName.at(indexColumn).first << m_listColumnName.at(indexColumn).second;
//        indexColumn++;
//        delete newValue;
//    }
//    indexLine++;

//    if (m_listColumnName.size() < m_nbrLigne)
//        recursiveRegistration(line, indexLine, indexColumn);

//    for (int i = 0; i < m_nbrLigne; i++){
//        qDebug() << "check de ses morts" << m_listColumnName.at(i).first << m_listColumnName.at(i).second;

//    }

//}
