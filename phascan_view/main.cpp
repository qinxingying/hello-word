#include "mainwindow.h"

#include <QApplication>
#include "configure/config_phascan_ii/settings.h"
#include <stdio.h>
#include <stdlib.h>

MainWindow* g_pMainWnd = NULL;
CURVE_RL_EL_SL CUR_RES;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
    {
        strMsg = QString("Debug:");
        // 设置输出信息格式
        QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        QString strMessage = QString("Message:%1 File:%2  Line:%3  Function:%4  DateTime:%5")
                .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);

        // 输出信息至文件中（读写、追加形式）
        QFile file("log.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream stream(&file);
        stream << strMessage << "\r\n";
        file.flush();
        file.close();
        break;
    }
    case QtWarningMsg:
    {
        strMsg = QString("Warning:");
        break;
    }
    case QtCriticalMsg:
    {
        strMsg = QString("Critical:");
        break;
    }
    case QtFatalMsg:
    {
        strMsg = QString("Fatal:");
        break;
    }
    }

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    //qInstallMessageHandler(myMessageOutput);
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi);

    QSettings::Format format = QSettings::registerFormat("cfg", &settings_read_msgpack, &settings_write_msgpack);
    QSettings::setDefaultFormat(format);

    MainWindow _mainWindow;
    g_pMainWnd  = &_mainWindow;
    _mainWindow.show();
    _mainWindow.showMaximized();
    _mainWindow.setMinimumSize(_mainWindow.width(), _mainWindow.height());

    if(argc > 1) {
        //sleep(200);

        if(argv[1]) {
            _mainWindow.OpenFilePro(QString::fromLocal8Bit(argv[1]));
        }
    }

    return app.exec();
}
