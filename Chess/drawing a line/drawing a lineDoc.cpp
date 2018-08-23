
// drawing a lineDoc.cpp : implementation of the CdrawingalineDoc class
//

#include "stdafx.h"
#include "drawing a line.h"

#include "drawing a lineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdrawingalineDoc

IMPLEMENT_DYNCREATE(CdrawingalineDoc, CDocument)

BEGIN_MESSAGE_MAP(CdrawingalineDoc, CDocument)
END_MESSAGE_MAP()


// CdrawingalineDoc construction/destruction

CdrawingalineDoc::CdrawingalineDoc()
{
	// TODO: add one-time construction code here

}

CdrawingalineDoc::~CdrawingalineDoc()
{
}

BOOL CdrawingalineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CdrawingalineDoc serialization

void CdrawingalineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CdrawingalineDoc diagnostics

#ifdef _DEBUG
void CdrawingalineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CdrawingalineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CdrawingalineDoc commands
