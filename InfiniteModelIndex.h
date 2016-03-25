//
//  InfiniteModelIndex.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef InfiniteModelIndex_h
#define InfiniteModelIndex_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteModelIndex
{
public:
	// InfiniteModelIndex
	virtual ~InfiniteModelIndex() {};

	virtual const std::wstring GetStringForColumn(size_t uColumnIndex) = 0;
};

#endif // InfiniteModelIndex_h
