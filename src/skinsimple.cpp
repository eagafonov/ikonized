//
// C++ Implementation: skinsimple
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "skinsimple.h"

#include <QSize>
#include <QRect>
#include <QPainter>

#include <assert.h>

namespace ikonized {

SkinSimple::SkinSimple()
 : SkinBase()
 , mBorder(10)
{
    mSize.setWidth(mBorder * 2 + 48 * 5);
    mSize.setHeight(mBorder * 2 + 48);
}

SkinSimple::~SkinSimple()
{
}

const char * SkinSimple::GetName()
{
    return "simple";
}

int SkinSimple::GetInitialCellSize(QSize & cell_size)
{
    cell_size = mSize;

    return 1;
}

int SkinSimple::GetMinCellSize(QSize & cell_size)
{
    cell_size.setWidth(16 + mBorder*2);
    cell_size.setHeight(16  + mBorder*2);

    return 1;
}

int SkinSimple::GetCellClientRect(const QSize &size, QRect & client_rect)
{
    client_rect = QRect(mBorder, mBorder,
                      size.width() - mBorder * 2,
                      size.height() - mBorder * 2);

    return 1;
}

int SkinSimple::DrawCellBackground(QPainter & painter, bool bActive, const QSize &size)
{
//  painter.drawText(20, 20, QString::number(m_windowInfo.count()));

    QRect r(QPoint(0,0), size);

    painter.setPen(QPen(Qt::black, bActive ? 5 : 2, Qt::SolidLine));
    painter.drawRect(r);

    QRect icons;
    GetCellClientRect(size, r);

    painter.setPen(QPen(Qt::black, 1, Qt::DotLine));
    painter.drawRect(r);

    return 1;
}

int SkinSimple::DrawCellForeground(QPainter & g, bool bActive, const QSize &size)
{
    return 1;
}

int SkinSimple::IsSizable()
{
    return 1;
}

int SkinSimple::SetSize(const QSize &size)
{
    mSize = size;

    return 1;
}

}
