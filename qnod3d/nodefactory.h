#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QVector2D>
#include <QMatrix4x4>
#include <QList>

class Node;

class NodeFactory
{

public:

    NodeFactory();
    ~NodeFactory();

    Node* makeNode( int x, int y, int w, int h );

    QList<QMatrix4x4>&& collectModels();

private:

    QList<Node*> m_nodeList;
};

#endif // NODEFACTORY_H
