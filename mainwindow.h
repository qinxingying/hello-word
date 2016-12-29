#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString fileName;

private:
    Ui::MainWindow *ui;

    void testReading();

private slots:
    void on_pushButton_openFile_clicked();

};
extern MainWindow* g_pMainWnd;

#endif // MAINWINDOW_H
