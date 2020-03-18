//
// C++ Implementation: settings
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "settings.h"

#include <QDir>

namespace ikonized {

Settings::Settings()
 : QSettings(QDir::homePath() + "/.ikonized/config.ini", QSettings::IniFormat)
{
}


Settings::~Settings()
{
}


}
