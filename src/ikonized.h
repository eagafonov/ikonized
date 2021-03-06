//
// C++ Interface: ikonized
//
// Description: 
//
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZED_H
#define IKONIZED_H

#include <KApplication>
#include "mainwindow.h"

/**
    @author Eugene Agafonov
*/
class Ikonized: public KApplication
{
    Q_OBJECT
public:
    Ikonized();

    ~Ikonized();

private:
    ikonized::MainWindow mMainWindow;
};

#endif
