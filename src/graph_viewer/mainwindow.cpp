#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbBCRed->findChild<QLineEdit *>()->setReadOnly(true);
    ui->sbBCBlue->findChild<QLineEdit *>()->setReadOnly(true);
    ui->sbBCGreen->findChild<QLineEdit *>()->setReadOnly(true);

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

