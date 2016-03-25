//
//  InfiniteTreeView.h
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#ifndef InfiniteTreeView_h
#define InfiniteTreeView_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteController;
class InfiniteModelIndex;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteTreeView : public QTreeView
{
	Q_OBJECT

public:
	// InfiniteTreeView
	InfiniteTreeView(QWidget* pParentWidget = nullptr);
	virtual ~InfiniteTreeView();

	void SetController(InfiniteController* pController);
	void ScrollToIndex(InfiniteModelIndex* pRowIndex);

private Q_SLOTS:
	// InfiniteTreeView
	void UpdateCurrentItem();

private:
	// QAbstractScrollArea
	virtual void scrollContentsBy(int iDeltaX, int iDeltaY) override;

	// InfiniteTreeView
	void RefreshVisibleArea(bool bUpdatingDisplayRange);

	class PrivateModel;
	PrivateModel* m_pPrivateModel;

	bool m_bCurrentIndexIsChanging;
	QModelIndex m_currentModelIndex;

	InfiniteController* m_pController;
};

#endif // InfiniteTreeView_h
