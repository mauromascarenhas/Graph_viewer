#ifndef NODEATTRIBUTES_H
#define NODEATTRIBUTES_H

#include <QColor>
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

public slots:
    void clear();
    void trySave();

private:
    Ui::NodeAttributes *ui;

    QColor selColour;
    QColorDialog cDlg;

signals:
    void nodeAdded(GraphNode *node);
    //TODO: Include old relation and new attribs
    void nodeUpdated();
};

#endif // NODEATTRIBUTES_H
