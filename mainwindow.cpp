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

int MainWindow::defineCounts(QString filename)
{
    int countLines = 0;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);

    for(int i = 0; i < 10000; i++){
        QByteArray arr = file.readLine();
        if(QString::fromUtf8(arr) != ""){
        countLines++;
        } else {
            break;
        }
    }

    file.close();
    return countLines + 1;
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
    QFileDialog dialog;
//    QFile f(dialog.getOpenFileName());
    QFile f("bookmarks_12.07.2020.html");
    if(f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        str = stream.readAll();
        ui->edtText->setText(str);
    }
}

void MainWindow::search_and_show(QString pattern)
{
    QRegExp rx(pattern);
    QStringList list;

    //Ищем ютубовскую ссылку
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        pos += rx.matchedLength();
        list << rx.cap(0);
    }

    ui->lstWindow->addItems(list);
}

void MainWindow::on_btnEmail_clicked()
{
    search_and_show("[a-zA-Z0-9-_]{11}");
}

void MainWindow::on_btnLink_clicked()
{
    //search_and_show("http(s)?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?");
    QRegExp rx("http(s)?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?");
    QStringList list;

    //Ищем ютубовскую ссылку
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        pos += rx.matchedLength();
        list << rx.cap(0);
    }

    ui->lstWindow->addItems(list);
}

void MainWindow::on_edtPattern_editingFinished()
{
    QRegExp rx(ui->edtPattern->text());
    QStringList list;

    //Ищем ютубовскую ссылку
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        pos += rx.matchedLength();
        list << rx.cap(0);
    }

    ui->lstWindow->addItems(list);
}

void MainWindow::on_btnSearch_clicked()
{
    QRegExp rx(ui->edtPattern->text());
    QStringList list;

    //Ищем ютубовскую ссылку
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        pos += rx.matchedLength();
        list << rx.cap(0);
    }

    ui->lstWindow->addItems(list);
}

void MainWindow::on_btnClear_clicked()
{
    ui->lstWindow->clear();
}




