#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>
#include <QPair>
#include <QRegExpValidator>

class CSVFile
{
public:
    CSVFile();

//    void modifyDoc();
//    void fillColumnName();
//    void fillData(QString line);
//    void recursiveRegistration(QString line, int indexLine, int indexColumn);
//    void displayList(QList<QPair<QString,QList<QString>>> listColumnName);
<<<<<<< HEAD
=======
    int getMinMaxValue(QString columnName);
    int getMoyenne(QString columnName);
    int getTimeValueChanged(QString columnName);
    
    void recursiveGetValue(QString lin);
>>>>>>> ef851b7f1376bbcf0bbebf0476ff65d012a8e8da
    void getName();
    void getData();
    void checkBoolValue();
    bool createFileDest(QString path);
    void recursiveGetValue(QString line);

private:

//    QList<QPair<QString,QList<QString>>> m_listColumnName;
//    QPair<QString,QList<QString>> *m_pairColumn = nullptr;

    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
    QFile *m_fileMVB = nullptr;

    QStringList m_nameColumn;
    QPair<QStringList,bool> m_indexBoolValue;

    int m_nbrLigne;
    int m_nbrColonne;

};

#endif // CSVFILE_H
