#ifndef DIALOGABOUVERSION_H
#define DIALOGABOUVERSION_H

#include <QDialog>

namespace Ui {
class DialogAboutVersion;
}

class DialogAboutVersion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAboutVersion(QWidget *parent = 0);
    ~DialogAboutVersion();

private:
    Ui::DialogAboutVersion *ui;
};

#endif // DIALOGABOUVERSION_H
