#ifndef DIALOGREGISTER_H
#define DIALOGREGISTER_H

#include <QDialog>

namespace Ui {
    class DialogRegister;
}

class DialogRegister : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRegister(QWidget *parent = 0);
    ~DialogRegister();

private:
    Ui::DialogRegister *ui;

	bool RegCharacterPro(const QString& str_, char* buf_);

private slots:
	void slotTextChanged1(const QString& str_);
/*
	void slotTextChanged2(const QString& str_);
	void slotTextChanged3(const QString& str_);
	void slotTextChanged4(const QString& str_);

	void slotTextChanged5(const QString& str_);
	void slotTextChanged6(const QString& str_);
	void slotTextChanged7(const QString& str_);
	void slotTextChanged8(const QString& str_);
*/
	void slotRegBtnClicked();
};

#endif // DIALOGREGISTER_H
