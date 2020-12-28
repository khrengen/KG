#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->xRot, SIGNAL(valueChanged(int)), ui->widget, SLOT(setXRot(int)));
    connect(ui->yRot, SIGNAL(valueChanged(int)), ui->widget, SLOT(setYRot(int)));
    connect(ui->zRot, SIGNAL(valueChanged(int)), ui->widget, SLOT(setZRot(int)));
    connect(ui->size, SIGNAL(valueChanged(int)), ui->widget, SLOT(setParam(int)));
    connect(ui->vision, SIGNAL(stateChanged(int)), ui->widget, SLOT(setVision(int)));
    connect(ui->light, SIGNAL(stateChanged(int)), ui->widget, SLOT(setPrg(int)));
    connect(ui->apro, SIGNAL(valueChanged(int)), ui->widget, SLOT(setApro(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
