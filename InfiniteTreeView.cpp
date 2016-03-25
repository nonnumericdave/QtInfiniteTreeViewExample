//
//  InfiniteTreeView.cpp
//  Scheduler
//
//  Created by David Flores on 1/23/16.
//  Copyright © 2016 David Flores. All rights reserved.
//

#include "stdafx.h"

#include "InfiniteTreeView.h"

#include "InfiniteController.h"
#include "InfiniteModel.h"
#include "InfiniteModelIndex.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const size_t g_kuAllocatedRowCount = 512*3;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InfiniteTreeView::PrivateModel : public QAbstractItemModel
{
public:
	// PrivateModel
	PrivateModel();
	virtual ~PrivateModel();

	void SetModel(InfiniteModel* pModel);
	void ScrollToIndex(InfiniteModelIndex* pRowIndex);
	void ScrollIndicesByOffset(int iRowOffset);
	InfiniteModelIndex* GetInfiniteModelIndex(const QModelIndex& modelIndex) const;

private:
	// QAbstractItemModel
	virtual QModelIndex index(int iRow, int iColumn, const QModelIndex& modelIndexParent) const override;
	virtual QModelIndex parent(const QModelIndex& modelIndexChild) const override;
	virtual int rowCount(const QModelIndex& modelIndexParent) const override;
	virtual int columnCount(const QModelIndex& modelIndexParent) const override;
	virtual QVariant data(const QModelIndex& modelIndex, int iItemDataRole) const override;

	// PrivateModel
	size_t GetAdjustedVectorIndex(size_t uVectorVirtualIndex) const;

	InfiniteModel* m_pModel;
	std::vector<InfiniteModelIndex*> m_vectorModelIndices;
	size_t m_uVectorZeroIndex;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteTreeView::PrivateModel::PrivateModel() :
	m_pModel(nullptr),
	m_vectorModelIndices(g_kuAllocatedRowCount),
	m_uVectorZeroIndex(0)
{
	for ( auto& iterator : m_vectorModelIndices )
		iterator = nullptr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteTreeView::PrivateModel::~PrivateModel()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::PrivateModel::SetModel(InfiniteModel* pModel)
{
	m_pModel = pModel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
InfiniteTreeView::PrivateModel::ScrollToIndex(InfiniteModelIndex* pRowIndex)
{
	if ( m_pModel == nullptr || pRowIndex == nullptr )
		return;

	m_uVectorZeroIndex = 0;

	size_t uFirstVisibleIndex = g_kuAllocatedRowCount/3;
	InfiniteModelIndex* pCurrentRowIndex = pRowIndex;

	size_t uIndex = uFirstVisibleIndex;
	size_t uIndexVectorSize = m_vectorModelIndices.size();

	for ( ; pCurrentRowIndex != nullptr; uIndex-- )
	{
		delete m_vectorModelIndices[uIndex];

		m_vectorModelIndices[uIndex] = pCurrentRowIndex;

		if ( uIndex == 0 )
			break;

		pCurrentRowIndex = m_pModel->CreateIndexBeforeIndex(pCurrentRowIndex);
	}

	uIndex = uFirstVisibleIndex + 1;
	pCurrentRowIndex = pRowIndex;

	for ( ; uIndex < uIndexVectorSize; uIndex++ )
	{
		pCurrentRowIndex = m_pModel->CreateIndexAfterIndex(pCurrentRowIndex);

		delete m_vectorModelIndices[uIndex];

		m_vectorModelIndices[uIndex] = pCurrentRowIndex;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::PrivateModel::ScrollIndicesByOffset(int iRowOffset)
{
	size_t uPreviousVectorZeroIndex = m_uVectorZeroIndex;
	size_t uPreviousVectorLastIndex = GetAdjustedVectorIndex(g_kuAllocatedRowCount - 1);

	m_uVectorZeroIndex = static_cast<size_t>(m_uVectorZeroIndex + iRowOffset + g_kuAllocatedRowCount) % g_kuAllocatedRowCount;

	if ( iRowOffset > 0 )
	{
		size_t uFillIndex = uPreviousVectorZeroIndex;
		size_t uStopFillIndex = m_uVectorZeroIndex;

		InfiniteModelIndex* pFillModelIndex = m_vectorModelIndices[uPreviousVectorLastIndex];
		while ( uFillIndex != uStopFillIndex )
		{
			delete m_vectorModelIndices[uFillIndex];
			pFillModelIndex = m_pModel->CreateIndexAfterIndex(pFillModelIndex);
			m_vectorModelIndices[uFillIndex] = pFillModelIndex;
			uFillIndex = (uFillIndex + 1) % g_kuAllocatedRowCount;
		}
	}
	else if ( iRowOffset < 0 )
	{
		size_t uFillIndex = (uPreviousVectorZeroIndex + g_kuAllocatedRowCount - 1) % g_kuAllocatedRowCount;
		size_t uStopFillIndex = (m_uVectorZeroIndex + g_kuAllocatedRowCount - 1) % g_kuAllocatedRowCount;

		InfiniteModelIndex* pFillModelIndex = m_vectorModelIndices[uPreviousVectorZeroIndex];
		while ( uFillIndex != uStopFillIndex )
		{
			delete m_vectorModelIndices[uFillIndex];
			pFillModelIndex = m_pModel->CreateIndexBeforeIndex(pFillModelIndex);
			m_vectorModelIndices[uFillIndex] = pFillModelIndex;
			uFillIndex = (uFillIndex + g_kuAllocatedRowCount - 1) % g_kuAllocatedRowCount;
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteModelIndex* 
InfiniteTreeView::PrivateModel::GetInfiniteModelIndex(const QModelIndex& modelIndex) const
{
	if ( ! modelIndex.isValid() )
		return nullptr;

	int iRowIndex = modelIndex.row();
	assert(iRowIndex >= 0);
	size_t uRowIndex = static_cast<size_t>(iRowIndex);
	size_t uAdjustedRowIndex = GetAdjustedVectorIndex(uRowIndex);

	assert(uAdjustedRowIndex >=0 && uAdjustedRowIndex < g_kuAllocatedRowCount);

	return m_vectorModelIndices[uAdjustedRowIndex];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
QModelIndex
InfiniteTreeView::PrivateModel::index(int iRow, int iColumn, const QModelIndex&) const
{
	return createIndex(iRow, iColumn, nullptr);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
QModelIndex
InfiniteTreeView::PrivateModel::parent(const QModelIndex&) const
{
	return QModelIndex();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
InfiniteTreeView::PrivateModel::rowCount(const QModelIndex& modelIndexParent) const
{
	if ( modelIndexParent.isValid() || m_pModel == nullptr )
		return 0;

	assert(g_kuAllocatedRowCount <= std::numeric_limits<int>::max());
	return static_cast<int>(g_kuAllocatedRowCount);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int
InfiniteTreeView::PrivateModel::columnCount(const QModelIndex& modelIndexParent) const
{
	if ( modelIndexParent.isValid() || m_pModel == nullptr )
		return 0;

	size_t uColumnCount = m_pModel->GetColumnCount();
	assert(uColumnCount <= std::numeric_limits<int>::max());
	return static_cast<int>(uColumnCount);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
QVariant
InfiniteTreeView::PrivateModel::data(const QModelIndex& modelIndex, int iItemDataRole) const
{
	if ( iItemDataRole != Qt::DisplayRole || m_pModel == nullptr )
		return QVariant(QVariant::Type::Invalid);

	int iRowIndex = modelIndex.row();
	assert(iRowIndex >= 0);
	size_t uRowIndex = static_cast<size_t>(iRowIndex);
	size_t uAdjustedRowIndex = GetAdjustedVectorIndex(uRowIndex);
	
	InfiniteModelIndex* pInfiniteModelIndex = m_vectorModelIndices[uAdjustedRowIndex];
	if ( pInfiniteModelIndex == nullptr )
		return QVariant(QVariant::Type::Invalid);

	int iColumnIndex = modelIndex.column();
	assert(iColumnIndex >= 0);
	size_t uColumnIndex = static_cast<size_t>(iColumnIndex);

	const std::wstring& wszData = pInfiniteModelIndex->GetStringForColumn(uColumnIndex);

	return QVariant(QString::fromStdWString(wszData));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
size_t
InfiniteTreeView::PrivateModel::GetAdjustedVectorIndex(size_t uVectorVirtualIndex) const
{
	return (m_uVectorZeroIndex + uVectorVirtualIndex) % g_kuAllocatedRowCount;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteTreeView::InfiniteTreeView(QWidget* pParentWidget) :
	QTreeView(pParentWidget),
	m_pPrivateModel(new PrivateModel),
	m_bCurrentIndexIsChanging(false),
	m_pController(nullptr)
{
	setModel(m_pPrivateModel);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setHeaderHidden(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRootIsDecorated(false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
InfiniteTreeView::~InfiniteTreeView()
{
	delete m_pPrivateModel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::SetController(InfiniteController* pController)
{
	m_pController = pController;

	if ( pController == nullptr )
		return;

	InfiniteModel* pModel = pController->GetModel();
	m_pPrivateModel->SetModel(pModel);

	if ( pModel == nullptr )
		return;

	m_pPrivateModel->ScrollToIndex(pModel->CreateInitialModelIndex());

	size_t uFirstVisibleRowIndex = g_kuAllocatedRowCount / 3;
	assert(uFirstVisibleRowIndex <= std::numeric_limits<int>::max());
	int iFirstVisibleRowIndex = static_cast<int>(uFirstVisibleRowIndex);

	QModelIndex modelIndex = model()->index(iFirstVisibleRowIndex, 0);
	scrollTo(modelIndex, QAbstractItemView::PositionAtTop);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void
InfiniteTreeView::ScrollToIndex(InfiniteModelIndex* pRowIndex)
{
	m_pPrivateModel->ScrollToIndex(pRowIndex);

	RefreshVisibleArea(true);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::UpdateCurrentItem()
{
	// Under certain circumstances, the current item may be updated, however, the visual
	//  decorations for the current item will not be displayed.  We effectively
	//  have to redo the setting of the current item outside of scrollContentsBy(...)
	//  in order for the decorations to get displayed correctly.  That said, we only
	//  update if the current item is still visible.
	QRect rectCurrentIndexInViewport = visualRect(m_currentModelIndex);

	if ( ! rectCurrentIndexInViewport.isEmpty() )
		selectionModel()->setCurrentIndex(m_currentModelIndex, QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::scrollContentsBy(int iDeltaX, int iDeltaY)
{
	if ( m_bCurrentIndexIsChanging )
		return;

	QTreeView::scrollContentsBy(iDeltaX, iDeltaY);

	size_t uFirstVisibleRowIndex = g_kuAllocatedRowCount / 3;
	assert(uFirstVisibleRowIndex <= std::numeric_limits<int>::max());
	int iFirstVisibleRowIndex = static_cast<int>(uFirstVisibleRowIndex);

	QModelIndex updatedFirstVisibleModelIndex = indexAt(rect().topLeft());

	int iRowOffset = updatedFirstVisibleModelIndex.row() - iFirstVisibleRowIndex;
	if ( iRowOffset == 0 )
		return;
	
	QModelIndex currentModelIndex = selectionModel()->currentIndex();
	if ( currentModelIndex.isValid() )
	{
		int iUpdatedCurrentItemIndex = currentModelIndex.row() - iRowOffset;
		m_currentModelIndex = model()->index(iUpdatedCurrentItemIndex, 0);

		m_bCurrentIndexIsChanging = true;
		selectionModel()->setCurrentIndex(m_currentModelIndex, QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows);
		m_bCurrentIndexIsChanging = false;

		QTimer::singleShot(0, this, SLOT(UpdateCurrentItem()));
	}

	m_pPrivateModel->ScrollIndicesByOffset(iRowOffset);

	QModelIndex modelIndex = model()->index(iFirstVisibleRowIndex, 0);
	scrollTo(modelIndex, QAbstractItemView::PositionAtTop);

	RefreshVisibleArea(true);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void 
InfiniteTreeView::RefreshVisibleArea(bool bUpdatingDisplayRange)
{
	QModelIndex firstVisibleModelIndex = indexAt(rect().topLeft());
	QModelIndex lastVisibleModelIndex = indexAt(rect().bottomLeft());
	dataChanged(firstVisibleModelIndex, lastVisibleModelIndex);

	if ( ! bUpdatingDisplayRange )
		return;
	
	InfiniteModelIndex* pFirstVisibleModelIndex = m_pPrivateModel->GetInfiniteModelIndex(firstVisibleModelIndex);
	InfiniteModelIndex* pLastVisibleModelIndex = m_pPrivateModel->GetInfiniteModelIndex(lastVisibleModelIndex);

	m_pController->DisplayingIndexRange(pFirstVisibleModelIndex, pLastVisibleModelIndex);
}
