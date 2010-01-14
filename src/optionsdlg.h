#ifndef OPTIONSDLG_H
#define OPTIONSDLG_H

#include <QtGui/QDialog>

namespace Ui {
    class OptionsDlg;
}

class OptionsDlg : public QDialog {
    Q_OBJECT
public:
    OptionsDlg(QWidget *parent = 0);
    ~OptionsDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::OptionsDlg *m_ui;
};

#endif // OPTIONSDLG_H
