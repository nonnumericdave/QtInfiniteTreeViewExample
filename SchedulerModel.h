//
//  SchedulerModel.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef SchedulerModel_h
#define SchedulerModel_h

#include "InfiniteModel.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SchedulerModel :	public InfiniteModel
{
public:
	// SchedulerModel
	SchedulerModel();
	virtual ~SchedulerModel();

private:
	// InfiniteModel
	virtual size_t GetColumnCount() override;
	virtual InfiniteModelIndex* CreateInitialModelIndex() override;
	virtual InfiniteModelIndex* CreateIndexBeforeIndex(const InfiniteModelIndex* pNextRowIndex) override;
	virtual InfiniteModelIndex* CreateIndexAfterIndex(const InfiniteModelIndex* pPreviousRowIndex) override;
};

#endif // SchedulerModel_h
