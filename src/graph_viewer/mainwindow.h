#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphds.h"
#include "edgeattributes.h"
#include "nodeattributes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

   EdgeAttributes edgeEditor;
   NodeAttributes nodeEditor;

   GraphDS graph;

private slots:
    void bgColourChanged();
};
#endif // MAINWINDOW_H

