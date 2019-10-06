#ifndef EDGEATTRIBUTES_H
#define EDGEATTRIBUTES_H

#include <QMainWindow>

namespace Ui {
class EdgeAttributes;
}

class EdgeAttributes : public QMainWindow
{
    Q_OBJECT

public:
    explicit EdgeAttributes(QWidget *parent = nullptr);
    ~EdgeAttributes();

private:
    Ui::EdgeAttributes *ui;
};

#endif // EDGEATTRIBUTES_H
