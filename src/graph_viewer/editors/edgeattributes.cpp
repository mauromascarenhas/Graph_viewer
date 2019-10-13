#include "edgeattributes.h"
#include "ui_edgeattributes.h"

EdgeAttributes::EdgeAttributes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EdgeAttributes)
{
    ui->setupUi(this);

    connect(ui->cbNodeA, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){
        ui->cbNodeB->setEnabled(index);
        ui->cbNodeB->clear();
        if (!index) return;

        for (int i = 1; i < ui->cbNodeA->count(); ++i)
            if (i != index) ui->cbNodeB->addItem(ui->cbNodeA->itemText(i));
    });

    connect(ui->btColourChooser, &QPushButton::clicked, [this]{
        cDlg.show();
    });

    connect(&cDlg, &QColorDialog::colorSelected, [=](const QColor &colour){
       ui->btColourChooser->setStyleSheet(QString("background: rgb(%1, %2, %3);")
                                                 .arg(colour.red()).arg(colour.green()).arg(colour.blue()));
       selColour = colour;
    });

    connect(ui->btSave, &QPushButton::clicked, this, &EdgeAttributes::trySave);
}

EdgeAttributes::~EdgeAttributes()
{
    delete ui;
}

void EdgeAttributes::setAvailableNodes(const QStringList &nodes){
    ui->cbNodeA->clear();
    ui->cbNodeA->addItem("-");
    ui->cbNodeA->addItems(nodes);
}

void EdgeAttributes::clear(){
    ui->edtDesc->setText("");
    ui->cbNodeB->clear();
    ui->cbNodeA->clear();
    ui->cbNodeA->addItem("-");
    ui->sbWeight->setValue(0);
}

void EdgeAttributes::trySave(){
    GraphEdge *edge = new GraphEdge(ui->cbNodeA->currentText(), ui->cbNodeB->currentText());
    edge->setDesc(ui->edtDesc->text());
    edge->setWeight(ui->sbWeight->value());
    edge->setColour(selColour);
    emit edgeAdded(edge);
}
