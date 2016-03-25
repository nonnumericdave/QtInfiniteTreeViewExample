//
//  MainWindow.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h

#include "SchedulerModel.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SchedulerController;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace Ui
{ 
	class MainWindow; 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	// MainWindow
	MainWindow();
	~MainWindow();

private:
	Ui::MainWindow* m_pui;

	SchedulerController* m_pSchedulerController;
};

#endif // MainWindow_h
