#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

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

void MainWindow::search_and_show()
{
        QRegExp rx(ui->edtPattern->text());
        QStringList list;

        //Ищем ютубовскую ссылку
        int pos = 0;
        int i = 0;
        while ((pos = rx.indexIn(str, pos)) != -1) {
            i++;
            pos += rx.matchedLength();
            list << QString::number(i) + ": " + rx.cap(0);
        }

        ui->lstWindow->addItems(list);
}


void MainWindow::on_btnEmail_clicked()
{
    QString pattern = "[a-zA-Z0-9-_]{11}";
    ui->edtPattern->setText(pattern);
    search_and_show();
}

void MainWindow::on_btnLink_clicked()
{
    QString pattern = "http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?";
    ui->edtPattern->setText(pattern);
    search_and_show();
}


void MainWindow::on_btnSearch_clicked()
{
    search_and_show();
}

void MainWindow::on_btnClear_clicked()
{
    ui->lstWindow->clear();
}


void MainWindow::on_lstWindow_doubleClicked(const QModelIndex &index)
{
    QString pattern = "http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?";
    QRegExp rx(pattern);
    QString link;

     int pos = 0;
    QString tmp = ui->lstWindow->item(index.row())->text();
    while ((pos = rx.indexIn(tmp, pos)) != -1) {
        pos += rx.matchedLength();
        link = rx.cap(0);
    }

    if (link == "") return;
    else {
        QDesktopServices::openUrl(QUrl(link));
    }
}
