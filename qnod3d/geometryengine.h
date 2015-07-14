#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(QOpenGLShaderProgram *program, QOpenGLFunctions_3_3_Core *gl330);
    virtual ~GeometryEngine();

    void drawNodeGeometry();

private:
    void initNodeGeometry(QOpenGLShaderProgram *program);

    QOpenGLBuffer m_arrayBuf;
    QOpenGLBuffer m_indexBuf;
    QOpenGLBuffer m_modelsBuffer;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLFunctions_3_3_Core* m_gl330;


};

#endif // GEOMETRYENGINE_H
