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

    edit = nullptr;
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

void EdgeAttributes::setEditEdge(GraphEdge *edge){
    edit = edge;
    ui->edtDesc->setText(edge->desc());
    ui->cbNodeB->setCurrentText(edge->secondNodeName());
    ui->cbNodeA->setCurrentText(edge->firstNodeName());
    ui->sbWeight->setValue(edge->weight());

    selColour = edge->colour();
    ui->btColourChooser->setStyleSheet(QString("background: rgb(%1, %2, %3);")
                                              .arg(selColour.red()).arg(selColour.green()).arg(selColour.blue()));
}

void EdgeAttributes::clear(){
    ui->edtDesc->setText("");
    ui->cbNodeB->clear();
    ui->cbNodeA->clear();
    ui->cbNodeA->addItem("-");
    ui->sbWeight->setValue(0);
}

void EdgeAttributes::trySave(){
    if (edit){
        GraphEdge edge(ui->cbNodeA->currentText(), ui->cbNodeB->currentText());
        edge.setDesc(ui->edtDesc->text());
        edge.setWeight(ui->sbWeight->value());
        edge.setColour(selColour);
        emit edgeEdited();
    }

    GraphEdge *edge = new GraphEdge(ui->cbNodeA->currentText(), ui->cbNodeB->currentText());
    edge->setDesc(ui->edtDesc->text());
    edge->setWeight(ui->sbWeight->value());
    edge->setColour(selColour);
    emit edgeAdded(edge);
}

void EdgeAttributes::closeEvent(QCloseEvent *evnt){
    if (edit) edit = nullptr;
    QMainWindow::closeEvent(evnt);
}
