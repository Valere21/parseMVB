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

    void setNameList(QStringList nameList){m_listName = nameList;}
    void setList();

signals:
    //ferme la fenêtre depuis this, vers dialog
    void    si_closeSelectPeriod(QString, QString);
    //lance un signal sur slot dans dialog pour appeller fonction de return de list name
    void    si_askGetListName();

private slots:
    //Si période de temps accepté
    void on_buttonBox_accepted();
    //Si période de temps refusé
    void on_buttonBox_rejected();


    void on_pushButton_clicked();

protected:
    Ui::SelectPeriod *ui;


    QStringList m_listName;
    QPair<QDateTime,QDateTime> *m_period = nullptr;
};

#endif // SELECTPERIOD_H
