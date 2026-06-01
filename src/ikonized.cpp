//
// C++ Implementation: ikonized
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ikonized.h"

Ikonized::Ikonized(int &argc, char **argv)
: QApplication(argc, argv)
{
    setApplicationName("ikonized");
    setApplicationVersion("0.2");

    mMainWindow.show();
    mMainWindow.setAttribute(Qt::WA_AlwaysShowToolTips, true);
}

Ikonized::~Ikonized()
{
}
