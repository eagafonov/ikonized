//
// C++ Interface: skinsvg
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDSKINSVG_H
#define IKONIZEDSKINSVG_H

#include "skinsimple.h"
#include <QSvgRenderer>

namespace ikonized {

/**
	@author 
*/
class SkinSvg : public SkinSimple
{
public:
    SkinSvg(const QString &filename);

    ~SkinSvg();
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
private:
    QSvgRenderer mRenderer;
};

}

#endif
