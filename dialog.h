#ifndef DIALOG_H
#define DIALOG_H

#include "csvfile.h"
#include "selectperiod.h"
#include <QDialog>
#include <QTableWidgetItem>
#include <QStringList>
#include <QWidget>
#include <string.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    enum {
        bool_column,
        min_column,
        max_column,
        stage_changed_column
    };

    enum {
        check_bool,
        check_min_max,
        check_stage_changed
    };

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void getBool();
    void getMin();
    void getMax();
    void getMoyenne(QString columnName);
    void getTimeValueChanged(QString columnName);




    int getTimeIndexPeriod();

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
    void    sl_onGetListData(QList<QList<QByteArray>> listValue){m_listData = listValue; qDebug() << "DATA RECEIVE" << listValue.size();}
    //get les data time depuis csvfile, vers dialog
    void    sl_onGetListDataTime(QStringList listDataTime);

    void    sl_onAcceptSelectPeriod();
    //signal reçu au moment du delete du selectperiod. Return la date de séléction (from & to)
    void    sl_onClosePeriod(QString fromDate, QString toDate);

    void    sl_onStartPeriod(QString start);
    void    sl_onEndPeriod(QString end);

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_clicked();

private:
    Ui::Dialog *ui;
    CSVFile *csvFile = nullptr;
    SelectPeriod *m_selecter = nullptr;

    int m_nbrCol;
    int m_nbrRow = 0;
    int m_indexTime = 0;

    QStringList m_nameList;
    QStringList m_listDataTime;
    QList<QList<QByteArray>> m_listData;

    QPair<int,int> m_periodChoose;
    QPair<int,int> m_minMaxCheck;


};

#endif // DIALOG_H
