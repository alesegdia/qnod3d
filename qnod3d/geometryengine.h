#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(QOpenGLShaderProgram *program);
    virtual ~GeometryEngine();

    void drawNodeGeometry();

private:
    void initNodeGeometry(QOpenGLShaderProgram *program);

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLVertexArrayObject* m_vao;

};

#endif // GEOMETRYENGINE_H
