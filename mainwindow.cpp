#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->resetZoomButton, &QPushButton::clicked,
        ui->chartView, &ChartView::resetZoom);
    connect(
        ui->resetDatasetButton, &QPushButton::clicked,
        ui->chartView, &ChartView::resetDataset);
}

MainWindow::~MainWindow()
{
    delete ui;
}
