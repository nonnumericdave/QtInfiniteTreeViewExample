//
//  InfiniteModel.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef InfiniteModel_h
#define InfiniteModel_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteModelIndex;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteModel
{
public:
	// InfiniteModel
	virtual ~InfiniteModel() {};

	virtual size_t GetColumnCount() = 0;
	virtual InfiniteModelIndex* CreateInitialModelIndex() = 0;
	virtual InfiniteModelIndex* CreateIndexBeforeIndex(const InfiniteModelIndex* pNextRowIndex) = 0;
	virtual InfiniteModelIndex* CreateIndexAfterIndex(const InfiniteModelIndex* pPreviousRowIndex) = 0;
};

#endif // InfiniteModel_h
