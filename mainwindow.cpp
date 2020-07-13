#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QUrl>
#include <QClipboard>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("RegExp");

    label = new QLabel("");
    ui->statusBar->addWidget(label);

    setEnableFalseButtons();
    ui->edtPattern->setPlaceholderText("Регулярное выражение");

    networkManager = new QNetworkAccessManager();
    // Подключаем networkManager к обработчику ответа
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onResult(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEnableFalseButtons()
{
    ui->btnEmail->setEnabled(false);
    ui->btnLink->setEnabled(false);
    ui->btnSearch->setEnabled(false);
    ui->btnCopy->setEnabled(false);
}

void MainWindow::setEnableTrueButtons()
{
    ui->btnEmail->setEnabled(true);
    ui->btnLink->setEnabled(true);
    ui->btnSearch->setEnabled(true);
}


void MainWindow::onResult(QNetworkReply *reply)
{
    QByteArray arr = reply->readAll();

    if(!reply->error()){
           ui->edtText->setHtml(QString::fromUtf8(arr));
    }
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
    QFile f(dialog.getOpenFileName());
//    QFile f("bookmarks_12.07.2020.html");
    if(f.open(QIODevice::ReadOnly)){
        QTextStream stream(&f);
        str = stream.readAll();
        ui->edtText->setText(str);
    }

    setEnableTrueButtons();
}

void MainWindow::search_and_show()
{
    ui->lstWindow->clear();

    str = ui->edtText->toHtml();
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
    QString pattern = "[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+";
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
    ui->edtPattern->clear();
    ui->edtText->clear();
    setEnableFalseButtons();
    label->clear();
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

void MainWindow::on_actionSiteParser_triggered()
{
    LinkDialog ld;
    ld.exec();

    QString link = ld.getLink();
    networkManager->get(QNetworkRequest(QUrl(link)));

    setEnableTrueButtons();
}

void MainWindow::on_btnCopy_clicked()
{
    QApplication::clipboard()->setText(currentTxt);
    label->setText("Скопировано");
    ui->btnCopy->setEnabled(false);
}

void MainWindow::on_lstWindow_clicked(const QModelIndex &index)
{
    ui->btnCopy->setEnabled(true);
    currentTxt = ui->lstWindow->item(index.row())->text();
}
