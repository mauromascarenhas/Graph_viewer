#include "graphedge.h"

GraphEdge::GraphEdge(QOpenGLWidget *view, const QString &firstNode, const QString &secondNode)
{
    this->l_view = new QListWidgetItem(firstNode + " <---> " + secondNode);

    this->node1Name = firstNode;
    this->node2Name = secondNode;

    this->edgeWeight = 0;

    this->attObj = view ? new GraphObject(view , GraphObject::CYLINDER) : nullptr;
}

GraphEdge::~GraphEdge(){
    if (l_view){
        delete l_view;
        l_view = nullptr;
    }

    if (attObj){
        delete attObj;
        attObj = nullptr;
    }
}
