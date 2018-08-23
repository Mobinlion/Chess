
// drawing a lineDoc.h : interface of the CdrawingalineDoc class
//


#pragma once


class CdrawingalineDoc : public CDocument
{
protected: // create from serialization only
	CdrawingalineDoc();
	DECLARE_DYNCREATE(CdrawingalineDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CdrawingalineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


