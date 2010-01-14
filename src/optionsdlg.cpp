#include "optionsdlg.h"
#include "ui_optionsdlg.h"

OptionsDlg::OptionsDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::OptionsDlg)
{
    m_ui->setupUi(this);
}

OptionsDlg::~OptionsDlg()
{
    delete m_ui;
}

void OptionsDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
