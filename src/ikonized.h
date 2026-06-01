//
// C++ Interface: ikonized
//
// Author: Eugene Agafonov <e.a.agafonov@gmail.com> (C) 2009-2020
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef IKONIZED_H
#define IKONIZED_H

#include <QApplication>
#include "mainwindow.h"

class Ikonized: public QApplication
{
    Q_OBJECT
public:
    Ikonized(int &argc, char **argv);
    ~Ikonized();

private:
    ikonized::MainWindow mMainWindow;
};

#endif
