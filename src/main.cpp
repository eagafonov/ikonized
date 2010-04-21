#include "ikonized.h"

#include <KCmdLineArgs>
#include <KAboutData>

#include <QDebug>

#include "settings.h"

ikonized::Settings *gSettings = 0;

int main(int argc, char **argv)
{
    KAboutData about(QString("ikonized").toLocal8Bit(), QString("ikonized").toLocal8Bit(), KLocalizedString(), QString("0.1").toLocal8Bit());

    KCmdLineArgs::init(argc, argv, &about);

    ikonized::Settings settings;
    gSettings = &settings;

    Ikonized app;

    int ret_val = app.exec();

    qDebug() << "Exit, result=" << ret_val;
    return ret_val;
}