#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>
#include <QPair>
#include <QRegExpValidator>

class CSVFile : public QObject
{

    Q_OBJECT

public:
    CSVFile();

//    void modifyDoc();
//    void fillColumnName();
//    void fillData(QString line);
//    void recursiveRegistration(QString line, int indexLine, int indexColumn);
//    void displayList(QList<QPair<QString,QList<QString>>> listColumnName);

    int getMinMaxValue(QString columnName);
    int getMoyenne(QString columnName);
    int getTimeValueChanged(QString columnName);
    
    void recursiveGetValue(QString lin);
    void getName();
    void getData();
    void checkBoolValue(QString data, int index);
    bool createFileDest(QString path);

    void initCsvFile();


signals:

void    si_newValue(QString newName, QString newValue, int indexCol, int indexRow);
void    si_getNbrCol(int nbrCol);
void    si_getNbrRow(int nbrRow);
void    si_getNameList(QStringList);

private:


    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
    QFile *m_fileMVB = nullptr;

    // Liste contenant les noms de colonnes
    QStringList m_nameColumn;

    // Liste contenant les valeurs de chaque colonnes
    QList<QList<QByteArray>*> m_listValue;
    QList<QByteArray> *m_listByteArray= nullptr;


    QList<QPair<QString, bool>> m_indexBoolValue;


    int m_nbrLigne;
    int m_nbrColonne;

};

#endif // CSVFILE_H
