//
// C++ Interface: settings
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2015
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDSETTINGS_H
#define IKONIZEDSETTINGS_H

#include <qsettings.h>

namespace ikonized {

/**
	@author 
*/
class Settings : public QSettings
{
public:
    Settings();

    ~Settings();

};

}

#endif
