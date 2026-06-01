#include "optionsdlg.h"
#include "ui_optionsdlg.h"
#include "globals.h"

#include <QDebug>
#include <QFileDialog>
#include <KWindowSystem>
#include <QProcess>
#include <QMessageBox>
#include <QRandomGenerator>

OptionsDlg::OptionsDlg(const ikonized::WindowInfoCollection &windowInfo, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::OptionsDlg),
    m_windowInfo(windowInfo)
{
    m_ui->setupUi(this);
    connect(m_ui->iconSizeSlider, &QSlider::valueChanged,
            this, &OptionsDlg::iconSizeValueChanged);

    connect(m_ui->skinFileBrowseBtn, &QPushButton::clicked,
            this, &OptionsDlg::browseSkin);

    connect(m_ui->launchKeyManagerBtn, &QPushButton::clicked,
            this, &OptionsDlg::launchKeyManagerBtn);

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
    gSettings->setValue("hide.desktop_changed", m_ui->hideOnChangeDesktop->checkState() == Qt::Checked);
    gSettings->setValue("hide.activate_window", m_ui->hideOnActivateWindow->checkState() == Qt::Checked);
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
    qDebug() << "OPTIONS: Icon size" << size;

    if (m_windowInfo.empty())
    {
        QPixmap icon(size, size);
        icon.fill(Qt::blue);
        m_ui->iconPreview->setPixmap(icon);
    }
    else
    {
        int idx = QRandomGenerator::global()->bounded(m_windowInfo.size());
        QPixmap icon = KWindowSystem::icon(m_windowInfo[idx].mId, size, size, true);
        m_ui->iconPreview->setPixmap(icon);
    }
}

void OptionsDlg::browseSkin(bool)
{
    QString filename = QFileDialog::getOpenFileName(this, "Select skin", QString(), "SVG files (*.svg)");

    if (!filename.isEmpty())
    {
        m_ui->skinFilenameEdit->setText(filename);
    }
}

void OptionsDlg::launchKeyManagerBtn(bool)
{
    bool ok = QProcess::startDetached("kcmshell5", QStringList() << "keys");

    if (!ok)
    {
        qDebug() << "Key manager launch error";
        QMessageBox msgBox;
        msgBox.setText("Failed to launch key manager");
        msgBox.exec();
    }
}
