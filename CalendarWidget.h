//
//  CalendarWidget.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef CalendarWidget_h
#define CalendarWidget_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CalendarWidgetDelegate;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CalendarWidget : public QCalendarWidget
{
	Q_OBJECT

public:
	// CalendarWidget
	CalendarWidget(QWidget* pParentWidget = nullptr);

	void SetDelegate(CalendarWidgetDelegate* pDelegate);

private Q_SLOTS:
	// CalendarWidget
	void SelectionChanged();

private:
	CalendarWidgetDelegate* m_pDelegate;
};

#endif // CalendarWidget_h
