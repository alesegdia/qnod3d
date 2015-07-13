#include "customglwidget.h"

CustomGLWidget::CustomGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void CustomGLWidget::initializeGL() {
    qglClearColor(Qt::red);
    glEnable(GL_DEPTH_TEST);
}

void CustomGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
