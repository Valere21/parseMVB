#ifndef DIALOG_H
#define DIALOG_H

#include "csvfile.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:

void    sl_onNewValue(QString strName, QString strValue, int indexCol, int indexRow);
void    sl_onGetNbrCol(int nbrCol);
void    sl_onGetNbrRow(int nbrRow);
void    sl_onGetNameList(QStringList list){m_nameList = list;}

private:
    Ui::Dialog *ui;
    CSVFile *csvFile = nullptr;

    int m_nbrCol = 0;
    int m_nbrRow;
    QStringList m_nameList;
};

#endif // DIALOG_H
