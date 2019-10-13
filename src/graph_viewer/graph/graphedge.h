#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QString>
#include <QListWidgetItem>

#include "graphnode.h"

class GraphEdge
{
public:
    explicit GraphEdge(const QString &firstNode = "", const QString &secondNode= "");
    ~GraphEdge();

    inline void setFirstNode(const QString &nodeName) { this->node1Name = nodeName; }
    inline void setSecondNode(const QString &nodeName) { this->node2Name = nodeName; }

    inline void setDesc(const QString &desc) {
        if (this->l_view) this->l_view->setToolTip(desc);
        this->edgeDesc = desc;
    }
    inline void setColour(const QColor &colour) { this->edgeColour = colour; }
    inline void setWeight(unsigned short weight) { this->edgeWeight = weight; }

    inline QString label() const { return node1Name + " <---> " + node2Name; }
    inline QString firstNodeName() const { return node1Name; }
    inline QString secondNodeName() const { return node2Name; }

    inline QString desc() const { return this->edgeDesc; }
    inline QColor colour() const { return this->edgeColour; }
    inline unsigned short weight() const { return this->edgeWeight; }

    inline QListWidgetItem *view() { return this->l_view; }

private:
    QString node1Name;
    QString node2Name;
    QString edgeDesc;

    QColor edgeColour;

    unsigned short edgeWeight;

    QListWidgetItem *l_view;
};

#endif // GRAPHEDGE_H
