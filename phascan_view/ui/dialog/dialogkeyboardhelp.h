#ifndef DIALOGKEYBOARDHELP_H
#define DIALOGKEYBOARDHELP_H

#include <QDialog>

namespace Ui {
class DialogKeyboardHelp;
}

class DialogKeyboardHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogKeyboardHelp(QWidget *parent = 0);
    ~DialogKeyboardHelp();

private:
    Ui::DialogKeyboardHelp *ui;
};

#endif // DIALOGKEYBOARDHELP_H
