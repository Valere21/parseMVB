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
    void fillListColumnName();
    void fillData(QString line);

private:

    QList<QPair<QString,QList<QString>>> m_listColumnName;
    QPair<QString,QList<QString>> m_pairColumn;

    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
};

#endif // CSVFILE_H
