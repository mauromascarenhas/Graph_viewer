#include "nodeattributes.h"
#include "ui_nodeattributes.h"

NodeAttributes::NodeAttributes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NodeAttributes)
{
    ui->setupUi(this);
    edit = nullptr;

    connect(ui->btChooseColour, &QPushButton::clicked, [this]{
        cDlg.show();
    });

    connect(&cDlg, &QColorDialog::colorSelected, [=](const QColor &colour){
       ui->btChooseColour->setStyleSheet(QString("background: rgb(%1, %2, %3);")
                                                 .arg(colour.red()).arg(colour.green()).arg(colour.blue()));
       selColour = colour;
    });

    connect(ui->btSave, &QPushButton::clicked, this, &NodeAttributes::trySave);
}

NodeAttributes::~NodeAttributes()
{
    delete ui;
}

void NodeAttributes::setEditNode(GraphNode *node){
    edit = node;
    ui->edtName->setText(node->name());
    ui->edtDescription->setText(node->desc());
    ui->sbWeight->setValue(node->weight());
    ui->btPosX->setValue(node->pos().x());
    ui->btPosY->setValue(node->pos().y());
    ui->btPosZ->setValue(node->pos().z());

    selColour = node->colour();
    ui->btChooseColour->setStyleSheet(QString("background: rgb(%1, %2, %3);")
                                              .arg(selColour.red()).arg(selColour.green()).arg(selColour.blue()));
}

void NodeAttributes::clear(){
    ui->edtName->setText("");
    ui->edtDescription->setText("");
    ui->sbWeight->setValue(0);
    ui->btPosX->setValue(0.0);
    ui->btPosY->setValue(0.0);
    ui->btPosZ->setValue(0.0);
}

void NodeAttributes::trySave(){
    if (edit){
        GraphNode node(nullptr, ui->edtName->text());
        node.setDesc(ui->edtDescription->text());
        node.setPos(QVector4D(ui->btPosX->value(), ui->btPosY->value(), ui->btPosZ->value(), 1));
        node.setWeight(ui->sbWeight->value());
        node.setColour(selColour);
        emit nodeEdited(edit, node);
        return;
    }

    QRegularExpressionMatch match;
    if ((match = QRegularExpression(QStringLiteral(u"[^\\p{L}\\d\\s\\-\\_]+")).match(ui->edtName->text())).hasMatch()){
        QMessageBox::warning(nullptr, tr("Warning"), tr("Forbidden elements detected: '%1'.").arg(match.captured()),
                             QMessageBox::Ok);
        ui->edtName->setFocus();
        return;
    }

    GraphNode *node = new GraphNode(static_cast<QOpenGLWidget*>(parentWidget()), ui->edtName->text());
    node->setDesc(ui->edtDescription->text());
    node->setPos(QVector4D(ui->btPosX->value(), ui->btPosY->value(), ui->btPosZ->value(), 1));
    node->setWeight(ui->sbWeight->value());
    node->setColour(selColour);
    emit nodeAdded(node);
}

void NodeAttributes::closeEvent(QCloseEvent *evnt){
    if (edit) edit = nullptr;
    QMainWindow::closeEvent(evnt);
}
