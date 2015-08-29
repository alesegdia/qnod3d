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
    GeometryEngine *m_geometries;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QOpenGLTexture *m_texture;
    QQuaternion m_rotation_x;
    QQuaternion m_rotation_y;
    QVector3D m_position;

    float m_scale = 1;
    bool m_pressed = false;
    QVector2D m_mousePressPosition;
    QVector2D m_nodeSize = QVector2D(2,3);

    QOpenGLFunctions_3_3_Core *m_gl330;
    ToolMode toolMode;

public slots:
    void setTranslateSceneMode(bool k) {
        toolMode = ToolMode::SCN_TRANSLATE;
    }

    void setRotateSceneMode(bool k) {
        toolMode = ToolMode::SCN_ROTATE;
    }

    void setScaleSceneMode(bool k) {
        toolMode = ToolMode::SCN_SCALE;
    }


};

#endif // CUSTOMGLWIDGET_H
