#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QVector2D>
#include <QList>

class Node
{
public:
    Node(int w, int h) : m_size(w,h) {}
    Node(QVector2D size) : m_size(size) {}
    QVector2D m_size;
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

    Node* makeNode( int w, int h ) {
        Node* n = new Node(w,h);
        m_nodeList.append(n);
        return n;
    }

private:
    QList<Node*> m_nodeList;
};

#endif // NODEFACTORY_H
