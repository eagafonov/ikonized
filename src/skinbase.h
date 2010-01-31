/**************************************************************************
 *  i-conized - module for Virtual Desktop Manager (virtuawin.sourceforge.net)
 * 
 *  Copyright (c) 2007-2008 Eugene Agafonov
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
 *  USA.
 * 
 *************************************************************************
 * 
 * Definition of Skin's runtime interface
 *
 **************************************************************************/

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
    virtual int GetCellClientRect(QRect & client_rect) = 0;
    virtual int GetCellRect(QRect & cell_rect) = 0;

    // Drawing
    virtual int DrawCellBackground(QPainter &g, bool bActive) = 0;
    virtual int DrawCellForeground(QPainter &g, bool bActive) = 0;

    // Size
    virtual int IsSizable() = 0;
    virtual int SetSize(const QSize &) = 0;
};

} // end of namespace iconized

#endif
