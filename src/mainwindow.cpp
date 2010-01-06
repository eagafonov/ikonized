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

#define SWITCH_TO_MOVE_THRESEHOLD 10
#define RESIZE_BORDER 20

namespace ikonized {

MainWindow::MainWindow()
 : QWidget(NULL , Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint/*| Qt::Tool*/)
 , mDesktopCount(3)
 , mShowAllDesktopWindows(false)
 , m_bLeftButtonPressed(false)
 , m_State(STATE_IDLE)
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
    connect(KWindowSystem::self(), SIGNAL(windowChanged(WId,unsigned int)), this, SLOT(windowChanged(WId,unsigned int)));
    connect(KWindowSystem::self(), SIGNAL(showingDesktopChanged(bool)), this, SLOT(showingDesktopChanged(bool)));

	m_IconWidth = 32;	// TODO get icon size from settings
	m_IconHeight = 32;
	setMouseTracking(true);
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
	updateWindowInfo();
}

void ikonized::MainWindow::windowAdded(WId id)
{
// 	qDebug() << __func__ << "(" << id << ")";
	updateWindowInfo();
}

void ikonized::MainWindow::windowRemoved(WId )
{
// 	qDebug() << __func__;
	updateWindowInfo();
}

void ikonized::MainWindow::activeWindowChanged(WId )
{
// 	qDebug() << __func__;
}

void ikonized::MainWindow::numberOfDesktopsChanged(int count)
{
// 	qDebug() << "New desktop number: " << count;
	mDesktopCount = count;

	updateDesktopRegions(size());
	update();
}

void ikonized::MainWindow::desktopNamesChanged()
{
// 	qDebug() << __func__;
}

void ikonized::MainWindow::stackingOrderChanged()
{
// 	qDebug() << __func__;
}

void ikonized::MainWindow::windowChanged(WId , unsigned int flags)
{

	if (flags & NET::WM2RestackWindow)
	{
		qDebug() << __func__ << "Some window was moved from one desktop to another";
		updateWindowInfo();
	}
}

void ikonized::MainWindow::showingDesktopChanged(bool )
{
// 	qDebug() << __func__;
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

// 		qDebug() << __func__ << ": Adding window " <<  info.visibleName();

		WindowInfo winfo;
		winfo.mDesktop = info.desktop();
		winfo.mName = info.visibleName();
		winfo.mId = info.win();
		winfo.mIconName = info.visibleIconName();
		winfo.mIsAllDesktops = info.onAllDesktops();

// 		qDebug() << __func__ << ": Icon " << winfo.mIconName;


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

void ikonized::MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint point(event->pos());
    int desktop, icon;

// 	grabMouse();

    m_bLeftButtonPressed = true;

    m_MousePressPosition = point;

     resetDragData();

    if (m_ResizeData.ready/* && m_pSkin->IsSizable()*/)
    {
        m_State = STATE_RESIZE;

        m_ResizeData.original_size = size();

/*        if (m_pSkin)
        {
            Gdiplus::Size min_size;
            m_pSkin->GetMinSize(GetDesktopY(), GetDesktopX(), min_size);

            m_ResizeData.min_w = min_size.Width;
            m_ResizeData.min_h = min_size.Height;
        }
        else*/
        {
            m_ResizeData.min_w = m_ResizeData.min_h = 0;
        }
    }
    
    getDesktopIconByPoint(point, desktop, icon, &m_DragData.icon_point);

    if (icon >= 0)
    {
        WindowInfo* window_info = NULL;

        getWindowByDesktopIcon(desktop, icon, &window_info);

        if (window_info)
        {
            if (!window_info->mIsAllDesktops)
            {
                setDragMode(window_info->mId, point);
            }
        }
    }
}

void ikonized::MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    QPoint  point(event->pos());
    int desktop;

	releaseMouse();

    m_bLeftButtonPressed = false;

//     StopDragMode();
    
    if (m_State == STATE_DRAG_ICON)
    {
//         Gdiplus::Rect dragging_icon_rect(m_DragData.position , Gdiplus::Size(m_IconWidth, m_IconHeight));
// 
//         // invalidate old position
//         InvalidateRect(dragging_icon_rect);

        if (point == m_MousePressPosition)
        {
            // access window...
			KWindowSystem::activateWindow(m_DragData.target_window);

//             CVWModule::AccessWindow(m_DragData.target_window , 3);
//             CVWModule::MakeForegroundWindow(m_DragData.target_window);

            // Restore window if minimized
//             long window_style = ::GetWindowLong(m_DragData.target_window, GWL_STYLE);


            if (KWindowSystem::windowInfo(m_DragData.target_window, NET::WMState | NET::XAWMState).isMinimized())
            {
				KWindowSystem::raiseWindow(m_DragData.target_window);
            }
            
/*            if (m_Settings.GetBoolValue(SETTING_HideAfterWindowActivating) && 
               !(m_HideData.m_AutohideForced))
            {
                ShowWindow(SW_HIDE);
            }*/
            
        }
        else if ((desktop = getDesktopByPoint(point)) != getDesktopByPoint(m_MousePressPosition))
        {
            // move window to desktop
			KWindowSystem::setOnDesktop(m_DragData.target_window, desktop);

            // update window list
//             RequestWindowsList(REFRESH_FULL_REDRAW);
        }            

        resetDragData();
    }
    else if (m_State == STATE_MOVE)
    {
        endWindowMoving();
    }
    else if (m_State == STATE_RESIZE)
    {
        m_State = STATE_IDLE;
		unsetCursor();
    }
    else
    {
        desktop = getDesktopByPoint(point);

        if (desktop != mCurrentDesktop)
        {
			KWindowSystem::setCurrentDesktop(desktop);

			// TODO autohiding
//             if (m_Settings.GetBoolValue(SETTING_HideAfterDesktopChanging)
//                 && !(m_HideData.m_AutohideForced))
//            {
//                 ShowWindow(SW_HIDE);
//             }

        }
    }
}

void ikonized::MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    QPoint point(event->pos());
    
    static bool bTooltipVisible = false;
    static QPoint PrevPosition;

    /* ignore dummy events */
    if (PrevPosition == point)
    {
        return;
    }

    PrevPosition = point;

    if (m_State == STATE_DRAG_ICON)
    {
//         assert(m_DragData.target_window != 0);
// 
//         if (bTooltipVisible)
//         {
//             m_ToolTip.ShowToolTip(FALSE);
//             bTooltipVisible = false;
//         }
// 
//         m_DragData.position = point - m_DragData.icon_point;
// 
//         m_DraggingIconWnd.SetPosition(m_DragData.position.X, 
//                                       m_DragData.position.Y);
    }
    else if (m_State == STATE_MOVE) // continue moving
    {
        QPoint shift = point - m_MoveData.old_position;

		QPoint p(pos());
		p += shift;

        // adjust window position to screen borders
//         RECT desktop_rect;
//         GetVirtualDesktopRect(&desktop_rect);
// 
//         if (adjust_window_bounds<LONG>(window_rect.top, window_rect.bottom, desktop_rect.top, desktop_rect.bottom, 10))
//         {
//             m_MoveData.old_position.Y = point.Y;
//         }
// 
//         if (adjust_window_bounds<LONG>(window_rect.left, window_rect.right, desktop_rect.left, desktop_rect.right, 10))
//         {
//             m_MoveData.old_position.X = point.X;
//         }

			move(p);
    }
    else if (m_State == STATE_RESIZE)
    {
		QPoint shift = point - m_MousePressPosition;

		QSize new_size = m_ResizeData.original_size + QSize(shift.x(), shift.y());

        if (new_size.width() < m_ResizeData.min_w)
        {
            new_size.setWidth(m_ResizeData.min_w);
        }
        if (new_size.height() < m_ResizeData.min_h)
        {
            new_size.setHeight(m_ResizeData.min_h);
        }

		resize(new_size);
    }
    else if (m_bLeftButtonPressed) // start window moving or resizeing
    {
		QPoint shift = point - m_MousePressPosition;

        if ((point.x() > SWITCH_TO_MOVE_THRESEHOLD) ||
            (point.x() < -SWITCH_TO_MOVE_THRESEHOLD) ||
            (point.y() > SWITCH_TO_MOVE_THRESEHOLD) ||
            (point.y() < -SWITCH_TO_MOVE_THRESEHOLD))

        {
            startWindowMoving(m_MousePressPosition);

//             m_ToolTip.ShowToolTip(FALSE);
//             bTooltipVisible = false;
        }

    }
    else 
    {
//         if (m_pSkin->IsSizable())
        {
//             LPCTSTR cursor_name = 0;
            QRect r = rect();


            bool left    = (point.x() - r.left()) < RESIZE_BORDER;
            bool right   = (r.right() - point.x()) < RESIZE_BORDER;
            bool top     = (point.y() - r.top()) < RESIZE_BORDER;
            bool bottom  = (r.bottom() - point.y()) < RESIZE_BORDER;

            m_ResizeData.ready = true;

            if (/*left && top ||*/
                right && bottom)
            {
				qDebug() << r;
//              cursor_name = IDC_SIZENWSE;
				setCursor(Qt::SizeFDiagCursor);
            }
            //else if (right && top ||
            //         left && bottom)
            //{
            //    cursor_name = IDC_SIZENESW;
            //}
            //else if (left || right)
            //{
            //    cursor_name = IDC_SIZEWE;
            //}
            //else if (top || bottom)
            //{
            //    cursor_name = IDC_SIZENS;
            //}
            else
            {
//                 cursor_name = IDC_ARROW;
                m_ResizeData.ready = false;
				unsetCursor();
            }

//             if (cursor_name && m_ResizeData.last_cursor != cursor_name)
//             {
//                 HCURSOR cursor = LoadCursor(0, cursor_name);
// 
//                 ::SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)cursor);
//                 m_ResizeData.last_cursor = cursor_name;
//             }
        }

//         // update tool tip position
//         int nDesktop, nIcon;
//         TCHAR window_name[MAX_PATH];
// 
//         // move tooltip window
//         CPoint tooltip_pos(pt);
// 
//         ClientToScreen(&tooltip_pos);
// 
//         tooltip_pos.x += 16;
//         tooltip_pos.y += 16;
// 
//         m_ToolTip.SetToolTipPosition(tooltip_pos);

//         /* if cursors hovers some window icon */
// 
//         GetDesktopIconByPoint(point, nDesktop, nIcon);
// 
//         if (nIcon >= 0)
//         {
//             /* update */
//             if ((m_nPrevTooltipDesktop != nDesktop) ||
//                 (m_nPrevTooltipIcon != nIcon))
//             {
//                 HWND hWnd = GetWindowByDesktopIcon(nDesktop, nIcon);
// 
//                 m_hHoveredWindow = hWnd;
// 
//                 ::GetWindowText(hWnd, window_name, MAX_PATH);
// 
//                 m_ToolTip.UpdateToolTipText(window_name);
// 
//                 m_ToolTip.ShowToolTip(TRUE);
//                 bTooltipVisible = true;
// 
//                 SetTooltipTimer();
// 
//                 m_nPrevTooltipDesktop = nDesktop;
//                 m_nPrevTooltipIcon    = nIcon;
//             }
//         }
//         else if (bTooltipVisible)
//         {
//             m_ToolTip.ShowToolTip(FALSE);
//             bTooltipVisible = false;
//             m_hHoveredWindow = 0;
//         }

    }
}

int ikonized::MainWindow::endWindowMoving(void )
{
	Q_ASSERT(m_State == STATE_MOVE);
	m_State = STATE_IDLE;
	return 0;
}

int ikonized::MainWindow::getDesktopByPoint(const QPoint& point)
{
    for (int i=1; i < m_Desktops.size(); i++)
    {
        if (m_Desktops[i].m_OveralRegion.contains(point))
        {
            return i;
        }
    }

    return -1;
}

void ikonized::MainWindow::getDesktopIconByPoint(const QPoint & point, 
                                         int & desktop,
                                         int & icon,
                                         QPoint * p_icon_drag_point /* = NULL*/)
{
    icon = -1;
    desktop = getDesktopByPoint(point);

    int x = point.x();
    int y = point.y();

    int row;
    int col;

    if (desktop > 0)
    {
        Q_ASSERT(desktop < m_Desktops.size());

        if (m_Desktops[desktop].m_nWindowsCount > 0)
        {
            // find the icon within desktop
            x -= m_Desktops[desktop].m_InnerRegion.left();
            y -= m_Desktops[desktop].m_InnerRegion.top();

            row = y / ICON_REGION_HEIGH;
            col = x / ICON_REGION_WIDTH;

            if (p_icon_drag_point)
            {
                *p_icon_drag_point = QPoint(x % ICON_REGION_WIDTH, y % ICON_REGION_HEIGH);
            }

            int icons_per_row = m_Desktops[desktop].m_InnerRegion.width() / (ICON_REGION_WIDTH);

            if (icons_per_row > col)
            {
                icon = row * icons_per_row + col;

                if (icon >= m_Desktops[desktop].m_nWindowsCount)
                {
                    icon = -1;
                }
            }
        }
    }
}

WId ikonized::MainWindow::getWindowByDesktopIcon(int desktop, int icon, WindowInfo ** windowInfo)
{
    Q_ASSERT(desktop < m_Desktops.size());
    
    if (m_Desktops[desktop].m_nWindowsCount > 0)
    {
        for (WindowInfoCollection::iterator iter = m_windowInfo.begin(); iter != m_windowInfo.end(); iter++)
        {
            WindowInfo &win = *iter;

            /* ignore sticky windows if they are not visible */
            /* ignore hidden windows */
            if (!mShowAllDesktopWindows && win.mIsAllDesktops)
            {
                continue;
            }

            if (win.mDesktop == desktop)
            {
                icon--;

                if (icon < 0)
                {
                    if (windowInfo != NULL)
                    {
                        *windowInfo = &win;
                    }

                    return iter->mId;
                }
            }
        }

    }
    return NULL;
}

int  ikonized::MainWindow::setDragMode(WId hTargetWnd, const QPoint &position)
{
    Q_ASSERT(m_State == STATE_IDLE);
    m_State = STATE_DRAG_ICON;

    m_DragData.target_window = hTargetWnd;

//     m_DragData.icon = GetWindowIcon(hTargetWnd);

    m_DragData.position = position - m_DragData.icon_point;

//     m_DraggingIconWnd.SetIcon(m_DragData.icon, m_bSmalIcons ? SMALL_ICON_SIZE : BIG_ICON_SIZE);
//     m_DraggingIconWnd.SetPosition(m_DragData.position.X, m_DragData.position.Y);
//     m_DraggingIconWnd.SetVisible(TRUE);

//     m_ToolTip.ShowToolTip(FALSE);

    return 0;
};

void ikonized::MainWindow::resetDragData(void)
{
    if (m_State == STATE_DRAG_ICON)
    {
        m_State = STATE_IDLE;

        // reset drag state
        m_DragData.reset();

//         StopDragMode();
    }
}

int ikonized::MainWindow::startWindowMoving(const QPoint & ancor_point)
{
    Q_ASSERT(m_State == STATE_IDLE);

    m_State = STATE_MOVE;

    m_MoveData.old_position = ancor_point;

    return 0;
}