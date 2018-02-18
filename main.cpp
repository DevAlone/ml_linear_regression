#include "chartview.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(800, 600);

    w.show();
    //    ChartView chartView;

    //    chartView.show();

    return a.exec();
}
