#ifndef CSVFILE_H
#define CSVFILE_H

#include <QDebug>
#include <QFile>



class CSVFile
{
public:
    CSVFile();
    void getCSVRef(QString path);
    void modifyDoc();
    void fillListColumnName();

private:

    QList<QString> m_listColumnName;
    QFile *m_fileRef = nullptr;

};

#endif // CSVFILE_H
