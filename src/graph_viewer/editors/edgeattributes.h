#ifndef EDGEATTRIBUTES_H
#define EDGEATTRIBUTES_H

#include <QCloseEvent>
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
    void setEditEdge(GraphEdge *edge);

public slots:
    void clear();
    void trySave();

private:
    Ui::EdgeAttributes *ui;

    QColor selColour;
    QColorDialog cDlg;

    GraphEdge *edit;

protected:
    void closeEvent(QCloseEvent *evnt);

signals:
    void edgeAdded(GraphEdge *edge);
    void edgeEdited(GraphEdge *edge, const GraphEdge &newValues);
};

#endif // EDGEATTRIBUTES_H
