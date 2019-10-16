#include "graphds.h"

GraphDS::GraphDS(QObject *parent) : QObject(parent)
{

}

GraphDS::~GraphDS(){

}

bool GraphDS::addNode(GraphNode *node){
    if (g_nodes.contains(node)) return false;
    g_nodes.append(node);
    return true;
}

bool GraphDS::addEdge(GraphEdge *edge){
    bool hasA = false, hasB = false;
    for (GraphNode *node : g_nodes)
        if (node->name() == edge->firstNodeName()) hasA = true;
        else if (node->name() == edge->secondNodeName()) hasB = true;

    if (g_edges.contains(edge->label()) || !hasA || !hasB) return false;
    g_edges.insert(edge->label(), edge);
    return true;
}

bool GraphDS::updateNode(GraphNode *node, const GraphNode &newValues){
    for (GraphNode *n : g_nodes)
        if (newValues.name() == n->name()) return false;

    for (GraphEdge *edge : g_edges){
        if (edge->label().startsWith(node->name())) edge->setFirstNode(newValues.name());
        else if (edge->label().endsWith(node->name())) edge->setSecondNode(newValues.name());
    }

    node->setName(newValues.name());
    node->setDesc(newValues.desc());
    node->setColour(newValues.colour());
    node->setWeight(newValues.weight());
    node->setPos(newValues.pos());

    return true;
}

bool GraphDS::updateEdge(GraphEdge *edge, const GraphEdge &newVal){
    if (g_edges.contains(newVal.label())) return false;

    edge->setDesc(newVal.desc());
    edge->setColour(newVal.colour());
    edge->setWeight(newVal.weight());
    edge->setFirstNode(newVal.firstNodeName());
    edge->setSecondNode(newVal.secondNodeName());
    return true;
}

bool GraphDS::removeNode(const QString &name){
    for (int i = 0; i < g_nodes.length(); ++i){
        if (g_nodes.at(i)->name() == name){
            this->removeEdges(name);
            delete g_nodes.takeAt(i);
            return true;
        }
    }
    return false;
}

GraphEdge * GraphDS::removeEdge(const QString &label){
    return g_edges.take(label);
}

GraphEdge *GraphDS::removeEdge(const GraphEdge &edge){
    return g_edges.take(edge.label());
}

bool GraphDS::removeEdges(const QString &nodeName){
    QStringList toRemove;

    for (QString key : g_edges.keys())
        if (key.endsWith(" <---> " + nodeName)
                || key.startsWith(nodeName + " <---> "))
            toRemove.append(key);
    if (toRemove.isEmpty()) return false;

    for (QString key : toRemove)
        delete g_edges.take(key);
    return true;
}
