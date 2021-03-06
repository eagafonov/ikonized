#include "optionsdlg.h"
#include "ui_optionsdlg.h"
#include "globals.h"

#include <QDebug>
#include <KFileDialog>
#include <KWindowSystem>
#include <KToolInvocation>
#include <QMessageBox>

OptionsDlg::OptionsDlg(const ikonized::WindowInfoCollection &windowInfo, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::OptionsDlg),
    m_windowInfo(windowInfo)
{
    m_ui->setupUi(this);
    connect(m_ui->iconSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(iconSizeValueChanged(int)));

    connect(m_ui->skinFileBrowseBtn, SIGNAL(clicked(bool)),
            this, SLOT(browseSkin(bool)));

    connect(m_ui->launchKeyManagerBtn, SIGNAL(clicked(bool)),
            this, SLOT(launchKeyManagerBtn(bool)));

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
    m_ui->hideOnActivateWindow->setChecked(gSettings->value("hide.activate_window", true).toBool());
    m_ui->iconSizeSlider->setValue(gSettings->value("icon.size", 32).toInt());
    m_ui->skinFilenameEdit->setText(gSettings->value("skin.filename", "").toString());
    m_ui->showUnderCursor->setChecked(gSettings->value("show.under_cursor", false).toBool());
}

void OptionsDlg::setValues()
{
    Q_ASSERT(gSettings != 0);
    gSettings->setValue("hide.desktop_changed",m_ui->hideOnChangeDesktop->checkState() == Qt::Checked);
    gSettings->setValue("hide.activate_window",m_ui->hideOnActivateWindow->checkState() == Qt::Checked);
    gSettings->setValue("icon.size", m_ui->iconSizeSlider->value());
    gSettings->setValue("icon.size", m_ui->iconSizeSlider->value());

    gSettings->setValue("skin.filename", m_ui->skinFilenameEdit->text());

    gSettings->setValue("show.under_cursor", m_ui->showUnderCursor->checkState() == Qt::Checked);
}

void OptionsDlg::accept()
{
    setValues();

    QDialog::accept();
}

void OptionsDlg::iconSizeValueChanged(int size)
{
    qDebug() << "OPTIONS: Icon size " << size;

    if (m_windowInfo.empty())
    {
        QPixmap icon(size, size);
        icon.fill(Qt::blue);

        m_ui->iconPreview->setPixmap(icon);
    }
    else
    {
        QPixmap icon = KWindowSystem::icon(m_windowInfo[qrand() % m_windowInfo.size()].mId, size, size, true);
        m_ui->iconPreview->setPixmap(icon);
    }
}

void OptionsDlg::browseSkin(bool)
{
    QString filename = KFileDialog::getOpenFileName(KUrl(), "*.svg", this, "Select skin");
    
    if (!filename.isEmpty())
    {
       m_ui->skinFilenameEdit->setText(filename);
    }
}

void OptionsDlg::launchKeyManagerBtn(bool )
{
  QString error;
  int err = KToolInvocation::startServiceByDesktopName("keys", QStringList(), &error);

  if (err)
  {
        qDebug() << "Key manager launch error" << err << error;

         QMessageBox msgBox;
         msgBox.setText("ikonized error");
//          msgBox.setInformativeText(QString("%1\nerror=%2").arg(error).arg(err));
//          msgBox.setStandardButtons(QMessageBox::Ok);
//          msgBox.setDefaultButton(QMessageBox::Ok);
         msgBox.exec();
  }
  else
  {
  }
}
