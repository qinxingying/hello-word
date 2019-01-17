#include "mainwindow.h"

#include <QApplication>
#include "configure/config_phascan_ii/settings.h"

MainWindow* g_pMainWnd = NULL;
CURVE_RL_EL_SL CUR_RES;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSettings::Format format = QSettings::registerFormat("cfg", &settings_read_msgpack, &settings_write_msgpack);
    QSettings::setDefaultFormat(format);

    MainWindow _mainWindow;
    g_pMainWnd  = &_mainWindow;
    _mainWindow.show();
    _mainWindow.showMaximized();
    _mainWindow.setMinimumSize(_mainWindow.width(), _mainWindow.height());

    if(argc > 1) {
        sleep(200);

        if(argv[1]) {
            _mainWindow.OpenFilePro(QString::fromLocal8Bit(argv[1]));
        }
    }

    return app.exec();
}
