#ifndef GRAPHDS_H
#define GRAPHDS_H

#include <QHash>
#include <QObject>
#include <QOpenGLWidget>

#include "graphedge.h"
#include "graphnode.h"

class GraphDS : public QObject
{
    Q_OBJECT
public:
    explicit GraphDS(QObject *parent = nullptr);
    ~GraphDS();

    bool addNode(GraphNode *node);
    bool addEdge(GraphEdge *edge);

    bool updateNode(GraphNode *node, const GraphNode &newValues);
    bool updateEdge(GraphEdge *edge, const GraphEdge &newVal);

    bool removeNode(const QString &name);

    GraphEdge * removeEdge(const QString &label);
    GraphEdge * removeEdge(const GraphEdge &edge);
    bool removeEdges(const QString &nodeName);

    GraphEdge * edge(const QString &label) { return this->g_edges.value(label); }

    QList<GraphNode*> nodes() { return this->g_nodes; }
    QList<GraphEdge*> edges() { return this->g_edges.values(); }

private:
    QList<GraphNode*> g_nodes;
    QHash<QString, GraphEdge*> g_edges;
};

#endif // GRAPHDS_H
