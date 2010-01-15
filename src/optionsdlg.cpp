#include "optionsdlg.h"
#include "ui_optionsdlg.h"
#include "globals.h"

OptionsDlg::OptionsDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::OptionsDlg)
{
    m_ui->setupUi(this);
    getValues();
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

void OptionsDlg::getValues()
{
    Q_ASSERT(gSettings != 0);

    m_ui->hideOnChangeDesktop->setChecked(gSettings->value("hide.desktop_changed", true).toBool());
}

void OptionsDlg::setValues()
{
    Q_ASSERT(gSettings != 0);
    gSettings->setValue("hide.desktop_changed",m_ui->hideOnChangeDesktop->checkState() == Qt::Checked);
}

void OptionsDlg::accept()
{
    setValues();

    QDialog::accept();
}
