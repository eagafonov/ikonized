//
// C++ Implementation: mainwindow
//
// Description: 
//
//
// Author:  <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mainwindow.h"

#include <QPainter>
#include <KWindowSystem>
#include <QDebug>
#include <QResizeEvent>

namespace ikonized {

MainWindow::MainWindow()
 : QWidget(NULL /*, Qt::FramelessWindowHint | Qt::Tool*/)
 , mDesktopCount(3)
 , mShowAllDesktopWindows(false)
{
	mDesktopCount = KWindowSystem::numberOfDesktops();
	mCurrentDesktop = KWindowSystem::currentDesktop();
	updateDesktopRegions(size());

    connect(KWindowSystem::self(), SIGNAL(currentDesktopChanged(int)), this, SLOT(currentDesktopChanged(int)));
    connect(KWindowSystem::self(), SIGNAL(windowAdded(WId)), this, SLOT(windowAdded(WId)));
    connect(KWindowSystem::self(), SIGNAL(windowRemoved(WId)), this, SLOT(windowRemoved(WId)));
    connect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)), this, SLOT(activeWindowChanged(WId)));
    connect(KWindowSystem::self(), SIGNAL(numberOfDesktopsChanged(int)), this, SLOT(numberOfDesktopsChanged(int)));
    connect(KWindowSystem::self(), SIGNAL(desktopNamesChanged()), this, SLOT(desktopNamesChanged()));
//     connect(KWindowSystem::self(), SIGNAL(stackingOrderChanged()), this, SLOT(stackingOrderChanged()));
//     connect(KWindowSystem::self(), SIGNAL(windowChanged(WId,unsigned int)), this, SLOT(windowChanged(WId,unsigned int)));
    connect(KWindowSystem::self(), SIGNAL(showingDesktopChanged(bool)), this, SLOT(showingDesktopChanged(bool)));

	m_IconWidth = 32;	// TODO get icon size from settings
	m_IconHeight = 32;

}


MainWindow::~MainWindow()
{
}


}

void ikonized::MainWindow::paintEvent(QPaintEvent * e)
{
	QPainter painter(this);
	QPen pen(Qt::black, 2, Qt::SolidLine);

	painter.setPen(pen);
// 	painter.drawLine(20, 40, 250, 40);

	painter.drawText(20, 20, QString::number(m_windowInfo.count()));

	for (int desk=1; desk < m_Desktops.size(); desk++)
	{
		painter.drawRect(m_Desktops[desk].m_OveralRegion);
	}

	painter.setPen(QPen(Qt::black, 1, Qt::DotLine));

	for (int desk=1; desk < m_Desktops.size(); desk++)
	{
		painter.drawRect(m_Desktops[desk].m_InnerRegion);
	}

	drawContent(painter);
}

void ikonized::MainWindow::currentDesktopChanged(int desktop)
{
	qDebug() << "Desktop #" << desktop << " activated";
	mCurrentDesktop = desktop;
}

void ikonized::MainWindow::windowAdded(WId id)
{
	qDebug() << __func__ << "(" << id << ")";
	updateWindowInfo();
}

void ikonized::MainWindow::windowRemoved(WId )
{
	qDebug() << __func__;
	updateWindowInfo();
}

void ikonized::MainWindow::activeWindowChanged(WId )
{
	qDebug() << __func__;
}

void ikonized::MainWindow::numberOfDesktopsChanged(int count)
{
	qDebug() << "New desktop number: " << count;
	mDesktopCount = count;

	updateDesktopRegions(size());
	update();
}

void ikonized::MainWindow::desktopNamesChanged()
{
	qDebug() << __func__;
}

void ikonized::MainWindow::stackingOrderChanged()
{
	qDebug() << __func__;
}

void ikonized::MainWindow::windowChanged(WId , unsigned int )
{
	qDebug() << __func__;
}

void ikonized::MainWindow::showingDesktopChanged(bool )
{
	qDebug() << __func__;
}

void ikonized::MainWindow::updateWindowInfo()
{
    m_windowInfo.clear();

    QList<WId> windows = KWindowSystem::stackingOrder();

    foreach (WId window, windows) {
        KWindowInfo info = KWindowSystem::windowInfo(window, NET::WMGeometry | NET::WMFrameExtents |
                                                             NET::WMWindowType | NET::WMDesktop |
                                                             NET::WMState | NET::XAWMState | NET::WMVisibleName | NET::WMVisibleIconName);

        NET::WindowType type = info.windowType(NET::NormalMask | NET::DialogMask | NET::OverrideMask |
                                               NET::UtilityMask | NET::DesktopMask | NET::DockMask |
                                               NET::TopMenuMask | NET::SplashMask | NET::ToolbarMask |
                                               NET::MenuMask);

        // the reason we don't check for -1 or Net::Unknown here is that legitimate windows, such
        // as some java application windows, may not have a type set for them.
        // apparently sane defaults on properties is beyond the wisdom of x11.
        if (type == NET::Desktop || type == NET::Dock || type == NET::TopMenu ||
            type == NET::Splash || type == NET::Menu || type == NET::Toolbar ||
            info.hasState(NET::SkipPager)) 
        {
            continue;
        }

		qDebug() << __func__ << ": Adding window " <<  info.visibleName();

		WindowInfo winfo;
		winfo.mDesktop = info.desktop();
		winfo.mName = info.visibleName();
		winfo.mId = info.win();
		winfo.mIconName = info.visibleIconName();
		winfo.mIsAllDesktops = info.onAllDesktops();

		qDebug() << __func__ << ": Icon " << winfo.mIconName;


		m_windowInfo.append(winfo);

/*        for (int i = 0; i < m_desktopCount; i++) {
            if (!info.isOnDesktop(i+1)) {
                continue;
            }

            QRect windowRect = info.frameGeometry();

            if (KWindowSystem::mapViewport()) {
                windowRect = fixViewportPosition( windowRect );
            }

            windowRect = QRectF(windowRect.x() * m_widthScaleFactor,
                                windowRect.y() * m_heightScaleFactor,
                                windowRect.width() * m_widthScaleFactor,
                                windowRect.height() * m_heightScaleFactor).toRect();
            windowRect.translate(m_rects[i].topLeft().toPoint());
            m_windowRects[i].append(QPair<WId, QRect>(window, windowRect));
            if (window == KWindowSystem::activeWindow()) {
                m_activeWindows.append(windowRect);
            }

            m_windowInfo.append(info);
        }*/
    }	

	update();
}

const int cell_frame=5;

void ikonized::MainWindow::updateDesktopRegions(const QSize &size)
{
	// desktiop IDs is 1-based
    m_Desktops.resize(mDesktopCount + 1);

	int cell_w = size.width();
	int cell_h = size.height() / mDesktopCount;

	QRect cell_rect (0, 0, cell_w, cell_h);

	QRect icont_rect (cell_frame, cell_frame, cell_w - 2*cell_frame, cell_h-2*cell_frame);

    for (int desk=1; desk <= mDesktopCount; desk++)
    {
		size_t hash = 0;

		// TODO
// 		m_pSkin->GetCellRect(row, col, m_Desktops[desk].m_OveralRegion);
// 		m_pSkin->GetCellClientRect(row, col, m_Desktops[desk].m_InnerRegion);

		//Fixed size reg

		cell_rect.moveTop(cell_h * (desk-1));
		m_Desktops[desk].m_OveralRegion = cell_rect;

		icont_rect.moveTop(cell_h * (desk-1) + cell_frame);
		m_Desktops[desk].m_InnerRegion = icont_rect;

		// init new hash
		hash += desk;

		if (mCurrentDesktop == desk)
		{
			hash += 1;

			if (mShowAllDesktopWindows)
			{
				hash += 2;
			}
		}

		m_Desktops[desk].m_Hash = hash;
    }
};

void ikonized::MainWindow::resizeEvent(QResizeEvent * event)
{
	updateDesktopRegions(event->size());
}

void ikonized::MainWindow::drawContent(QPainter & painter)
{
	QRect desk_rect;
	QRect icon_rect;
	
	QRect client_rect = geometry();
// 	GetClientRect(&client_rect);

	/* draw background */
	for (int d=0; d <= mDesktopCount; d++)
	{
		// TODO
		// m_pSkin->DrawCellBackground(g, row, col, (nCurDesktop == nDesktop));

		// reset window count
		Q_ASSERT(d < m_Desktops.size());
		m_Desktops[d].m_nWindowsCount = 0;
	}
	
	// loop other windows
	for (WindowInfoCollection::const_iterator iter =  m_windowInfo.begin(); 
		iter != m_windowInfo.end(); 
		iter++)
	{
		// check that window is on some desktop
		int nDesktop = iter->mDesktop;

		if (nDesktop > 0 && (nDesktop <= mDesktopCount))
		{
			// skip sticky widnows on all desktops
			// skipp hidden windows on current desktop

			if (iter->mIsAllDesktops  && !mShowAllDesktopWindows)
			{
				continue;
			}

			// set clipping to inner region 
			Q_ASSERT(nDesktop < m_Desktops.size());
			
			int icon_index = (m_Desktops[nDesktop].m_nWindowsCount++);

			if (getDesktopIconRect(icon_index, m_Desktops[nDesktop].m_InnerRegion, icon_rect))
			{
				painter.setClipRect(m_Desktops[nDesktop].m_InnerRegion);

				// draw an icon
				// TODO implement pixmap cache
				QPixmap icon = KWindowSystem::icon(iter->mId, m_IconWidth, m_IconHeight, true);

				painter.drawPixmap(icon_rect, icon);

				// TODO draw sticky mark
// 				if (m_bShowStickyWindows && iter->Sticky && m_pStickyWindowMark)
// 				{
// 					Gdiplus::ImageAttributes attr;
// 
// 					// TODO Add sticky mark into skin
// 					static Gdiplus::ColorMap map={Gdiplus::Color::White,Gdiplus::Color::Transparent};
// 					
// 					attr.SetRemapTable(1, &map);
// 					
// 					g.DrawImage(m_pStickyWindowMark, icon_rect, 
// 								0, 0, 
// 								m_pStickyWindowMark->GetWidth(), m_pStickyWindowMark->GetHeight(), 
// 								Gdiplus::UnitPixel,
// 								&attr);
// 				}
			}
		}
	}

	// reset clipping area
	painter.setClipping(false);

	/* draw borders */
	// TODO draw foregrownd
// 	nDesktop = 0;
// 
// 	for (row = 0; row < max_row; row++)
// 	{
// 		for (col = 0; col < max_col; col++)
// 		{
// 			nDesktop++;
// 			m_pSkin->DrawCellForeground(g, row, col, (nCurDesktop == nDesktop));
// 		}
// 	}
}

// TODO make part of Skin/setting
#define ICON_HSPACING 2
#define ICON_VSPACING 2

#define ICON_REGION_WIDTH (m_IconWidth + ICON_HSPACING)
#define ICON_REGION_HEIGH (m_IconHeight + ICON_VSPACING)

bool ikonized::MainWindow::getDesktopIconRect(int n, const QRect &outer_rect, QRect &icon_rect)
{
    int icons_per_row = outer_rect.width();
	icons_per_row /= (m_IconWidth + ICON_HSPACING);

    if (icons_per_row == 0)
    {
        return false;
    }


    int icon_row = n / icons_per_row;
    int icon_col = n % icons_per_row;

	icon_rect = QRect((icon_col) * ICON_REGION_WIDTH,
					  (icon_row) * ICON_REGION_WIDTH,
				      m_IconWidth,
					  m_IconHeight);

//     icon_rect.Y = (icon_row) * ICON_REGION_WIDTH;
//     icon_rect.X = (icon_col) * ICON_REGION_WIDTH;
// 
//     icon_rect.Height = m_IconHeight;
//     icon_rect.Width  = m_IconWidth;

    icon_rect.translate(outer_rect.left(), outer_rect.top());

    // check that icon will be visible
    return icon_rect.intersects(outer_rect);
}
