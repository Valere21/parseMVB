#include "csvfile.h"
#include <iostream>

using namespace std;
CSVFile::CSVFile()
{
    m_fileRef = new QFile(QString::fromStdString("C:/QtProject/parseMVB/telematics.csv"));
    if (m_fileRef->open((QIODevice::ReadWrite))) qDebug() << "Ouverture ok du fichier";

    getName();
    //    fillColumnName();
}

void CSVFile::getName(){

    QString line = QString(m_fileRef->readLine());
    int index = 0;
    while(line.contains(';')){
        m_nameColumn.append(line.left(line.indexOf(';')));
        line = line.remove(0,line.indexOf(';')+1);
        index++;
    }
    m_nameColumn.append(line.left(line.indexOf('\r')));
    line = line.remove(0,line.indexOf('\r')+2);

    qDebug() << m_fileRef->size();
    QList<QStringList> listNewValue;
    while (!m_fileRef->atEnd()){
        line = QString(m_fileRef->readLine());
        QStringList list1 = line.split(QLatin1Char(';'));
        listNewValue.append(list1);
        //        for (int i = 0; i < list1.size(); i++){
        //            QString newStr = list1.at(i);
        //            m_nameColumn.value(i).append('\n' + str);
        //            //m_nameColumn.replace(i,m_nameColumn.at(i) + '\n' + line.at(i));
        //        }
    }

    for (int i = 0; i < listNewValue.size(); i++){
        for (int j = 0; j < listNewValue.at(i).size(); j++){
            QString str = QString(listNewValue.at(i).at(j));
            // m_nameColumn.value(i).append(listNewValue.at(i).at(j));
            m_nameColumn.value(i).append(str);
//            qDebug() << listNewValue.at(i).at(j);
//            qDebug() << m_nameColumn.at(i);
        }
    }

    for (int i = 0; i < m_nameColumn.size(); i++){
        qDebug() << m_nameColumn.at(i);
    }
}

void CSVFile::recursiveGetValue(QString line){

    qDebug() << Q_FUNC_INFO;



    while (!m_fileRef->atEnd()){


        QStringList list1 = line.split(QLatin1Char(';'));
        for (int i = 0; i < m_nameColumn.size(); i++){
            m_nameColumn.value(i).append(list1.at(i));
        }

        qDebug() << "list" << list1;
        line = m_fileRef->readLine();
    }
}


//void CSVFile::fillColumnName(){


//    int index = 0;
//    QString line = m_fileRef->readLine();

//    while(line.contains(';') || line.contains('\n')){

//        m_pairColumn = new QPair<QString, QList<QString>>;
//        if (line.contains(';')){
//            m_pairColumn->first = line.left(line.indexOf(';'));

//            line = line.remove(0,line.indexOf(';')+1);
//            m_listColumnName.append(*m_pairColumn);

//        }
//        else {
//            m_pairColumn->first = line.left(line.indexOf('\r'));
//            line = line.remove(0,line.indexOf('\r')+2);
//            m_listColumnName.append(*m_pairColumn);
//        }
//        delete m_pairColumn;
//        index++;
//    }
//    //    for (int i = 0; i < m_listColumnName.size(); i++) qDebug() << "column name: " << m_listColumnName.at(i);

//    line = m_fileRef->readLine();
//    recursiveRegistration(line,0,0);
//}



//void CSVFile::recursiveRegistration(QString line, int indexLine, int indexColumn){                                  //If it has been hard to write, it should be hard to read <3

//    //    qDebug() << line;



//    while (line.contains(';') || line.contains('\n')){

//        m_pairColumn = new QPair<QString, QList<QString>>;


//        if (line.contains(';')){

//            m_pairColumn->second.append(line.left(line.indexOf(';')));
//            m_pairColumn->first = m_listColumnName.at(indexColumn).first;
//            m_listColumnName.replace(indexColumn, *m_pairColumn);
//            line = line.remove(0, line.indexOf(';')+1);

//        }
//        else if (line.contains('\n')) {
//            m_pairColumn->second.append(line.left(line.indexOf('\n')));
//            m_pairColumn->first = m_listColumnName.at(indexColumn).first;
//            m_listColumnName.replace(indexColumn, *m_pairColumn);
//            line = line.remove(0, line.indexOf('\n')+1);
//        }
//        delete m_pairColumn;

//        qDebug() << "index ligne" << indexLine << "new value  " << m_listColumnName.at(indexColumn).first << m_listColumnName.at(indexColumn).second << m_listColumnName.at(indexColumn).second.size();
//        indexColumn++;
//    }
//    indexColumn = 0;
//    indexLine++;

//    //    if (m_listColumnName.size() < m_nbrLigne)

//    if (!(m_fileRef->atEnd())){
//        line = m_fileRef->readLine();
//        recursiveRegistration(line, indexLine, indexColumn);
//    }

//    displayList(m_listColumnName);

//}


//void CSVFile::displayList(QList<QPair<QString,QList<QString>>> listColumnName){

//    for (int i = 0; i < listColumnName.size(); i++)
//        for (int j = 0; j < m_listColumnName.at(i).second.size(); j++){
//            qDebug() << "index colonne" << i << "nom de la colonne" << m_listColumnName.at(i).first << "variable " << m_listColumnName.at(j).second << "nombre de variables associees" << m_listColumnName.at(j).second.size();
//            //            qDebug() << "list " << listColumnName.at(i).first << " & " << listColumnName.at(j).second;
//            //            qDebug() << "list " << listColumnName.at(i).first << " & " << listColumnName.at(j).second.size();
//        }
//}


/*
C:\QtProject\parseMVB\telematics2.csv
*/



/*

FULL BACKUP     FULL BACK UP        FULL BACKUP


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

    m_fileRef = new QFile(QString::fromStdString("C:/QtProject/parseLogMVB/telematics2.csv"));


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
        qDebug() << endl;
        qDebug() << "NEW";
        qDebug() << endl;

        for (int j = 0; j < m_nbrLigne; j++){
            qDebug() << "check de ses morts" << m_listColumnName.at(i).first << m_listColumnName.at(j).second;
        }
    }
}






C:\QtProject\parseMVB\telematics2.csv
        */


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
    //*/










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
