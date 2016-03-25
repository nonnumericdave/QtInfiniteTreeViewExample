//
//  main.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "MainWindow.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int 
main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setAttribute(Qt::AA_MacDontSwapCtrlAndMeta, true);

	MainWindow mw;
	mw.show();

	app.exec();

	return 0;
}
