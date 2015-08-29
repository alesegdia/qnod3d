#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>

#include <QBuffer>

class Node;

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(QOpenGLShaderProgram *program, QOpenGLFunctions_3_3_Core *gl330);
    virtual ~GeometryEngine();

    void beginBatch();
    void drawNodeGeometry(Node *n);
    void endBatch();

private:
    void initNodeGeometry(QOpenGLShaderProgram *program);

    QOpenGLBuffer m_indexBuf;
    QOpenGLBuffer m_arrayBuf;
    QOpenGLBuffer m_gpuModelsBuffer;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLFunctions_3_3_Core* m_gl330;

    QBuffer m_modelsBuffer;
    int m_numNodesToRender;

};

#endif // GEOMETRYENGINE_H
