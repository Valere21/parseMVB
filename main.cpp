#include <QCoreApplication>
#include "csvfile.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CSVFile csvfile;

    return a.exec();
}
