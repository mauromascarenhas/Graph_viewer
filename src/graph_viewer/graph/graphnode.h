#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QColor>
#include <QString>
#include <QVector4D>
#include <QListWidgetItem>

class GraphNode
{
public:
    explicit GraphNode(const QString &name = "");
    ~GraphNode();

    inline void setPos(const QVector4D &pos) { this->nodePos = pos; }
    inline void setName(const QString &name) {
        this->nodeName = name;
        if (this->l_view) this->l_view->setText(name);
    }
    inline void setDesc(const QString &desc) {
        if (this->l_view) this->l_view->setToolTip(desc);
        this->nodeDesc = desc;
    }
    inline void setColour(const QColor &colour) { this->nodeColour = colour; }
    inline void setWeight(unsigned short weight) { this->nodeWeight = weight; }

    inline QVector4D pos() const { return this->nodePos; }
    inline QString name() const { return this->nodeName; }
    inline QString desc() const { return this->nodeDesc; }
    inline QColor colour() const { return this->nodeColour; }
    inline unsigned short weight() const { return this->nodeWeight; }

    inline QListWidgetItem *view() { return this->l_view; }

    inline bool operator == (const GraphNode &other) {
        return this->nodeName == other.nodeName &&
                this->nodeDesc == other.nodeDesc &&
                this->nodePos == other.nodePos &&
                this->nodeColour == other.nodeColour &&
                this->nodeWeight == other.nodeWeight;
    }

private:
    QString nodeName;
    QString nodeDesc;
    QVector4D nodePos;

    QColor nodeColour;

    unsigned short nodeWeight;

    QListWidgetItem *l_view;
};

#endif // GRAPHNODE_H
