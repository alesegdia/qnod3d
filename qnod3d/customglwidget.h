#ifndef CUSTOMGLWIDGET_H
#define CUSTOMGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QQuaternion>
#include <QOpenGLFunctions_3_3_Core>

#include "geometryengine.h"
#include "nodefactory.h"
#include "scenetransform.h"
#include "itool.h"


class CustomGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit CustomGLWidget(QWidget *parent = 0);
    ~CustomGLWidget();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

    void initShaders();
    void initTextures();

private:

    QOpenGLShaderProgram m_program;
    QOpenGLTexture *m_texture;
    QOpenGLFunctions_3_3_Core *m_gl330;

    NodeFactory m_nodeFactory;

    ITool* currentTool;

    // node geometry
    GeometryEngine *m_geometries;
    QVector2D m_nodeSize = QVector2D(2,3);

    // camera transform
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;

    SceneTransform m_sceneTransform;

};

#endif // CUSTOMGLWIDGET_H
