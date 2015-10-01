//
// C++ Interface: windowinfo
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2015
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDWINDOWINFO_H
#define IKONIZEDWINDOWINFO_H

#include <QList>
#include <KWindowInfo>
#include <QString>

namespace ikonized {

/**
    @author 
*/
class WindowInfo{
public:
    WindowInfo();

    ~WindowInfo();

    int mDesktop;
    QString mName;
    QString mIconName;
    WId mId;
    bool mIsAllDesktops;
};

typedef QList<WindowInfo> WindowInfoCollection;
}

#endif
