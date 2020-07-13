#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QLabel>

#include "linkdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QNetworkAccessManager *networkManager;
    QString str;
    QString currentTxt;
    QLabel *label;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setEnableFalseButtons();
    void setEnableTrueButtons();

private slots:
    void onResult(QNetworkReply *reply);
    void search_and_show();
    void on_btnEmail_clicked();
    void on_btnLink_clicked();
    void on_btnSearch_clicked();
    void on_btnClear_clicked();
    void on_lstWindow_doubleClicked(const QModelIndex &index);
     void on_actionOpenFile_triggered();
    void on_actionSiteParser_triggered();

    void on_btnCopy_clicked();

    void on_lstWindow_clicked(const QModelIndex &index);

private:
    bool checkRegExp(QRegExp rx);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
