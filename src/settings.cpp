//
// C++ Implementation: settings
//
// Description: 
//
//
// Author:  <>, (C) 2010
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
