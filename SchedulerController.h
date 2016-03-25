//
//  SchedulerController.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef SchedulerController_h
#define SchedulerController_h

#include "CalendarWidgetDelegate.h"
#include "InfiniteController.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CalendarWidget;
class InfiniteTreeView;
class SchedulerModel;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SchedulerController : public CalendarWidgetDelegate, public InfiniteController 
{
public:
	// SchedulerController
	SchedulerController(CalendarWidget* pCalendarWidget, InfiniteTreeView* pInfiniteTreeView);

	virtual ~SchedulerController();

private:
	// CalendarWidgetDelegate
	virtual void DisplayingDate(const QDate& date) override;

	// InfiniteController
	virtual InfiniteModel* GetModel() const override;
	virtual void DisplayingIndexRange(InfiniteModelIndex* pFirstVisibleIndex, InfiniteModelIndex* pLastVisibleIndex) override;

	CalendarWidget* m_pCalendarWidget;
	InfiniteTreeView* m_pInfiniteTreeView;
	SchedulerModel* m_pSchedulerModel;

	bool m_bCurrentlyDisplayingDate;
	bool m_bCurrentlyDisplayingIndexRange;
};

#endif // SchedulerController_h
