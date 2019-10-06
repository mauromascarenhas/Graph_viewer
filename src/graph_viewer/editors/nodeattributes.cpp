#include "nodeattributes.h"
#include "ui_nodeattributes.h"

NodeAttributes::NodeAttributes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NodeAttributes)
{
    ui->setupUi(this);

    connect(ui->btChooseColour, &QPushButton::clicked, [this]{
        cDlg.show();

        connect(&cDlg, &QColorDialog::colorSelected, [=](const QColor &colour){
           ui->btChooseColour->setStyleSheet(QString("background: rgb(%1, %2, %3);")
                                                     .arg(colour.red()).arg(colour.green()).arg(colour.blue()));
        });
    });
}

NodeAttributes::~NodeAttributes()
{
    delete ui;
}
