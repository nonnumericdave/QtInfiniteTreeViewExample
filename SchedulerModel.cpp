//
//  SchedulerModel.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "SchedulerModel.h"

#include "SchedulerModelIndex.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const int g_kiMinuteQuantum = 30;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerModel::SchedulerModel()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerModel::~SchedulerModel()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
size_t 
SchedulerModel::GetColumnCount()
{
	return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteModelIndex* 
SchedulerModel::CreateInitialModelIndex()
{
	QDateTime dateTimeCurrent(QDateTime::currentDateTime());

	QDate dateCurrent(dateTimeCurrent.date());
		
	QTime timeCurrent(dateTimeCurrent.time());

	int iCurrentMinute = timeCurrent.minute();
	QTime timeCurrentFloored(timeCurrent.hour(), iCurrentMinute - (iCurrentMinute % g_kiMinuteQuantum));

	return new SchedulerModelIndex(QDateTime(dateCurrent, timeCurrentFloored));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteModelIndex* 
SchedulerModel::CreateIndexBeforeIndex(const InfiniteModelIndex* pNextModelIndex)
{
	if ( pNextModelIndex == nullptr )
		return nullptr;

	assert(dynamic_cast<const SchedulerModelIndex*>(pNextModelIndex) != nullptr);
	const SchedulerModelIndex* pNextSchedulerModelIndex = static_cast<const SchedulerModelIndex*>(pNextModelIndex);

	return new SchedulerModelIndex(pNextSchedulerModelIndex->GetDateTime().addSecs(-60*g_kiMinuteQuantum));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteModelIndex* 
SchedulerModel::CreateIndexAfterIndex(const InfiniteModelIndex* pPreviousModelIndex)
{
	if ( pPreviousModelIndex == nullptr )
		return nullptr;

	assert(dynamic_cast<const SchedulerModelIndex*>(pPreviousModelIndex) != nullptr);
	const SchedulerModelIndex* pPreviousSchedulerModelIndex = static_cast<const SchedulerModelIndex*>(pPreviousModelIndex);

	return new SchedulerModelIndex(pPreviousSchedulerModelIndex->GetDateTime().addSecs(60*g_kiMinuteQuantum));
}
