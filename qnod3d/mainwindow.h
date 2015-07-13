#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGLWidget *qglwidget;
};

#endif // MAINWINDOW_H
