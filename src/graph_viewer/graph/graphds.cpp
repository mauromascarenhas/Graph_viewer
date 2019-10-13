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
