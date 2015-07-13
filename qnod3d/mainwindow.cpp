#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSizePolicy qspLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy qspRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    qspLeft.setHorizontalStretch(1);
    qspRight.setHorizontalStretch(3);

    this->qglwidget = new CustomGLWidget(this);
    this->qglwidget->setSizePolicy(qspRight);

    ui->qglcontainer->addWidget(this->qglwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
