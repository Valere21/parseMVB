#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>
#include <QPair>
#include <QRegExpValidator>
#include <QString>
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
    
    void getData();
    void getName();
    void initCsvFile();
    void recursiveGetValue(QString lin);

    void setListValueTime();

    void checkBoolValue(int index, QString data);
    bool createFileDest(QString path);



signals:

    void    si_newValue(QString newName, QString newValue, int indexCol, int indexRow);
    void    si_setNbrCol(int nbrCol);
    void    si_setNbrRow(int nbrRow);
    void    si_setNameList(QStringList);
    void    si_setListData(QList<QByteArray>);

private slots:

    void    onReadyReadData();

private:

    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
    QFile *m_fileMVB = nullptr;

    // Liste contenant les noms de colonnes
    QStringList m_nameColumn;
    //Liste contenant les valeurs
    QList<QByteArray> *m_listByteArray = nullptr;


    QList<QPair<int, int[5]>> m_checker;


    int m_nbrLigne;
    int m_nbrColonne;

};

#endif // CSVFILE_H
