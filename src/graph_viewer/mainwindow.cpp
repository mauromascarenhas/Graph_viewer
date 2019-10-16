#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lwEdges->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->lwNodes->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->sbBCRed->findChild<QLineEdit *>()->setReadOnly(true);
    ui->sbBCBlue->findChild<QLineEdit *>()->setReadOnly(true);
    ui->sbBCGreen->findChild<QLineEdit *>()->setReadOnly(true);

    connect(ui->btCreateEdge, &QPushButton::clicked, [this]{
        QStringList aNodes;
        for (GraphNode *node: graph.nodes())
            aNodes << node->name();

        edgeEditor.clear();
        edgeEditor.setAvailableNodes(aNodes);
        edgeEditor.show();
    });

    connect(ui->btDeleteEdge, &QPushButton::clicked, this, &MainWindow::removeEdge);

    connect(ui->btCreateNode, &QPushButton::clicked, [this]{
        nodeEditor.clear();
        nodeEditor.show();
    });

    connect(ui->btDeleteNode, &QPushButton::clicked, this, &MainWindow::removeNode);

    connect(&nodeEditor, &NodeAttributes::nodeAdded, [this](GraphNode *node){
        if (graph.addNode(node)){
            ui->lwNodes->addItem(node->view());
            ui->btDeleteNode->setEnabled(true);
            nodeEditor.close();
        }
        else delete node;
    });

    connect(&edgeEditor, &EdgeAttributes::edgeAdded, [this](GraphEdge *edge){
        if (graph.addEdge(edge)){
            ui->lwEdges->addItem(edge->view());
            ui->btDeleteEdge->setEnabled(true);
            edgeEditor.close();
        }
        else delete edge;
    });

    connect(&nodeEditor, &NodeAttributes::nodeEdited, [this](GraphNode *node, const GraphNode &newValues){
        if (graph.updateNode(node, newValues)) nodeEditor.close();
        //TODO: Add else with warning!
    });

    connect(&edgeEditor, &EdgeAttributes::edgeEdited, [this](GraphEdge *edge, const GraphEdge &newValues){
        if (graph.updateEdge(edge, newValues)) edgeEditor.close();
        //TODO: Add else with warning!
    });

    connect(ui->lwEdges, &QListWidget::customContextMenuRequested, [this](const QPoint &p){
        QPoint globalPos = ui->lwEdges->mapToGlobal(p);

        QMenu cMenu;
        cMenu.addAction(tr("Edit edge"), this, &MainWindow::editEdge);
        cMenu.addAction(tr("Remove edge"), this, &MainWindow::removeEdge);
        cMenu.exec(globalPos);
    });

    connect(ui->lwNodes, &QListWidget::customContextMenuRequested, [this](const QPoint &p){
        QPoint globalPos = ui->lwNodes->mapToGlobal(p);

        QMenu cMenu;
        cMenu.addAction(tr("Edit node"), this, &MainWindow::editNode);
        cMenu.addAction(tr("Remove node"), this, &MainWindow::removeNode);
        cMenu.exec(globalPos);
    });

    connect(ui->sbScale, &QSlider::valueChanged, [this](int value){ ui->graphViewer->setViewScale(0.01f * value); });

    connect(ui->hsBCRed, &QSlider::valueChanged, ui->sbBCRed, &QSpinBox::setValue);
    connect(ui->hsBCBlue, &QSlider::valueChanged, ui->sbBCBlue, &QSpinBox::setValue);
    connect(ui->hsBCGreen, &QSlider::valueChanged, ui->sbBCGreen, &QSpinBox::setValue);

    connect(ui->hsBCRed, &QSlider::valueChanged, this, &MainWindow::bgColourChanged);
    connect(ui->hsBCBlue, &QSlider::valueChanged, this, &MainWindow::bgColourChanged);
    connect(ui->hsBCGreen, &QSlider::valueChanged, this, &MainWindow::bgColourChanged);

    connect(ui->sbBCRed, QOverload<int>::of(&QSpinBox::valueChanged), ui->hsBCRed, &QSlider::setValue);
    connect(ui->sbBCBlue, QOverload<int>::of(&QSpinBox::valueChanged), ui->hsBCBlue, &QSlider::setValue);
    connect(ui->sbBCGreen, QOverload<int>::of(&QSpinBox::valueChanged), ui->hsBCGreen, &QSlider::setValue);

    connect(ui->cbToolMode, QOverload<int>::of(&QComboBox::currentIndexChanged), ui->swTools, &QStackedWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bgColourChanged(){
    ui->graphViewer->setBackgroundColour(ui->sbBCRed->value() * 0.00393f,
                                         ui->sbBCGreen->value() * 0.00393f,
                                         ui->sbBCBlue->value() * 0.00393f, 0);
}

void MainWindow::editEdge(){
    if (ui->lwEdges->currentRow() > -1){
        QStringList aNodes;
        for (GraphNode *node: graph.nodes())
            aNodes << node->name();

        edgeEditor.clear();
        edgeEditor.setAvailableNodes(aNodes);
        edgeEditor.setEditEdge(graph.edge(ui->lwEdges->currentItem()->text()));
        edgeEditor.show();
    }
}

void MainWindow::editNode(){
    if (ui->lwNodes->currentRow() > -1){
        nodeEditor.setEditNode(graph.nodes().at(ui->lwNodes->currentRow()));
        nodeEditor.show();
    }
}

void MainWindow::removeEdge(){
    if (ui->lwEdges->currentRow() > -1
            && QMessageBox::question(nullptr, tr("Confirmation"),
                                     tr("Are you sure you want to remove this edge ('%1')?").arg(ui->lwEdges->currentItem()->text()),
                                     QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
        delete graph.removeEdge(ui->lwEdges->currentItem()->text());
        ui->btDeleteEdge->setEnabled(ui->lwEdges->count());
    }
}

void MainWindow::removeNode(){
    if (ui->lwNodes->currentRow() > -1
            && QMessageBox::question(nullptr, tr("Confirmation"),
                                     tr("Are you sure you want to remove this vertex ('%1')?").arg(ui->lwNodes->currentItem()->text()),
                                     QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
        graph.removeNode(ui->lwNodes->currentItem()->text());
        ui->btDeleteNode->setEnabled(ui->lwNodes->count());
        ui->btDeleteEdge->setEnabled(ui->lwEdges->count());
    }
}
