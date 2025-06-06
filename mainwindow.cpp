#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    importer = new ImportHandler(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete importer;
}


