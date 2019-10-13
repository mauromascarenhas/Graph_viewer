#include "graphnode.h"

GraphNode::GraphNode(const QString &name)
{
    this->l_view = new QListWidgetItem(name);

    this->nodeName = name;
    this->nodeWeight = 0;
}

GraphNode::~GraphNode(){
    if (l_view){
        delete l_view;
        l_view = nullptr;
    }
}
