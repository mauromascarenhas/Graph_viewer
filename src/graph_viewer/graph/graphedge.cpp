#include "graphedge.h"

GraphEdge::GraphEdge(const QString &firstNode, const QString &secondNode)
{
    this->l_view = new QListWidgetItem(firstNode + " <---> " + secondNode);

    this->node1Name = firstNode;
    this->node2Name = secondNode;

    this->edgeWeight = 0;
}

GraphEdge::~GraphEdge(){
    if (l_view){
        delete l_view;
        l_view = nullptr;
    }
}
