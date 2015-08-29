#include "customglwidget.h"

#include <QMouseEvent>

CustomGLWidget::CustomGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_geometries(0),
    m_texture(0),
    m_position(0,0,-10.f)
{
    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setDepthBufferSize(24);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();
}

CustomGLWidget::~CustomGLWidget()
{
    makeCurrent();
    delete m_texture;
    delete m_geometries;
    doneCurrent();
}

void CustomGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    m_gl330 = context()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    glClearColor(0.0,0.0,0.0,1.0);
    initShaders();
    initTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_geometries = new GeometryEngine(&(this->m_program), m_gl330);

}

void CustomGLWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 50.0, fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void CustomGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_texture->bind();

    QMatrix4x4 matrix;
    matrix.translate(m_position.x(), m_position.y(), m_position.z());
    matrix.rotate(m_rotation_x);
    matrix.rotate(m_rotation_y);
    matrix.scale(m_scale);

    m_program.setUniformValue("projectionMatrix", m_projection);
    m_program.setUniformValue("viewMatrix", matrix);
    m_program.setUniformValue("texture", 0);
    m_program.setUniformValue("node_size", m_nodeSize);
    m_program.bind();
    m_geometries->drawNodeGeometry();
}

void CustomGLWidget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vshader.glsl"))
    {
        close();
    }
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fshader.glsl"))
    {
        close();
    }
    if (!m_program.link())
    {
        close();
    }
    if (!m_program.bind())
    {
        close();
    }
}

void CustomGLWidget::initTextures()
{
    m_texture = new QOpenGLTexture(QImage(":/images/cubetex.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void CustomGLWidget::mousePressEvent(QMouseEvent* e)
{
    m_pressed = true;
    if( e->button() == Qt::MouseButton::RightButton ) {
        toolMode = ToolMode::SCN_SCALE;
    } else if( e->button() == Qt::MouseButton::LeftButton ) {
        toolMode = ToolMode::SCN_TRANSLATE;
    } else if( e->button() == Qt::MouseButton::MidButton ) {
        toolMode = ToolMode::SCN_ROTATE;
    }
    m_mousePressPosition = QVector2D(e->localPos());
}

void CustomGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if( m_pressed ) {
        QPointF mousePos = e->localPos();
        QVector2D d = QVector2D(mousePos) - m_mousePressPosition;
        d.setY(-d.y());
        switch( toolMode ) {
        case ToolMode::SCN_ROTATE:
            m_rotation_x *= QQuaternion::fromEulerAngles(QVector3D(0.f,(mousePos.x()-m_mousePressPosition.x()),0.f));
            m_rotation_y *= QQuaternion::fromEulerAngles(QVector3D((mousePos.y()-m_mousePressPosition.y()),0.f,0.f));
            break;
        case ToolMode::SCN_TRANSLATE:
            mousePos.setY(-mousePos.y());
            d.setY(d.y());
            m_position += d/40;
            break;
        case ToolMode::SCN_SCALE:
            m_scale += (e->localPos().y() - m_mousePressPosition.y())/1000.f;
            break;
        }

        m_mousePressPosition = QVector2D(e->localPos());
        update();
    }
}

void CustomGLWidget::mouseReleaseEvent(QMouseEvent* e)
{
    m_pressed = false;
}
