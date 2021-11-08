#ifndef DIALOG_H
#define DIALOG_H

#include "csvfile.h"
#include "selectperiod.h"
#include <QDialog>
#include <QTableWidgetItem>

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

    //envoie de nouvelles valeurs après traitement du csv, vers la gui
void    sl_onNewValue(QString strName, QString strValue, int indexCol, int indexRow);

    //indique le nombres de lignes en fonctions de la taille du fichier csv
void    sl_onSetNbrCol(int nbrRow);
void    sl_onSetNbrRow(int nbrRow);

    //return la liste des noms de ligne, vers la gui
void    sl_onSetNameList(QStringList listName){m_nameList = listName;}

    //get les valeurs depuis csvfile, vers dialog
void    sl_onGetListData(QList<QByteArray> listValue){m_dialogData = listValue;}

//signal reçu au moment du delete du selectperiod. Return la date de séléction (from & to)
void    sl_onClosePeriod(QString fromDate, QString toDate);

private slots:
void on_toolButton_clicked();

void on_toolButton_2_triggered(QAction *arg1);

private:
    Ui::Dialog *ui;
    CSVFile *csvFile = nullptr;

    int m_nbrCol;
    int m_nbrRow = 0;
    QStringList m_nameList;
    QList<QByteArray> m_dialogData;

    QPair<QString,QString> m_periodChoose;

    SelectPeriod *m_selecter = nullptr;

};

#endif // DIALOG_H
