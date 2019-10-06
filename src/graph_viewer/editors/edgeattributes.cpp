#include "edgeattributes.h"
#include "ui_edgeattributes.h"

EdgeAttributes::EdgeAttributes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EdgeAttributes)
{
    ui->setupUi(this);
}

EdgeAttributes::~EdgeAttributes()
{
    delete ui;
}
