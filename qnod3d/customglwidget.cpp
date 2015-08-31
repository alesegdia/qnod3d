#include "customglwidget.h"

#include <QMouseEvent>
#include <QtGlobal>

#include "node.h"
#include "scenetransformtool.h"

CustomGLWidget::CustomGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_texture(0),
    m_geometries(0)
{
    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setDepthBufferSize(24);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    currentTool = new SceneTransformTool( m_sceneTransform );
    m_nodeFactory.makeNode( -3, -4,  0,  0 );
    m_nodeFactory.makeNode( -3,  4,  0,  0 );
    m_nodeFactory.makeNode(  3, -4,  0,  0 );
    m_nodeFactory.makeNode(  3,  4,  0,  0 );

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

void CustomGLWidget::paintGL()
{
    QMatrix4x4 matrix;
    matrix.translate(m_sceneTransform.m_position.x(), m_sceneTransform.m_position.y(), m_sceneTransform.m_position.z());
    matrix.rotate(m_sceneTransform.m_rotation_x);
    matrix.rotate(m_sceneTransform.m_rotation_y);
    matrix.scale(m_sceneTransform.m_scale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_texture->bind();

    m_program.setUniformValue("projectionMatrix", m_projection);
    m_program.setUniformValue("viewMatrix", matrix);
    m_program.setUniformValue("texture", 0);
    m_program.setUniformValue("node_size", m_nodeSize);
    m_program.bind();

    m_geometries->beginBatch();
    for( Node* n : m_nodeFactory )
    {
        m_geometries->drawNodeGeometry(n);
    }
    m_geometries->endBatch();
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
    currentTool->mousePressEvent(e);
}

void CustomGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    currentTool->mouseMoveEvent(e);
    update();
}

void CustomGLWidget::mouseReleaseEvent(QMouseEvent* e)
{
    currentTool->mousePressEvent(e);
}
