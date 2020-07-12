#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkRegExp(QRegExp rx)
{
    if(rx.isValid() && !rx.isEmpty() && !rx.exactMatch("")){
        return true;
    }else{
        QMessageBox::information(this,
                                 "Информсообщение",
                                 trUtf8("Некорректный шаблон регулярного выражения!"));
        return false;
    }
}

void MainWindow::on_actionOpenFile_triggered()
{
    QMessageBox::information(this,
                             "Информсообщение",
                             trUtf8("Некорректный шаблон регулярного выражения!"));
}
