#include "mainwindow.h"
#include <QApplication>
#include "datarecord.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("hello world");
    w.show();
    return a.exec();
}
