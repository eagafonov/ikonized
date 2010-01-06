#include "ikonized.h"

#include <KCmdLineArgs>
#include <KAboutData>

#include <QDebug>

int main(int argc, char **argv)
{
	KAboutData about(QString("ikonized").toLocal8Bit(), QString("ikonized").toLocal8Bit(), KLocalizedString(), QString("0.1").toLocal8Bit());

	KCmdLineArgs::init(argc, argv, &about);

	Ikonized app;

	app.exec();

	qDebug() << "Exit";
	return 0;
}