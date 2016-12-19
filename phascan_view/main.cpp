#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"
#include "const.h"

MainWindow* g_pMainWnd = NULL;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow _mainWindow;
    g_pMainWnd  = &_mainWindow;
    _mainWindow.show();
    _mainWindow.showMaximized();
    _mainWindow.setMinimumSize(_mainWindow.width(), _mainWindow.height());

    {
        if(argc > 1) {
            sleep(200);
            if(argv[1]) {
                _mainWindow.OpenFilePro(QString(QObject::tr(argv[1])));
            }
        }
    }

    return app.exec();
}
