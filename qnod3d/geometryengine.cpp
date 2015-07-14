#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <QBuffer>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine(QOpenGLShaderProgram *program, QOpenGLFunctions_3_3_Core *gl330)
    : m_indexBuf(QOpenGLBuffer::IndexBuffer),
      m_arrayBuf(QOpenGLBuffer::VertexBuffer),
      m_modelsBuffer(QOpenGLBuffer::VertexBuffer)
{
    initializeOpenGLFunctions();

    this->m_gl330 = gl330;
    m_arrayBuf.create();
    m_indexBuf.create();
    m_modelsBuffer.create();

    initNodeGeometry(program);
}

GeometryEngine::~GeometryEngine()
{
    m_arrayBuf.destroy();
    m_indexBuf.destroy();
}
//! [0]

void GeometryEngine::initNodeGeometry(QOpenGLShaderProgram *program)
{
    float width = 0.125f;

    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  width), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  width), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  width), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  width), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  width), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -width), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  width), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -width), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -width), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -width), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -width), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -width), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -width), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  width), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -width), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  width), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -width), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -width), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  width), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  width), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  width), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  width), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -width), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -width), QVector2D(0.66f, 1.0f)}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    m_vao = new QOpenGLVertexArrayObject(0);
    m_vao->create();
    m_vao->bind();

    m_arrayBuf.bind();
    m_arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    m_indexBuf.bind();
    m_indexBuf.allocate(indices, 34 * sizeof(GLushort));

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    m_modelsBuffer.bind();

    int modelLocation = program->attributeLocation("a_modelMatrix");

    for( int i = 0; i < 4; i++ ) {
        program->enableAttributeArray( modelLocation + i );
        program->setAttributeBuffer( modelLocation + i, GL_FLOAT, i * sizeof(QVector4D), 4, 4 * sizeof(QVector4D) );
        m_gl330->glVertexAttribDivisor( modelLocation + i, 1 );
    }

    m_modelsBuffer.release();
    m_vao->release();
    program->release();
}

void GeometryEngine::drawNodeGeometry()
{
    m_vao->bind();
    m_modelsBuffer.bind();

    QBuffer buf;
    buf.open(QIODevice::WriteOnly);

    int m44size = 4 * sizeof(QVector4D);
    QMatrix4x4 m;

    m.setToIdentity();
    m.translate(-0.5,0,0);
    buf.write(((char*)m.constData()), m44size);

    m.setToIdentity();
    m.translate(0.5,0,0);
    buf.write(((char*)m.constData()), m44size);

    buf.close();

    m_modelsBuffer.allocate(buf.data().constData(), 4*sizeof(QVector4D)*2);
    m_gl330->glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 34, 2);

}
