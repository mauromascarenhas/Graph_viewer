#ifndef EDGEATTRIBUTES_H
#define EDGEATTRIBUTES_H

#include <QMainWindow>
#include <QColorDialog>
#include <QListWidgetItem>

#include "graphedge.h"

namespace Ui {
class EdgeAttributes;
}

class EdgeAttributes : public QMainWindow
{
    Q_OBJECT

public:
    explicit EdgeAttributes(QWidget *parent = nullptr);
    ~EdgeAttributes();

    void setAvailableNodes(const QStringList &nodes);

public slots:
    void clear();
    void trySave();

private:
    Ui::EdgeAttributes *ui;

    QColor selColour;
    QColorDialog cDlg;

signals:
    void edgeAdded(GraphEdge *edge);
    //TODO: Include old relation and new attribs
    void edgeUpdated();
};

#endif // EDGEATTRIBUTES_H
