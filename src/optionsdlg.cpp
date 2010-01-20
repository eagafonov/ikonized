#include "optionsdlg.h"
#include "ui_optionsdlg.h"
#include "globals.h"

#include <QDebug>

OptionsDlg::OptionsDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::OptionsDlg)
{
    m_ui->setupUi(this);
    connect(m_ui->iconSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(iconSizeValueChanged(int)));

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
    m_ui->iconSizeSlider->setValue(gSettings->value("icon.size", 32).toInt());
}

void OptionsDlg::setValues()
{
    Q_ASSERT(gSettings != 0);
    gSettings->setValue("hide.desktop_changed",m_ui->hideOnChangeDesktop->checkState() == Qt::Checked);
    gSettings->setValue("icon.size", m_ui->iconSizeSlider->value());
}

void OptionsDlg::accept()
{
    setValues();

    QDialog::accept();
}

void OptionsDlg::iconSizeValueChanged(int size)
{
    qDebug() << "OPTIONS: Icon size " << size;
}
