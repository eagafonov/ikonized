//
// C++ Implementation: ikonized
//
// Description:
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ikonized.h"

Ikonized::Ikonized()
: KApplication()
{
    mMainWindow.show();
    mMainWindow.setAttribute(Qt::WA_AlwaysShowToolTips, true);
}


Ikonized::~Ikonized()
{
}


