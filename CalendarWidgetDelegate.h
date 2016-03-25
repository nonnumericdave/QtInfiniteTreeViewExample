//
//  CalendarWidgetDelegate.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef CalendarWidgetDelegate_h
#define CalendarWidgetDelegate_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CalendarWidgetDelegate
{
public:
	// CalendarWidgetDelegate
	virtual ~CalendarWidgetDelegate() {};

	virtual void DisplayingDate(const QDate& date) = 0;
};

#endif // CalendarWidgetDelegate_h
