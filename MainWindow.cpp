//
//  MainWindow.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "SchedulerController.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MainWindow::MainWindow()
{
	m_pui = new Ui::MainWindow;
	m_pui->setupUi(this);

	setUnifiedTitleAndToolBarOnMac(true);

	m_pSchedulerController = new SchedulerController(m_pui->pCalendarWidget, m_pui->pTreeView);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MainWindow::~MainWindow()
{
	delete m_pSchedulerController;

	delete m_pui;
}
