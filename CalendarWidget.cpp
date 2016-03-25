//
//  CalendarWidget.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "CalendarWidget.h"

#include "CalendarWidgetDelegate.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CalendarWidget::CalendarWidget(QWidget* pParentWidget) :
	QCalendarWidget(pParentWidget),
	m_pDelegate(nullptr)
{
	connect(this, SIGNAL(selectionChanged()), this, SLOT(SelectionChanged()));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
CalendarWidget::SetDelegate(CalendarWidgetDelegate* pDelegate)
{
	m_pDelegate = pDelegate;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
CalendarWidget::SelectionChanged()
{
	if ( m_pDelegate == nullptr )
		return;

	m_pDelegate->DisplayingDate(selectedDate());
}
