#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString str;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int defineCounts(QString filename);

private slots:
    void on_actionOpenFile_triggered();

    void search_and_show();
    void on_btnEmail_clicked();
    void on_btnLink_clicked();

    void on_btnSearch_clicked();
    void on_btnClear_clicked();

    void on_lstWindow_doubleClicked(const QModelIndex &index);

private:
    bool checkRegExp(QRegExp rx);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
