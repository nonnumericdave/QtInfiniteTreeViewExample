//
//  InfiniteController.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef InfiniteController_h
#define InfiniteController_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteModel;
class InfiniteModelIndex;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteController
{
public:
	// InfiniteController
	virtual ~InfiniteController() {};

	virtual InfiniteModel* GetModel() const = 0;
	virtual void DisplayingIndexRange(InfiniteModelIndex* pFirstVisibleIndex, InfiniteModelIndex* pLastVisibleIndex) = 0;
};

#endif // InfiniteController_h
