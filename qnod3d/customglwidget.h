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

enum ToolMode {
    SCN_TRANSLATE,
    SCN_ROTATE,
    SCN_SCALE
};

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

    // node geometry
    GeometryEngine *m_geometries;
    QVector2D m_nodeSize = QVector2D(2,3);

    // camera transform
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;

    SceneTransform cam;

    // tool objects
    bool m_pressed = false;
    QVector2D m_mousePressPosition;
    ToolMode m_toolMode;

};

#endif // CUSTOMGLWIDGET_H
