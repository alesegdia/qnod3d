#include "node.h"

Node::Node(int x, int y, int w, int h)
    : m_size(x,y), m_position(w,h)
{}


Node::Node(QVector2D size, QVector2D position)
    : m_size(size), m_position(position)
{}


QMatrix4x4 Node::getModelMatrix()
{
    QMatrix4x4 model;
    model.translate( m_position.x(), m_position.y(), 0.0 );
    return model;
}
