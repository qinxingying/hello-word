#include "mainwindow.h"

#include <QApplication>

MainWindow* g_pMainWnd = NULL;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow _mainWindow;
    g_pMainWnd  = &_mainWindow;
    _mainWindow.show();
    //_mainWindow.showMaximized();
    _mainWindow.setMinimumSize(_mainWindow.width(), _mainWindow.height());

    if(argc > 1) {
        sleep(200);

        if(argv[1]) {
            _mainWindow.OpenFilePro(QString::fromLocal8Bit(argv[1]));
        }
    }

    return app.exec();
}
