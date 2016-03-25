//
//  SchedulerModelIndex.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "SchedulerModelIndex.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerModelIndex::SchedulerModelIndex(const QDateTime& dateTime) :
	m_dateTime(dateTime)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SchedulerModelIndex::~SchedulerModelIndex() 
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const QDateTime& 
SchedulerModelIndex::GetDateTime() const
{
	return m_dateTime;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::wstring 
SchedulerModelIndex::GetStringForColumn(size_t)
{
	return m_dateTime.toString().toStdWString();
}
