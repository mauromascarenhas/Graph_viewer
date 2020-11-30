#include "graphnode.h"

GraphNode::GraphNode(QOpenGLWidget *view, const QString &name)
{
    this->l_view = new QListWidgetItem(name);

    this->nodeName = name;
    this->nodeWeight = 0;

    this->attObj = view ? new GraphObject(view , GraphObject::SPHERE) : nullptr;
}

GraphNode::~GraphNode(){
    if (l_view){
        delete l_view;
        l_view = nullptr;
    }

    if (attObj){
        delete attObj;
        attObj = nullptr;
    }
}
