#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>
#include <QPair>


class CSVFile
{
public:
    CSVFile();

    void modifyDoc();
    void fillColumnName();
    void fillData(QString line);
    void recursiveRegistration(QString line, int indexLine, int indexColumn);
    void displayList(QList<QPair<QString,QList<QString>>> listColumnName);

private:

    QList<QPair<QString,QList<QString>>> m_listColumnName;
    QPair<QString,QList<QString>> *m_pairColumn = nullptr;

    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;

    int m_nbrLigne;
    int m_nbrColonne;

};

#endif // CSVFILE_H
