#include "customglwidget.h"

#include <QMouseEvent>

CustomGLWidget::CustomGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_geometries(0),
    m_texture(0)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);
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
    glClearColor(0.0,0.0,0.0,1.0);
    initShaders();
    initTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_geometries = new GeometryEngine(&(this->m_program));

}

void CustomGLWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 20.0, fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void CustomGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_texture->bind();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    matrix.rotate(m_rotation);
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);
    m_program.setUniformValue("texture", 0);
    m_program.setUniformValue("node_size", m_nodeSize);
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
    m_mousePressPosition = QVector2D(e->localPos());
}

void CustomGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if( m_pressed ) {
        QPointF mousePos = e->localPos();
        m_rotation = m_rotation.fromEulerAngles(QVector3D(-mousePos.y(),mousePos.x(),0.f));
        update();
    }
}

void CustomGLWidget::mouseReleaseEvent(QMouseEvent* e)
{
    m_pressed = false;
}
