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
#include <QFile>

namespace ikonized {

SkinSvg::SkinSvg(const QString &filename)
{
    QString skin_filename = filename;

    if (QFile::exists(filename))
    {
        skin_filename = filename;
    }
    else if (QFile::exists("skin.svg"))
    {
        skin_filename = "skin.svg";
    }
    else if (QFile::exists("/usr/share/ikonized/skins/default/skin.svg"))
    {
        skin_filename = "/usr/share/ikonized/skins/default/skin.svg";
    }
    else if (QFile::exists("/usr/local/share/ikonized/skins/default/skin.svg"))
    {
        skin_filename = "/usr/local/share/ikonized/skins/default/skin.svg";
    }

    if (!skin_filename.isEmpty())
    {
        if (mRenderer.load(skin_filename))
        {
            qDebug() << "I: Loaded skin " << skin_filename;
        }
        else
        {
            qWarning() << "Failed to load SVG " << skin_filename;
        }
    }
    else
    {
        qWarning() << "Couldn't locate skin SVG file";
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

    return 0;
}

}
