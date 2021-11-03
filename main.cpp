#include <QCoreApplication>
#include <QApplication>
#include "csvfile.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog dialog;

    return a.exec();
}

