#ifndef NODEATTRIBUTES_H
#define NODEATTRIBUTES_H

#include <QColor>
#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QColorDialog>
#include <QListWidgetItem>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "graphnode.h"

namespace Ui {
class NodeAttributes;
}

class NodeAttributes : public QMainWindow
{
    Q_OBJECT

public:
    explicit NodeAttributes(QWidget *parent = nullptr);
    ~NodeAttributes();

    void setEditNode(GraphNode *node);

public slots:
    void clear();
    void trySave();

protected:
    void closeEvent(QCloseEvent *evnt);

private:
    Ui::NodeAttributes *ui;

    QColor selColour;
    QColorDialog cDlg;

    GraphNode *edit;

signals:
    void nodeAdded(GraphNode *node);
    void nodeEdited(GraphNode *node, const GraphNode &newValues);
};

#endif // NODEATTRIBUTES_H
