//
// C++ Implementation: skinsvg
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "skinsvg.h"
#include <QPainter>
#include <QDebug>

namespace ikonized {

SkinSvg::SkinSvg()
{
    if (!mRenderer.load(QString("skin.svg")))
    {
        qWarning() << "E: Failed to load SVG";
    }
}


SkinSvg::~SkinSvg()
{
}

const char * SkinSvg::GetName()
{
    return "svg";
}

int SkinSvg::GetInitialCellSize(QSize & cell_size)
{
    cell_size = mSize;

    return 1;
}

int SkinSvg::GetMinCellSize(QSize & cell_size)
{
    cell_size.setWidth(16 + mBorder*2);
    cell_size.setHeight(16  + mBorder*2);

    return 1;
}

int SkinSvg::GetCellClientRect(QRect & client_rect)
{
    client_rect = QRect(mBorder, mBorder,
                      mSize.width() - mBorder * 2,
                      mSize.height() - mBorder * 2);

    return 1;
}

int SkinSvg::GetCellRect(QRect & cell_rect)
{
    cell_rect = QRect(QPoint(0, 0), mSize);

    return 1;
}

int SkinSvg::DrawCellBackground(QPainter & painter, bool bActive)
{
    if (mRenderer.isValid())
    {
        QRectF r(0,0, mSize.width(), mSize.height());
        mRenderer.render(&painter, bActive ?  "activebg" : "inactivebg", r);
        return 1;
    }
    else
        return SkinSimple::DrawCellBackground(painter, bActive);
}

int SkinSvg::DrawCellForeground(QPainter & painter, bool bActive)
{
    if (mRenderer.isValid())
    {
        QRectF r(0,0, mSize.width(), mSize.height());
        mRenderer.render(&painter, bActive ?  "activefg" : "inactivefg", r);
        return 1;
    }
}

}
