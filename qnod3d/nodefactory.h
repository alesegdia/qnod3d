#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QVector2D>
#include <QMatrix4x4>
#include <QList>

class Node
{
public:
    Node(int x, int y, int w, int h)
        : m_size(x,y), m_position(w,h)
    {}

    Node(QVector2D size, QVector2D position)
        : m_size(size), m_position(position)
    {}

    QMatrix4x4 getModelMatrix()
    {
        QMatrix4x4 model;
        model.translate( m_position.x(), m_position.y(), 0.0 );
        return model;
    }

    QVector2D m_size;
    QVector2D m_position;
};

class NodeFactory
{
public:
    NodeFactory() {}
    ~NodeFactory() {
        for( QList<Node*>::iterator it = m_nodeList.begin(); it != m_nodeList.end(); it++) {
            Node* n = *it;
            delete n;
        }
    }

    Node* makeNode( int x, int y, int w, int h ) {
        Node* n = new Node(x,y,w,h);
        m_nodeList.append(n);
        return n;
    }

    QList<QMatrix4x4>&& collectModels() {
        QList<QMatrix4x4> models;
        for( QList<Node*>::iterator it = m_nodeList.begin(); it != m_nodeList.end(); it++) {
            models.append((*it)->getModelMatrix());
        }
        return std::move(models);
    }

private:
    QList<Node*> m_nodeList;
};

#endif // NODEFACTORY_H
