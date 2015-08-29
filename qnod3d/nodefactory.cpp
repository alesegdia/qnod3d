#include "nodefactory.h"

#include "node.h"

NodeFactory::NodeFactory() {}

NodeFactory::~NodeFactory() {
    for( QList<Node*>::iterator it = m_nodeList.begin(); it != m_nodeList.end(); it++) {
        Node* n = *it;
        delete n;
    }
}

Node *NodeFactory::makeNode(int x, int y, int w, int h) {
    Node* n = new Node(x,y,w,h);
    m_nodeList.append(n);
    return n;
}

QList<QMatrix4x4> &&NodeFactory::collectModels() {
    QList<QMatrix4x4> models;
    for( QList<Node*>::iterator it = m_nodeList.begin(); it != m_nodeList.end(); it++) {
        models.append((*it)->getModelMatrix());
    }
    return std::move(models);
}
