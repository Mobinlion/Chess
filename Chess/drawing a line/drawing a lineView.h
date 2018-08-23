
// drawing a lineView.h : interface of the CdrawingalineView class
//


#pragma once
enum pieces;

class CdrawingalineView : public CView
{
protected: // create from serialization only
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnInitialUpdate();
	CdrawingalineView();
	DECLARE_DYNCREATE(CdrawingalineView)

// Attributes
public:
	CRgn rgn;
	CImageList image;
	CImage ci;
	CBitmap bmp;
	CScrollBar bar;
	void kaboom(CDC *dc,CPoint point);
	void draw (CDC*);
	void initialize(CDC*);
	void movepiece(CDC* dc, POINT pnt, POINT pnt_data,  pieces pc);
	int greenpiece(CDC*dc, POINT point);
	void drawpiece(CDC*dc, int i, int j);
	void checkvalidmove(CDC* dc, POINT point);
	void drawgreen(CDC*dc,int i, int j);
	void pawnmove();
	void removegreen();
	
	CdrawingalineDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	//virtual void OnCreate(LPCREATESTRUCT lpcs);

// Implementation
public:
	virtual ~CdrawingalineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in drawing a lineView.cpp
inline CdrawingalineDoc* CdrawingalineView::GetDocument() const
   { return reinterpret_cast<CdrawingalineDoc*>(m_pDocument); }
#endif


enum pieces {

	NONE=0, ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP2, KNIGHT2, ROOK2, PAWN
};

typedef struct _Player
{

	CRect point;
	pieces piece;
	bool green;
	bool black;
	bool white;
	

}Player, *PPlayer;