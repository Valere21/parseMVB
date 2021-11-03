#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>
#include <QPair>
#include <QRegExpValidator>

<<<<<<< HEAD
class CSVFile
=======
class CSVFile : public QObject
>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53
{

    Q_OBJECT

public:
    CSVFile();

//    void modifyDoc();
//    void fillColumnName();
//    void fillData(QString line);
//    void recursiveRegistration(QString line, int indexLine, int indexColumn);
//    void displayList(QList<QPair<QString,QList<QString>>> listColumnName);
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======

>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53
    int getMinMaxValue(QString columnName);
    int getMoyenne(QString columnName);
    int getTimeValueChanged(QString columnName);
    
    void recursiveGetValue(QString lin);
>>>>>>> ef851b7f1376bbcf0bbebf0476ff65d012a8e8da
    void getName();
    void getData();
<<<<<<< HEAD
    void checkBoolValue();
    bool createFileDest(QString path);
    void recursiveGetValue(QString line);
=======
    void checkBoolValue(QString data, int index);
    bool createFileDest(QString path);

    void initCsvFile();


signals:

void    si_newValue(QString newName, QString newValue, int indexCol, int indexRow);
void    si_getNbrCol(int nbrCol);
void    si_getNbrRow(int nbrRow);
void    si_getNameList(QStringList);
>>>>>>> 2e8d1c1f79fa28e5dc3cfd729bebd32387c9ed53

private:


    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
    QFile *m_fileMVB = nullptr;

    // Liste contenant les noms de colonnes
    QStringList m_nameColumn;
    QPair<QStringList,bool> m_indexBoolValue;

    // Liste contenant les valeurs de chaque colonnes
    QList<QList<QByteArray>*> m_listValue;
    QList<QByteArray> *m_listByteArray= nullptr;


    QList<QPair<QString, bool>> m_indexBoolValue;


    int m_nbrLigne;
    int m_nbrColonne;

};

#endif // CSVFILE_H
