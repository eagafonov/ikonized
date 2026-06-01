//
// C++ Interface: windowinfo
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDWINDOWINFO_H
#define IKONIZEDWINDOWINFO_H

#include <QList>
#include <KWindowSystem>
#include <KWindowInfo>
#include <NETWM>
#include <QString>

namespace ikonized {

class WindowInfo {
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
