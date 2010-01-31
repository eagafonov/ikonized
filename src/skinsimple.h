//
// C++ Interface: skinsimple
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDSKINSIMPLE_H
#define IKONIZEDSKINSIMPLE_H

#include "skinbase.h"
#include <QSize>

namespace ikonized {

/**
    @author 
*/
class SkinSimple : public SkinBase
{
public:
    SkinSimple();

    virtual ~SkinSimple();
    virtual const char *GetName();

    // initial metrics
    virtual int GetInitialCellSize(QSize &cell_size);
    virtual int GetMinCellSize(QSize &cell_size);

    // current metrics
    virtual int GetCellClientRect(QRect & client_rect);
    virtual int GetCellRect(QRect & cell_rect);

    // Drawing
    virtual int DrawCellBackground(QPainter &g, bool bActive);
    virtual int DrawCellForeground(QPainter &g, bool bActive);

    // Size
    virtual int IsSizable();
    virtual int SetSize(const QSize &size);

private:
    QSize mSize;
    int mBorder;
};

}

#endif
