
// drawing a lineView.cpp : implementation of the CdrawingalineView class
//

#include "stdafx.h"
#include "drawing a line.h"

#include "drawing a lineDoc.h"
#include "drawing a lineView.h"
#include "math.h"

int arrSinus[1000];
int iTime=0;

#define valx 80
#define valy 80
POINT CurrentMousePos = {0};
POINT origin = {0};
POINT origin2 = {0};
bool BLACK= true;
bool Green = false;
int gi=0, gj=0;

Player data[8][8] = {0, NONE , false};

#ifdef _DEBGU
#define new DEBUG_NEW
#endif


void CdrawingalineView::drawpiece(CDC*dc, int i, int j)
{
	
	if(BLACK)
	{

		char temp[MAX_PATH];
		sprintf(temp, "C:\\Users\\captain\\Desktop\\chess pieces\\Black\\%d.bmp", (int)data[i][j].piece);

		CString szFilename (temp);

		HBITMAP hBmp = (HBITMAP)::LoadImageA(NULL, szFilename, IMAGE_BITMAP,  0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		CBitmap bmp;
		bmp.Attach(hBmp);

		CDC bmDC;
		bmDC.CreateCompatibleDC(dc);
		CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

		BITMAP  bi;
		bmp.GetBitmap(&bi);

		dc->BitBlt(data[i][j].point.left, data[i][j].point.top,bi.bmWidth,bi.bmHeight,&bmDC,0,0,SRCCOPY);

 		bmDC.SelectObject(pOldbmp);

	}

}


int CdrawingalineView::greenpiece(CDC *dc, POINT point)
{ 
	for ( int i = 0 ; i <8; i++)
			{
				for(int j = 0 ; j<8; j++)
				{
					if(PtInRect(data[i][j].point, point) && data[i][j].piece != NONE)
					 {								 
						 Green = true;
						 data[i][j].green = true;
						 gi = i;
						 gj = j;
						 return 1;
					}
				}
	}

	return  0;
}


void CdrawingalineView::drawgreen (CDC*dc, int i, int j)
{
	CBrush br(RGB(0,200,0));
	dc->SelectObject(&br);
	dc->Rectangle(data[i][j].point);
	data[i][j].green = true;

}

void CdrawingalineView::removegreen()
{
	for(int i = 0 ; i<8;i++)
	{
		for(int j = 0 ; j<8;j++) //also remove if not clicked on green pieces
		{			
			if(data[i][j].green)
			{
				this->InvalidateRect(data[i][j].point);
				data[i][j].green = false;
			}
		}
	}
}




void CdrawingalineView::pawnmove()
{
	//double jump is possible
	drawgreen(GetDC(),gi,gj);
	drawpiece(GetDC(), gi, gj);

	
	if(gi==1)
	{
		for(int i = 1 ; i<=2; i++)
		{
		 if(data[gi+i][gj].piece==NONE)
		 {
			 drawgreen(GetDC(), gi+i, gj);
		 }
		}		
	}
	else if(gi>1 && gi<7)
	{
		if(data[gi+1][gj].piece==NONE)
		 {
			 drawgreen(GetDC(), gi+1, gj);
		 }
	}
	
}

void CdrawingalineView::checkvalidmove(CDC*dc, POINT point)
{


	
	switch ((int)data[gi][gj].piece)
	{
	case PAWN:
		pawnmove();
		break;

	}
			
}

void CdrawingalineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	//CWnd::OnLButtonDown(nFlags,point);
	//MessageBox("123");
	//kaboom(&dc,point);
	//draw(NULL);

	if (!Green)
	{
		if(greenpiece(GetDC(), point))
		checkvalidmove(GetDC(),point);
	}

	else if (Green)
	{
		if(PtInRect(data[gi][gj].point, point))
	
		{
			removegreen();
			Green = false;
			drawpiece(GetDC(),gi,gj);
			return;	
		}
		
		else {

			for(int i = 0 ; i<8;i++)
			 {
				for ( int j = 0 ; j<8; j++)
				{
					if(PtInRect(data[i][j].point, point) && data[i][j].green )//none what if enemy piece
					{

						drawpiece(GetDC(), gi,gj);

						data[i][j].piece = data[gi][gj].piece;
						data[gi][gj].piece=NONE;
						data[i][j].green = false;
						Green = false;
						this->InvalidateRect(data[i][j].point);
						/*if(i==7)
						{
							MessageBox("can become anything");

						}*/

					}

				}
			}

		}
		for(int i = 0 ; i<8;i++)
		{
			for(int j = 0 ; j<8;j++)
		
			{
				if(PtInRect(data[i][j].point, point) && !data[i][j].green)
			
				{
					removegreen();
					Green=false;

				}
			}
		}
	}
}


void CdrawingalineView::initialize(CDC *dc)
{

	int pnum = 1;
	int ppiece = 1;
	char buf[MAX_PATH];

	for ( int i = 0; i <8; i++)
	{
		for ( int j = 0 ; j<8 ; j++)
		{
			if(data[i][j].green)
			drawgreen(GetDC(),i,j);
			if(data[i][j].piece != NONE)
			   drawpiece(dc,i,j);
			
		}

	}

}

void CdrawingalineView::draw(CDC *dc1)
{

	/*CString szFilename ("C:\\delta.bmp");
		HBITMAP hBmp = (HBITMAP)::LoadImageA(
                NULL,
                szFilename,
                IMAGE_BITMAP,
                0,
                0,
                LR_LOADFROMFILE|LR_CREATEDIBSECTION
                );

		CBitmap bmp;
		bmp.Attach(hBmp);

		CClientDC dc(this);
		CDC bmDC;
		bmDC.CreateCompatibleDC(&dc);
		CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

		BITMAP  bi;
		bmp.GetBitmap(&bi);

		dc.BitBlt(0,0,bi.bmWidth,bi.bmHeight,&bmDC,0,0,SRCCOPY);

 		bmDC.SelectObject(pOldbmp);*/


}


void CdrawingalineView::kaboom(CDC *dc,CPoint point)
{
	

	
	//static CPen pen_black(PS_SOLID,1,RGB(0,0,0));
	//static CPen pen_white(PS_SOLID,1,RGB(255,255,255));
	static CBrush brush_white(RGB(255,255,255));
	static CBrush brush_black(RGB(0,0,0));
	int x1= 0 ,y1=0, x2=valx, y2=valy;


	for ( int i = 0; i<4 ; i++)
	{

		for(int j = 0 ; j<4; j++)
		{

			//dc->SelectObject(&pen_black);
			dc->SelectObject(&brush_white);
			dc->Rectangle(x1,y1,x2,y2);
			x1+=valx;
			x2+=valx;
			//dc->SelectObject(&pen_white);
			dc->SelectObject(&brush_black);
			dc->Rectangle(x1,y1,x2,y2);
			x1+=valx;
			x2+=valx;

		}

		y1+=valy;
		y2+=valy;
		x1=0;
		x2=valx;

		for(int k = 0; k<4; k++)
		{
			//dc->SelectObject(&pen_white);
			dc->SelectObject(&brush_black);
			dc->Rectangle(x1,y1,x2,y2);
			x1+=valx;
			x2+=valx;
			//dc->SelectObject(&pen_black);
			dc->SelectObject(&brush_white);
			dc->Rectangle(x1,y1,x2,y2);
			x1+=valx;
			x2+=valx;
			
		}
		y1+=valy;
		y2+=valy;
		x1=0;
		x2=valx;

	}



	int x4= 0 ,y4=0, x5=valx, y5=valy;

	for(int i = 0; i <8; i++)
	{


		for(int j = 0 ; j<8 ; j++)
		{
			data[i][j].point.top = y4;
			data[i][j].point.bottom = y5;
			data[i][j].point.left = x4;
			data[i][j].point.right = x5;
			x4+=valx;
			x5+=valx;

		}

		y4+=valy;
		y5+=valy;
		x4=0;
		x5=valx;
	}


	initialize(dc);
	
	
}

// CdrawingalineView

IMPLEMENT_DYNCREATE(CdrawingalineView, CView)

BEGIN_MESSAGE_MAP(CdrawingalineView, CView)
	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
//	ON_WM_ERASEBKGND()
//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CdrawingalineView construction/destruction

CdrawingalineView::CdrawingalineView()
{
	memset(data, '\0', sizeof(data));
	int piecer = 1;
	for ( int i = 1; i >= 0; i--)
	{
		for ( int j = 0 ; j<8 ; j++)
		{
			if( i == 1 )
			{
				data[i][j].piece = PAWN;
			}
			else
			{
				data[i][j].piece = (pieces)piecer++;
			}
			data[i][j].black = true;

		}
	}

	// TODO: add construction code here

}

CdrawingalineView::~CdrawingalineView()
{
}

BOOL CdrawingalineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CdrawingalineView drawing

void CdrawingalineView::OnDraw(CDC* pDC)
{
	CClientDC dc(this);
	//bar.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,CRect(418,0,461,800),this,24);

	
	//image.Draw(  //change mouse cursor when on bitmap

	//rgn.CreateRoundRectRgn(0,0,44,44,55,55);

	//ci.Draw(hdc,0,0);
	kaboom(pDC, NULL);
	//pDC->Polygon(&CPoint(100,100),9);
	
/*
	/////////////
	#define xx0 30
	#define yy0 100

        dc.TextOut(30,105,"SINUS LINE");
        CString strx;
        strx.Format("Step = %d",iTime);
        dc.TextOut(30,120,strx);

        dc.MoveTo(xx0,yy0);
        dc.LineTo(xx0+800,yy0);
		
        int xx=0;
        int yy;
        while(xx <= iTime)
        {
    yy = arrSinus[xx];
        if(xx==0) dc.MoveTo(xx0+xx,yy0-yy);
        else dc.LineTo(xx0+xx,yy0-yy);
        xx++;
        }*/
	
	CdrawingalineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	
	// TODO: add draw code for native data here
}


// CdrawingalineView diagnostics

#ifdef _DEBUG
void CdrawingalineView::AssertValid() const
{
	CView::AssertValid();
}

void CdrawingalineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdrawingalineDoc* CdrawingalineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdrawingalineDoc)));
	return (CdrawingalineDoc*)m_pDocument;
}
#endif //_DEBUG


// CdrawingalineView message handlers


void CdrawingalineView::OnInitialUpdate()
{
	
	//bar.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,CRect(418,0,461,800),this,24);


	/*ci.Load((CString)"D:\\sizes.jpg");
	CDC *dc1 = AfxGetMainWnd()->GetDC();
	HDC hdc = *dc1;
	ci.Draw(hdc,100,100);*/
	
	//bar.EnableScrollBar(ESB_DISABLE_BOTH);
	//bar.SetScrollRange(0, 400);
}



//void CdrawingalineView::OnMouseMove(UINT nFlags, CPoint point)
//{
//
//	if((nFlags & MK_LBUTTON) == MK_LBUTTON)
//		{
//
//
//			CClientDC dc(this);
//			POINT temp = {0};
//			POINT temp_data = {0};
//			for ( int i = 0 ; i <8; i++)
//			{
//				for(int j = 0 ; j<8; j++)
//				{
//
//					if(PtInRect(&data[i][j].point, CurrentMousePos) && data[i][j].piece != NONE)
//					 {				
//						 temp.x = point.x - CurrentMousePos.x;
//						 temp.y = point.y - CurrentMousePos.y;
//						 temp_data.x = data[i][j].point.left;
//						 temp_data.y = data[i][j].point.top;
//						 movepiece(GetDC(), temp, temp_data, ROOK);
//						 switch(data[i][j].piece)
//						 {
//						 
//						 case ROOK:
//							 movepiece(GetDC(), temp, temp_data, ROOK);
//							 //this->InvalidateRect(CRect(data[i][j].point));
//							 break;
//
//						 case PAWN:
//							 break;
//
//						 case KING:
//							 movepiece(GetDC(), temp, temp_data, KING);
//							 break;
//
//						 case QUEEN:
//							 movepiece(GetDC(), temp, temp_data, QUEEN);
//							 break;
//
//						 case BISHOP:
//							 movepiece(GetDC(), temp, temp_data, BISHOP);
//							 break;
//
//						 case KNIGHT:
//							 movepiece(GetDC(), temp, temp_data, KNIGHT);
//							 break;
//						 case KNIGHT2:
//							 movepiece(GetDC(), temp, temp_data, KNIGHT);
//							 break;
//						 case BISHOP2:
//							 movepiece(GetDC(), temp, temp_data, BISHOP);
//							 break;
//						 case ROOK2:
//							 movepiece(GetDC(), temp, temp_data, ROOK);
//							 break;
//
//
//
//
//						 }
//						 
//					}
//				}
//			}
//	}
//	// TODO: Add your message handler code here and/or call default
//
//	CView::OnMouseMove(nFlags, point);
//}






void CdrawingalineView::movepiece(CDC* dc, POINT pnt, POINT pnt_data,  pieces pc)
{

		POINT temp2;
		POINT lpp = {0};
		
		origin.x = (pnt.x+pnt_data.x);
		origin.y = (pnt.y+pnt_data.y);
		origin2.x = origin.x + 80;
		origin2.y = origin.y + 80;
		char temp[MAX_PATH];
		sprintf(temp, "C:\\Users\\captain\\Desktop\\chess pieces\\Black\\%d.bmp", (int)pc);

		CString szFilename (temp);

		HBITMAP hBmp = (HBITMAP)::LoadImageA(NULL, szFilename, IMAGE_BITMAP,  0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		CBitmap bmp;
		bmp.Attach(hBmp);

		CDC bmDC;
		bmDC.CreateCompatibleDC(dc);
		CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

		BITMAP  bi;
		bmp.GetBitmap(&bi);

		dc->BitBlt((pnt.x+pnt_data.x), (pnt.y+pnt_data.y),bi.bmWidth,bi.bmHeight,&bmDC,0,0,SRCCOPY);

 		bmDC.SelectObject(pOldbmp);




}




