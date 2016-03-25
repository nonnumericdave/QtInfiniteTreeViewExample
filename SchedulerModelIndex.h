//
//  SchedulerModelIndex.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef SchedulerModelIndex_h
#define SchedulerModelIndex_h

#include "InfiniteModelIndex.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SchedulerModelIndex : public InfiniteModelIndex
{
public:
	// SchedulerModelIndex
	SchedulerModelIndex(const QDateTime& dateTime);

	virtual ~SchedulerModelIndex();

	const QDateTime& GetDateTime() const;

private:
	// InfiniteModelIndex
	virtual const std::wstring GetStringForColumn(size_t) override;

	QDateTime m_dateTime;
};

#endif // SchedulerModelIndex_h
