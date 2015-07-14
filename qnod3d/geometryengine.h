#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawNodeGeometry(QOpenGLShaderProgram *program);

private:
    void initNodeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

};

#endif // GEOMETRYENGINE_H
