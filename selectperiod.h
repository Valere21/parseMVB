#ifndef SELECTPERIOD_H
#define SELECTPERIOD_H

#include <QDialog>
#include <QStringList>
#include <QListWidget>

namespace Ui {
class SelectPeriod;
}

class SelectPeriod : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPeriod(QWidget *parent = nullptr);
    ~SelectPeriod();

    void setList();
    void setNameList(QStringList nameList){m_listName = nameList;}
    void setDataTimeList(QStringList listTime){m_timePeriod = listTime;}

signals:
    //ferme la fenêtre depuis this, vers dialog
    void    si_closeSelectPeriod(QString, QString);
    //lance un signal sur slot dans dialog pour appeller fonction de return de list name
    void    si_askGetListName();
    //lance un signal sur slot dans dialog pour appeller fonction de return de list date time
    void    si_askGetListDate();

    void    si_setEndPeriod(QString, int);
    void    si_setStartPeriod(QString, int);
    void    si_acceptPeriod();
private slots:
    //Si période de temps accepté
    void on_buttonBox_accepted();
    //Si période de temps refusé
    void on_buttonBox_rejected();


    void on_pushButton_clicked();

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_listWidget_2_itemActivated(QListWidgetItem *item);

protected:
    Ui::SelectPeriod *ui;


    QStringList m_listName;
    QStringList m_timePeriod;
};

#endif // SELECTPERIOD_H
