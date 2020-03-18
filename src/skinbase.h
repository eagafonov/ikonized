//
// C++ Interface: SkinBase
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution

#ifndef _SKINBASE_H_
#define _SKINBASE_H_

class QSize;
class QRect;
class QPainter;

namespace ikonized {


class SkinBase
{
public:
    virtual ~SkinBase() = 0;
    // Metadata
    virtual const char *GetName() = 0;

    // initial metrics
    virtual int GetInitialCellSize(QSize &cell_size) = 0;
    virtual int GetMinCellSize(QSize &window_size) = 0;

    // current metrics
    virtual int GetCellClientRect(const QSize &cell_size, QRect & client_rect) = 0;

    // Drawing
    virtual int DrawCellBackground(QPainter &g, bool bActive, const QSize &size) = 0;
    virtual int DrawCellForeground(QPainter &g, bool bActive, const QSize &size) = 0;

    // Size
    virtual int IsSizable() = 0;
    virtual int SetSize(const QSize &) = 0;
};

} // end of namespace iconized

#endif
