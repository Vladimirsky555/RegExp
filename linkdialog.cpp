#include "linkdialog.h"
#include "ui_linkdialog.h"

#include <QMessageBox>

LinkDialog::LinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);

    setWindowTitle("ССылка на сайт");
    ui->edtLink->setPlaceholderText("http://mysite.ru");
}

LinkDialog::~LinkDialog()
{
    delete ui;
}

QString LinkDialog::getLink()
{
    return this->link;
}

void LinkDialog::on_btnOK_clicked()
{
    if(ui->edtLink->text() == ""){
        QMessageBox::information(this, "Предупреждение", "Вы не ввели ссылку!");
        return;
    }

    link = ui->edtLink->text();
    close();
}

void LinkDialog::on_btnCancel_clicked()
{
    close();
}
