#ifndef NODEATTRIBUTES_H
#define NODEATTRIBUTES_H

#include <QColor>
#include <QMainWindow>
#include <QColorDialog>

namespace Ui {
class NodeAttributes;
}

class NodeAttributes : public QMainWindow
{
    Q_OBJECT

public:
    explicit NodeAttributes(QWidget *parent = nullptr);
    ~NodeAttributes();

private:
    Ui::NodeAttributes *ui;

    QColorDialog cDlg;
};

#endif // NODEATTRIBUTES_H
