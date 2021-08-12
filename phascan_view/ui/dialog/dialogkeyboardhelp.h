#ifndef DIALOGKEYBOARDHELP_H
#define DIALOGKEYBOARDHELP_H

#include <QDialog>
#include "Struct.h"

namespace Ui {
class DialogKeyboardHelp;
}

class DialogKeyboardHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogKeyboardHelp(QWidget *parent = 0);
    ~DialogKeyboardHelp();

    void setLanguage(setup_LANG lang);
private:
    Ui::DialogKeyboardHelp *ui;
};

#endif // DIALOGKEYBOARDHELP_H
