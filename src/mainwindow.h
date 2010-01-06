//
// C++ Interface: mainwindow
//
// Description: 
//
//
// Author:  <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZEDMAINWINDOW_H
#define IKONIZEDMAINWINDOW_H

#include <QWidget>
#include "windowinfo.h"

namespace ikonized {

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

private:
	WindowInfoCollection m_windowInfo;

	virtual void paintEvent( QPaintEvent *e );
	void resizeEvent (QResizeEvent * event);

	int mDesktopCount;
	int mCurrentDesktop;
	bool mShowAllDesktopWindows;
	void updateWindowInfo();
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
	int m_IconWidth;
	int m_IconHeight;
};

}

#endif
