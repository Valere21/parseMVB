#ifndef SELECTPERIOD_H
#define SELECTPERIOD_H

#include <QDialog>

namespace Ui {
class SelectPeriod;
}

class SelectPeriod : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPeriod(QWidget *parent = nullptr);
    ~SelectPeriod();

signals:
    //ferme la fenêtre
void    si_closeSelectPeriod(QString, QString);

private slots:
    //Si période de temps accepté
    void on_buttonBox_accepted();
    //Si période de temps refusé
    void on_buttonBox_rejected();

private:
    Ui::SelectPeriod *ui;

    QPair<QDateTime,QDateTime> *m_period = nullptr;
};

#endif // SELECTPERIOD_H
