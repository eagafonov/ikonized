#include "ikonized.h"

#include <QDebug>

#include "settings.h"

ikonized::Settings *gSettings = 0;

int main(int argc, char **argv)
{
    ikonized::Settings settings;
    gSettings = &settings;

    Ikonized app(argc, argv);

    int ret_val = app.exec();

    qDebug() << "Exit, result=" << ret_val;
    return ret_val;
}
