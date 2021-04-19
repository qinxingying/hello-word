#ifndef DIALOGABOUTFILEPROPERTIES_H
#define DIALOGABOUTFILEPROPERTIES_H

#include <QDialog>

namespace Ui {
class DialogAboutFileProperties;
}

class DialogAboutFileProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAboutFileProperties(QWidget *parent = 0);
    ~DialogAboutFileProperties();

private:
    Ui::DialogAboutFileProperties *ui;
};

#endif // DIALOGABOUTFILEPROPERTIES_H
