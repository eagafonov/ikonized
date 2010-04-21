#ifndef OPTIONSDLG_H
#define OPTIONSDLG_H

#include <QtGui/QDialog>

#include "windowinfo.h"

namespace Ui {
    class OptionsDlg;
}

class OptionsDlg : public QDialog {
    Q_OBJECT
public:
    OptionsDlg(const ikonized::WindowInfoCollection &windowInfo, QWidget *parent = 0);
    ~OptionsDlg();

protected:
    void changeEvent(QEvent *e);
    void getValues();
    void setValues();

private slots:
    void iconSizeValueChanged(int size);
    void browseSkin(bool);
    void launchKeyManagerBtn(bool);

private:
    Ui::OptionsDlg *m_ui;
    mutable const ikonized::WindowInfoCollection &m_windowInfo;

    virtual void accept();
};

#endif // OPTIONSDLG_H
