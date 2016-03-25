//
//  SchedulerController.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "SchedulerController.h"

#include "CalendarWidget.h"
#include "InfiniteModelIndex.h"
#include "InfiniteTreeView.h"
#include "SchedulerModel.h"
#include "SchedulerModelIndex.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerController::SchedulerController(CalendarWidget* pCalendarWidget, InfiniteTreeView* pInfiniteTreeView) :
	m_pCalendarWidget(pCalendarWidget),
	m_pInfiniteTreeView(pInfiniteTreeView),
	m_pSchedulerModel(new SchedulerModel),
	m_bCurrentlyDisplayingDate(false),
	m_bCurrentlyDisplayingIndexRange(false)
{
	m_pCalendarWidget->SetDelegate(this);
	m_pInfiniteTreeView->SetController(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerController::~SchedulerController()
{
	delete m_pSchedulerModel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
SchedulerController::DisplayingDate(const QDate& date)
{
	if ( m_bCurrentlyDisplayingIndexRange )
		return;

	m_bCurrentlyDisplayingDate = true;

	QDateTime dateTime(date, QTime(0, 0));

	m_pInfiniteTreeView->ScrollToIndex(new SchedulerModelIndex(dateTime));

	m_bCurrentlyDisplayingDate = false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteModel* 
SchedulerController::GetModel() const
{
	return m_pSchedulerModel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
SchedulerController::DisplayingIndexRange(InfiniteModelIndex* pFirstVisibleIndex, InfiniteModelIndex*)
{
	if ( m_bCurrentlyDisplayingDate )
		return;

	if ( pFirstVisibleIndex == nullptr )
		return;

	m_bCurrentlyDisplayingIndexRange = true;

	assert(dynamic_cast<const SchedulerModelIndex*>(pFirstVisibleIndex) != nullptr);
	const SchedulerModelIndex* pFirstVisibleSchedulerModelIndex = static_cast<const SchedulerModelIndex*>(pFirstVisibleIndex);
	
	QDateTime dateTimeFirstVisible = pFirstVisibleSchedulerModelIndex->GetDateTime();
	QDate dateFirstVisible = dateTimeFirstVisible.date();

	if ( m_pCalendarWidget->selectedDate() != dateFirstVisible )
		m_pCalendarWidget->setSelectedDate(dateFirstVisible);

	m_bCurrentlyDisplayingIndexRange = false;
}
