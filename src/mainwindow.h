//
// C++ Interface: mainwindow
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDMAINWINDOW_H
#define IKONIZEDMAINWINDOW_H

#include <QWidget>
#include <KActionCollection>

#include "windowinfo.h"

namespace ikonized {

class SkinBase;

/**
	@author 
*/
class MainWindow : public QWidget
{
	Q_OBJECT
public:
    MainWindow();

    ~MainWindow();

public slots:
    void currentDesktopChanged(int);
    void windowAdded(WId);
    void windowRemoved(WId);
    void activeWindowChanged(WId);
    void numberOfDesktopsChanged(int);
    void desktopNamesChanged();
    void stackingOrderChanged();
    void windowChanged(WId ,unsigned int);
    void showingDesktopChanged(bool);

	void onHotKey();
	void onConfigureDesktops();
    void menuOptions();

private:
	WindowInfoCollection m_windowInfo;
	void updateWindowInfo();

	int mDesktopCount;
	int mCurrentDesktop;
	WId mSelfWid;
	bool mShowAllDesktopWindows;

	void drawContent(QPainter &painter);
	bool getDesktopIconRect(int n, const QRect &outer_rect, QRect &icon_rect);


    typedef struct DESKTOPSTRUCTtag
    {
        QRect m_OveralRegion;
        QRect m_InnerRegion;    // TODO let skin manage this region internally
        int m_nWindowsCount; // number of windows on desktop
        size_t m_Hash;
        size_t m_PrevHash;
    } DESKTOPSTRUCT;

    QVector<DESKTOPSTRUCT> m_Desktops;
    void updateDesktopRegions(const QSize &size);
	int  getDesktopByPoint(const QPoint& point);
	void getDesktopIconByPoint(const QPoint & point,
                               int & desktop,
                               int & icon,
                               QPoint * p_icon_drag_point = NULL);
    WId getWindowByDesktopIcon(int desktop, int icon, WindowInfo ** windowInfo = NULL);

	
	// Icon stuff
	int m_IconWidth;
	int m_IconHeight;

	// Mouse handling stuff
	QPoint m_MousePressPosition;
	bool m_bLeftButtonPressed;

    class  ResizeData
    {
    public:
        bool ready;
		QSize original_size;
        int min_w;
        int min_h;
        
//         LPCTSTR last_cursor;
        
        ResizeData()
        {
            ready = false;
//             last_cursor = 0;
        }
    } m_ResizeData;


    class DragData
    {
    public:
        WId target_window;
//      HICON icon;
        QPoint position;
        QPoint icon_point;

        void reset()
        {
	           target_window = 0;
//             icon = NULL;
        }
    } m_DragData;

	int  setDragMode(WId hTargetWnd, const QPoint &position);
	void resetDragData(void);


    class  MoveData
    {
    public:
        QPoint old_position;
    } m_MoveData;

	int startWindowMoving(const QPoint & ancor_point);

    typedef enum 
    {
        STATE_IDLE,
        STATE_DRAG_ICON,
        STATE_MOVE,
        STATE_RESIZE,
        STATE_VRESIZE,
        STATE_HRESIZE,
    } STATE_T;

    STATE_T m_State;
	
	int endWindowMoving(void);


	// Context menun stuff
	bool mMenuOpen;

	// hotkeys
	KActionCollection mActions;

	// Tooltip
	int m_nTooltipDesktop;
    int m_nTooltipIcon;

    // Options
    bool mOptionsDlgDisplyed;
    void readSettings();

	// Events from QWidgets
	virtual void paintEvent( QPaintEvent *e );
	virtual void resizeEvent (QResizeEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void contextMenuEvent(QContextMenuEvent *event);
	virtual void closeEvent(QCloseEvent *event);

    // skin 
    SkinBase *m_pSkin;
    QSize mCellSize;

    int setSkin(SkinBase *pNewSkin);
    int updateSkinMetrics();
    void preparePainter(QPainter &painter, int desktop);
};

}

#endif
