#ifndef CUSTOMGLWIDGET_H
#define CUSTOMGLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

class CustomGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CustomGLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();

signals:

public slots:

};

#endif // CUSTOMGLWIDGET_H
