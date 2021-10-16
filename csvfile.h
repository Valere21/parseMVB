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
    void fillData();

private:

    QList<QPair<QString,int*>> m_listColumnName;
    QPair<QString,int*> m_pairColumn;

    QFile *m_fileRef = nullptr;
    QFile *m_fileDest = nullptr;
};

#endif // CSVFILE_H
