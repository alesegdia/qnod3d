#include "customglwidget.h"

CustomGLWidget::CustomGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void CustomGLWidget::initializeGL() {
    glClearColor(1.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
}

void CustomGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
