#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopenglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setParam(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
