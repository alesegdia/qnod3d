#ifndef NODE_H
#define NODE_H

#include <QVector2D>

class Node
{
public:
    Node(int x, int y, int w, int h);

    Node(QVector2D size, QVector2D position);

    QMatrix4x4 getModelMatrix();

    QVector2D m_size;
    QVector2D m_position;
};


#endif // NODE_H
