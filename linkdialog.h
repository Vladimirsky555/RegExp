#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT

    QString link;

public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();

    QString getLink();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::LinkDialog *ui;
};

#endif // LINKDIALOG_H
