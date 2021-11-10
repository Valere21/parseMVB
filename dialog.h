#ifndef DIALOG_H
#define DIALOG_H

#include "csvfile.h"
#include "selectperiod.h"
#include <QDialog>
#include <QTableWidgetItem>
#include <QStringList>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setNameListDialog(){m_selecter->setNameList(m_nameList); qDebug() << "sens !";}
    void setDateListDialog(){m_selecter->setDataTimeList(m_listDataTime); qDebug() << "date !";}
public slots:

    //envoie de nouvelles valeurs après traitement du csv, vers la gui
    void    sl_onNewValue(QString strName, QString strValue, int indexCol, int indexRow);

    //indique le nombres de lignes en fonctions de la taille du fichier csv
    void    sl_onSetNbrCol(int nbrRow);
    void    sl_onSetNbrRow(int nbrRow);

    //return la liste des noms de ligne, vers la gui
    void    sl_onSetNameList(QStringList listName);
    //réceptionne l'appel de return Namelist() depuis selectperiod
    void    sl_onAskNameList();
    //réceptionne l'appel de return Datelist() depuis selectperiod
    void    sl_onAskDateList();

    //get les valeurs depuis csvfile, vers dialog
//    void    sl_onGetListData(QList<QByteArray> listValue){m_listData = listValue; qDebug() << "DATA " << listValue;}
    //get les data time depuis csvfile, vers dialog
    void    sl_onGetListDataTime(QStringList listDataTime);

    //signal reçu au moment du delete du selectperiod. Return la date de séléction (from & to)
    void    sl_onClosePeriod(QString fromDate, QString toDate);

    void    sl_onStartPeriod(QString start){m_periodChoose.first = start; qDebug() << "FIRST " << m_periodChoose.first;}
    void    sl_onEndPeriod(QString end){m_periodChoose.second = end; qDebug() << "SECOND " << m_periodChoose.second;}

private slots:
    void on_toolButton_clicked();

private:
    Ui::Dialog *ui;
    CSVFile *csvFile = nullptr;

    int m_nbrCol;
    int m_nbrRow = 0;
    QStringList m_nameList;
    QList<QByteArray> m_listData;
    QStringList m_listDataTime;

    QPair<QString,QString> m_periodChoose;

    SelectPeriod *m_selecter = nullptr;

};

#endif // DIALOG_H
