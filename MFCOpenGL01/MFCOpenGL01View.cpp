
// MFCOpenGL01View.cpp : CMFCOpenGL01View ���ʵ��
//


#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCOpenGL01.h"

#include "DialogPoint.h"
#include "DialogLine.h"
#include "DialogCirclePerfect.h"
#include "DialogCircleOval.h"
#include "DialogPolygon.h"
#include "DialogFill.h"

#endif

//#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCOpenGL01View

IMPLEMENT_DYNCREATE(CMFCOpenGL01View, CView)

BEGIN_MESSAGE_MAP(CMFCOpenGL01View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCOpenGL01View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_PAINT()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_DRAW_RULER, &CMFCOpenGL01View::OnDrawRuler)
    ON_COMMAND(ID_DRAW_ORTHO, &CMFCOpenGL01View::OnDrawOrtho)
    ON_COMMAND(ID_32784, &CMFCOpenGL01View::OnDrawLine)
    ON_COMMAND(ID_32783, &CMFCOpenGL01View::OnDrawPoint)
    ON_COMMAND(ID_32785, &CMFCOpenGL01View::OnDrawCirclePerfect)
    ON_COMMAND(ID_32786, &CMFCOpenGL01View::OnDrawCircleOval)
    ON_COMMAND(ID_32788, &CMFCOpenGL01View::OnDrawPolygon)
    ON_COMMAND(ID_32789, &CMFCOpenGL01View::OnDrawFill)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_COMMAND(ID_32792, &CMFCOpenGL01View::OnDrawSelect)
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_32793, &CMFCOpenGL01View::OnDrawErase)
    ON_COMMAND(ID_32794, &CMFCOpenGL01View::OnDrawClear)
    ON_COMMAND(ID_FILE_SAVE, &CMFCOpenGL01View::OnFileSave)
    ON_COMMAND(ID_FILE_OPEN, &CMFCOpenGL01View::OnFileOpen)
END_MESSAGE_MAP()

// CMFCOpenGL01View ����/����


CMFCOpenGL01View::CMFCOpenGL01View()
{
	// TODO: �ڴ˴���ӹ������
    //AfxInitRichEdit(); //��ʼ��RichEdit2.0!!!!!!!!
    
    m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
    m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;
}

CMFCOpenGL01View::~CMFCOpenGL01View()
{
}

BOOL CMFCOpenGL01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
    
	return CView::PreCreateWindow(cs);
}


// CMFCOpenGL01View ��ӡ


void CMFCOpenGL01View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCOpenGL01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCOpenGL01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCOpenGL01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMFCOpenGL01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCOpenGL01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCOpenGL01View ���

#ifdef _DEBUG
void CMFCOpenGL01View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenGL01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenGL01Doc)));
	return (CMFCOpenGL01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOpenGL01View ��Ϣ�������

/****************************************OpenGL��غ��Ĵ��� ��ʼ************************************/

//int CMFCOpenGL01View::OnCreate(LPCREATESTRUCT lpCreateStruct){
//    if (CView::OnCreate(lpCreateStruct) == -1)
//        return -1;
//
//    // TODO:  �ڴ������ר�õĴ�������
//
//    CClientDC dc(this);
//    PIXELFORMATDESCRIPTOR pfd;
//    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
//    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//    pfd.nVersion = 1;
//    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.cColorBits = 24;
//    pfd.cDepthBits = 32;
//    int pixelFormat = ChoosePixelFormat(dc.m_hDC, &pfd);
//    SetPixelFormat(dc.m_hDC, pixelFormat, &pfd);
//    m_hRC = wglCreateContext(dc.m_hDC);
//    return 0;
//}

//void CMFCOpenGL01View::OnSize(UINT nType, int cx, int cy){
//    CView::OnSize(nType, cx, cy);
//
//    // TODO: �ڴ˴������Ϣ����������
//    CClientDC dc(this);
//    wglMakeCurrent(dc.m_hDC, m_hRC);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    double deepth = 100;
//    double n = 1;
//
//    //glOrtho(-cx / n, -cx / n, -cy / n, -cy / n, -deepth, deepth);
//    glOrtho(0, 1920, 0, 1080, -100, 100); //��������ϵ
//
//    glMatrixMode(GL_MODELVIEW);
//    glViewport(0, 0, cx, cy);
//    //int viewport_arg = cx > cy ? cx : cy;
//    //glViewport(0, 0, viewport_arg, viewport_arg);
//    wglMakeCurrent(NULL, NULL);
//    //ReSizeGLScene(cx, cy);
//}

//void CMFCOpenGL01View::ReSizeGLScene(int width, int height) {
//    if (height == 0) height = 1;
//
//    glViewport(0, 0, width, height);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}

void CMFCOpenGL01View::OnDraw(CDC* pDC){
    CMFCOpenGL01Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

    //��ҵ
    COLORREF red = RGB(255, 0, 0), green = RGB(0, 255, 0), blue = RGB(0 ,0 ,255),  black = RGB(0, 0, 0);
    
    if (EntName.Compare(_T("bmp")) == 0){
        ShowBitmap(pDC, BmpName);               //��ʾͼƬ
        EntName = "";
    }
    /*
    FillPath
    FillRect ����� ��
    FillRgn
    PolyPolygon �����Σ�����ɫ�߿� ��
    FloodFill ����С�ķ������ ��Ĭ��ΪFLOODFILLBORDER����
    ExtFloodFill ��ģʽ��������FLOODFILLBORDER ָ���߽���ɫ��FLOODFILLSURFACE ָ����Ҫ���ǵ���ɫ����
    */
    
    //CPen cpen;
    //cpen.CreatePen(PS_SOLID, 10, red);
    //CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    //
    //pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);

    //pDC->SetROP2(R2_NOTXORPEN);
    //pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);

    ///*pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);*/

    //pDC->SelectObject(pOldPen);
    //cpen.DeleteObject();

    /*wglMakeCurrent(pDC->m_hDC, m_hRC);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3d(255,0,0);

    ....

    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);*/
}


//BOOL CMFCOpenGL01View::OnEraseBkgnd(CDC* pDC){
//    //return CView::OnEraseBkgnd(pDC);
//    return TRUE;
//}

//void CMFCOpenGL01View::OnDestroy(){
//    CView::OnDestroy();
//
//    // TODO: �ڴ˴������Ϣ����������
//    wglMakeCurrent(NULL, NULL);
//    wglDeleteContext(m_hRC);
//    m_hRC = NULL;
//}


/****************************************OpenGL��غ��Ĵ��� ����************************************/





/**********************************************MFC���ںͰ�ť��� ��ʼ****************************************/

//�Ի����еı���

//�������ֲ�����1�㣬2�ߣ�3Բ��4��Բ��5�����
int view_flag_global = 0;

//����
int point_size_global, point_type_global;
COLORREF point_color_global;

//����
int line_size_global, line_type_global;
COLORREF line_color_global;

//����Բ
int circle_perfect_size_global, circle_perfect_type_global;
COLORREF circle_perfect_color_global;

//����Բ
int circle_oval_size_global, circle_oval_type_global;
COLORREF circle_oval_color_global;

//�������
CMFCOpenGL01View::polygon polygon_global;
COLORREF polygon_color_global;
int polygon_size_global;
BOOL is_drawing_polygon_gloabl = FALSE;

//���
COLORREF fill_color_global;




//�˵����Ĳ˵���

void CMFCOpenGL01View::OnDrawRuler()
{
    // TODO: �ڴ���������������

    //�򵥿̶ȣ�ÿ50����һ�̶ȣ�
    CDC *pDC = GetDC();
    for (int i = 0; i <= 1920; i += 50) line_dda(pDC, RGB(0, 0, 0), i, 0, i, 10);
    for (int i = 0; i <= 1920; i += 50) line_dda(pDC, RGB(0, 0, 0), 0, i, 10, i);
}

void CMFCOpenGL01View::OnDrawOrtho()
{
    // TODO: �ڴ���������������

    //ģ��ѿ�������ϵ������ԭ����(900,400)��ÿ��50����Ϊ��λ1��
    CDC *pDC = GetDC();
    int xx = 900, yy = 400;
    line_dda(pDC, RGB(0, 0, 0), xx, 0, xx, 1080); for (int j = 0; j <= 1080; j += 50) line_dda(pDC, RGB(0, 0, 0), xx, j, xx + 10, j);
    line_dda(pDC, RGB(0, 0, 0), 0, yy, 1960, yy); for (int j = 0; j <= 1920; j += 50) line_dda(pDC, RGB(0, 0, 0), j, yy - 10, j, yy);
}

void CMFCOpenGL01View::OnDrawPoint()
{
    //view_flag_global = 1;
    point_color_global = RGB(0, 0, 0);
    DialogPoint dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawLine()
{
    //view_flag_global = 2;
    line_color_global = RGB(0, 0, 0);
    DialogLine dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawCirclePerfect()
{
    //view_flag_global = 3;
    circle_perfect_color_global = RGB(0, 0, 0);
    DialogCirclePerfect dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawCircleOval()
{
    //view_flag_global = 4;
    circle_oval_color_global = RGB(0, 0, 0);
    DialogCircleOval dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawPolygon()
{
    //view_flag_global = 5;
    polygon_color_global = RGB(0, 0, 0);
    DialogPolygon dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawFill()
{
    //view_flag_global = 10;
    fill_color_global = RGB(0, 0, 0);
    DialogFill dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawSelect()
{
    view_flag_global = 20;
}

void CMFCOpenGL01View::OnDrawErase()
{
    view_flag_global = 30;
}

void CMFCOpenGL01View::OnDrawClear()
{
    /*CRect rc;
    GetClientRect(&rc);
    GetDC()->FillSolidRect(&rc, RGB(255, 255, 255));*/
    Invalidate(TRUE);
}



void CMFCOpenGL01View::OnFileSave()
{
    Invalidate(FALSE); 
    CClientDC dc(this);
    CRect rect;
    BOOL  showMsgTag;                  //�Ƿ�Ҫ������ͼ�񱣴�ɹ��Ի���" 
    GetClientRect(&rect);                  //��ȡ������С
    HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
    //��������λͼ
    HDC hdc = CreateCompatibleDC(dc);      //��������DC���Ա㽫ͼ�񱣴�Ϊ��ͬ�ĸ�ʽ
    HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
    //��λͼѡ��DC�������淵��ֵ 
    BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
    //����ĻDC��ͼ���Ƶ��ڴ�DC��
    CImage image;
    image.Attach(hbitmap);                //��λͼת��Ϊһ��ͼ��
    if (!saveTag)                          //���ͼ���ǵ�һ�α�д��,��򿪶Ի���
    {
        saveTag = TRUE;
        showMsgTag = TRUE;
        CString  strFilter = _T("λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�|*.jpg|GIFͼ���ļ�|*.gif|PNGͼ���ļ�|*.png|������ʽ(*.*)|*.*||");
        CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);
        if (dlg.DoModal() != IDOK)
            return;

        CString strFileName;          //����û�û��ָ���ļ���չ������Ϊ�����һ��
        CString strExtension;
        strFileName = dlg.m_ofn.lpstrFile;
        if (dlg.m_ofn.nFileExtension = 0)               //��չ����ĿΪ0
        {
            switch (dlg.m_ofn.nFilterIndex) {
            case 1:
                strExtension = "bmp"; break;
            case 2:
                strExtension = "jpg"; break;
            case 3:
                strExtension = "gif"; break;
            case 4:
                strExtension = "png"; break;
            default:
                break;
            }
            strFileName = strFileName + "." + strExtension;
        }
        saveFilePath = strFileName;     //saveFilePathΪ�����е�ȫ�ֱ���,����ΪCString
    }
    else {
        showMsgTag = FALSE;
    }
    //AfxMessageBox(saveFilePath);               //��ʾͼ�񱣴��ȫ·��(�����ļ���)
    HRESULT hResult = image.Save(saveFilePath);     //����ͼ��
    if (FAILED(hResult)) {
        MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
    }
    else {
        if (showMsgTag)
            MessageBox(_T("�ļ�����ɹ���"));
    }
    image.Detach();
    SelectObject(hdc, hOldMap);
}

void CMFCOpenGL01View::OnFileOpen()
{
    CString filter;
    filter = "λͼ�ļ�(*.bmp)|*.bmp|������ʽ(*.*)|*.*||";
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
    //����ȷ����ť dlg.DoModal() ������ʾ�Ի���
    if (dlg.DoModal() == IDOK)
    {
        BmpName = dlg.GetPathName();     //��ȡ�ļ�·����   ��D:\pic\abc.bmp
        EntName = dlg.GetFileExt();      //��ȡ�ļ���չ��
        EntName.MakeLower();             //���ļ���չ��ת��Ϊһ��Сд�ַ�
        Invalidate();                    //���øú����ͻ����OnDraw�ػ滭ͼ
    }

    
}

void CMFCOpenGL01View::ShowBitmap(CDC *pDC, CString BmpName)
{
    //����bitmapָ�� ���ú���LoadImageװ��λͼ
    HBITMAP m_hBitmap;
    m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

    if (m_bitmap.m_hObject)
    {
        m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ
    }
    m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����

                                     //�߽�
    CRect rect;
    GetClientRect(&rect);

    //ͼƬ��ʾ(x,y)��ʼ����
    int m_showX = 0;
    int m_showY = 0;
    int m_nWindowWidth = rect.right - rect.left;   //����ͻ������
    int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�

                                                   //���岢����һ���ڴ��豸����DC
    CDC dcBmp;
    if (!dcBmp.CreateCompatibleDC(pDC))   //���������Ե�DC
        return;

    BITMAP m_bmp;                          //��ʱbmpͼƬ����
    m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��

    CBitmap *pbmpOld = NULL;
    dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

                                           //ͼƬ��ʾ���ú���stretchBlt
    pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);

    dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ
    DeleteObject(&m_bitmap);               //ɾ���ڴ��е�λͼ
    dcBmp.DeleteDC();                      //ɾ��CreateCompatibleDC�õ���ͼƬDC
}


BOOL CMFCOpenGL01View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

    if (pWnd == this && m_RectTracker.SetCursor(this, nHitTest)) {
        return TRUE;
    }
    if (pWnd == this && view_flag_global != 0) {
        HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
        ::SetCursor(hCur);
        return TRUE;
    }
    return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint oldPoint, newPoint;
//����Ŀ����������ݣ�ѡ����ٴ��Ƶ���ĵط�ȥ��Ҫ���ȥ
CRect rect_parent, rect_old, rect_new;
CDC dc_backup;
int clk_inside = 0;

void CMFCOpenGL01View::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (view_flag_global == 2) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 4) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 5) {
        if (!is_drawing_polygon_gloabl) {
            oldPoint = point;
            newPoint = point;
            is_drawing_polygon_gloabl = TRUE;
        }
        else {
            newPoint = point;
        }
    }
    else if (view_flag_global == 20) {
        
        m_RectTracker.TrackRubberBand(this, point, TRUE);
        m_RectTracker.m_rect.NormalizeRect();
        m_RectTracker.Draw(GetDC());

        rect_parent = m_RectTracker.m_rect;
        rect_old = m_RectTracker.m_rect;

        view_flag_global = 21;
    }
    else if (view_flag_global == 21) {
        
        int judge = m_RectTracker.HitTest(point);
        if (judge < 0) { //���λ����ѡ���ⲿ������ѡ���
            m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
            m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

            if (clk_inside > 0) {
                rect_parent.top--; rect_parent.bottom++; rect_parent.left--; rect_parent.right++;
                GetDC()->FillSolidRect(rect_parent, RGB(255, 255, 255));
            }
            
            clk_inside = 0;
            view_flag_global = 0;
        }
        else { //��ѡ����ڵ�����ȫ�����Ƶ�Ŀ������
            clk_inside++;

            rect_old = m_RectTracker.m_rect;
            

            m_RectTracker.Track(this, point, TRUE);
            //Invalidate(TRUE);
            m_RectTracker.Draw(GetDC());

            BitBlt(GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, rect_old.Width(), rect_old.Height(), dc_backup.m_hDC, 0, 0, SRCCOPY);

            rect_new = m_RectTracker.m_rect;
            int x = m_RectTracker.m_rect.TopLeft().x, y = m_RectTracker.m_rect.TopLeft().y;
            int width = m_RectTracker.m_rect.Width(), height = m_RectTracker.m_rect.Height();

            //����Ŀ�긲�������ͼ��
            //BitBlt(dc_backup.m_hDC, 0, 0, width, height, GetDC()->m_hDC, x, y, SRCCOPY);

            
            //����ͼ��
            BitBlt(GetDC()->m_hDC, x, y, width, height, GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, SRCCOPY);

            rect_old.top--; rect_old.bottom++; rect_old.left--; rect_old.right++;
            GetDC()->FillSolidRect(rect_old, RGB(255, 255, 255));
        }
    }

    CView::OnLButtonDown(nFlags, point);
}

CDC *dc2;

void CMFCOpenGL01View::OnLButtonUp(UINT nFlags, CPoint point)
{
    dc2 = GetDC();
    dc2->SetROP2(R2_NOT);

    if (view_flag_global == 1) {
        if (point_type_global == 0)
            point_circle(GetDC(), point_color_global, point.x, point.y, point_size_global);

        if (point_type_global == 1)
            point_cross(GetDC(), point_color_global, point.x, point.y, point_size_global);

        if (point_type_global == 2)
            point_rhombus(GetDC(), point_color_global, point.x, point.y, point_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 2) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc2->MoveTo(oldPoint);
        dc2->LineTo(newPoint);

        if (line_type_global == 0) line_dda_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);
        else if (line_type_global == 1) line_midpoint_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);
        else if (line_type_global == 2) line_bresenham_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc2->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        if (circle_perfect_type_global == 0) circle_perfect_bresenham_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);
        else if (circle_perfect_type_global == 1) circle_perfect_midpoint_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);
        else if (circle_perfect_type_global == 2) circle_perfect_midpoint_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 4) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc2->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        int x0 = (oldPoint.x + newPoint.x) / 2, y0 = (oldPoint.y + newPoint.y) / 2;
        int a = std::abs(x0 - oldPoint.x), b = std::abs(y0 - oldPoint.y);
        if (circle_oval_type_global == 0) circle_oval_bresenham_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);
        else if (circle_oval_type_global == 1) circle_oval_midpoint_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);
        else if (circle_oval_type_global == 2) circle_oval_midpoint_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 5) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc2->MoveTo(oldPoint);
        dc2->LineTo(newPoint);

        polygon_global.vertexes.push_back(vertex(point.x, point.y));
        polygon_global.vertex_num++;

        oldPoint.x = polygon_global.vertexes[(polygon_global.vertex_num) - 1].x;
        oldPoint.y = polygon_global.vertexes[(polygon_global.vertex_num) - 1].y;

        if (polygon_global.vertex_num == 1) {
            point_circle(GetDC(), polygon_color_global, point.x, point.y, polygon_size_global);
        }
        else {
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[(polygon_global.vertex_num) - 2].x, polygon_global.vertexes[(polygon_global.vertex_num) - 2].y, polygon_size_global);
        }
    }
    else if (view_flag_global == 10) {
        flood_fill_cbrush(GetDC(), fill_color_global, GetDC()->GetPixel(point.x, point.y), point);

        view_flag_global = 0;
    }
    
    CView::OnLButtonUp(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    if (view_flag_global == 5) {
        polygon_global.vertexes.push_back(vertex(point.x, point.y));
        polygon_global.vertex_num++;
        if (polygon_global.vertex_num == 1) {
            point_circle(GetDC(), polygon_color_global, point.x, point.y, polygon_size_global);
        }
        else {
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[(polygon_global.vertex_num) - 2].x, polygon_global.vertexes[(polygon_global.vertex_num) - 2].y, polygon_size_global);
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[0].x, polygon_global.vertexes[0].y, polygon_size_global);
        }
        polygon_global.vertexes.clear();
        polygon_global.vertex_num = 0;
        view_flag_global = 0;
        is_drawing_polygon_gloabl = FALSE;
    }
    else if (view_flag_global == 20) {
        view_flag_global = 0;
    }
    CView::OnLButtonDblClk(nFlags, point);
}


CRect rect_eraser;
CDC *dc1;

void CMFCOpenGL01View::OnMouseMove(UINT nFlags, CPoint point)
{
    dc1 = GetDC();
    dc1->SetROP2(R2_NOT);

    if (nFlags == MK_LBUTTON && view_flag_global == 2) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        newPoint = point;
        radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 4) {
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        newPoint = point;
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));
    }
    if (view_flag_global == 5 && is_drawing_polygon_gloabl) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 30) {
        rect_eraser.SetRect(CPoint(point.x - 25, point.y - 25), CPoint(point.x + 25, point.y + 25));
        //GetDC()->FillSolidRect(&rect_eraser, RGB(255, 255, 255));
        InvalidateRect(rect_eraser);

    }

    CView::OnMouseMove(nFlags, point);
}



/**********************************************MFC���ںͰ�ť��� ����****************************************/




/**********************************************���� ��ʼ****************************************/

//����Բ�εĵ�
void CMFCOpenGL01View::point_circle(CDC *pDC, COLORREF color, int x, int y, int size) {
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    pDC->MoveTo(x, y);
    pDC->LineTo(x, y);
    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

//����ʮ�ֵĵ�
void CMFCOpenGL01View::point_cross(CDC *pDC, COLORREF color, int x, int y, int size) {

    if (size == 1) {
        line_midpoint(pDC, color, x - 4, y, x + 3, y);
        line_midpoint(pDC, color, x, y - 4, x, y + 3);
        return;
    }

    int t = size / 2 + 3 * size;
    CRect rec1(x - t, y - size / 2, x + t, y + size / 2);
    CRect rec2(x - size / 2, y - t, x + size / 2, y + t);

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->FillRect(rec1, &cbrush);
    pDC->FillRect(rec2, &cbrush);

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}

//�������εĵ�
void CMFCOpenGL01View::point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size) {

    int t = size + size / 5;
    line_midpoint(pDC, color, x - size, y, x, y - t);
    line_midpoint(pDC, color, x, y - t, x + size, y);
    line_midpoint(pDC, color, x + size, y, x, y + t);
    line_midpoint(pDC, color, x, y + t, x - size, y);

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->FloodFill(x, y, color); //����㿪ʼ����brush����ɫ��䡰��С�����ǿ��������൱������Ͱ
    //COLORREF color_banned = pDC->GetPixel(CPoint(x, y));
    //pDC->ExtFloodFill(x, y, color_banned, FLOODFILLSURFACE); //����㿪ʼ����brush����ɫ������䣬ֱ������ĳ����ɫΪֹ

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}




/**********************************************���� ��ʼ****************************************/






/**********************************************�����㷨 ��ʼ****************************************/

//DDA��ֵ΢�ַ������ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
void CMFCOpenGL01View::line_dda(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    double delta_x = 0.0, delta_y = 0.0, x = 0.0, y = 0.0;
    int dx = 0, dy = 0, steps = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx)>abs(dy)) steps = abs(dx);
    else steps = abs(dy);
    delta_x = (double)dx / (double)steps;
    delta_y = (double)dy / (double)steps;
    x = x0, y = y0;
    pDC->SetPixel(x, y, color);
    for (int i = 1; i <= steps; i++){
        x += delta_x;
        y += delta_y;
        pDC->SetPixel(x, y, color);
    }

    return;
}

//�е㷨���ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
void CMFCOpenGL01View::line_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // б�ʾ���ֵ <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            pDC->SetPixel(x, y, color);
        }
    }
    else { // б�ʾ���ֵ > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            pDC->SetPixel(x, y, color);
        }
    }
    return;
}

//�е㷨���ߣ�б�ʾ���ֵ[0,1]��ָ���߿���ֱ��ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
void CMFCOpenGL01View::line_midpoint_vertical_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // б�ʾ���ֵ <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for(int i = -width/2; i <= width/2; i++)
                pDC->SetPixel(x, y+i, color);
        }
    }
    else { // б�ʾ���ֵ > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x, y+i, color);
        }
    }
    return;
}

//�е㷨���ߣ�б�ʾ���ֵ(1,+oo)��ָ���߿�ˮƽ��ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
void CMFCOpenGL01View::line_midpoint_horizontal_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // б�ʾ���ֵ <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x+i, y, color);
        }
    }
    else { // б�ʾ���ֵ > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x+i, y, color);
        }
    }
    return;
}

//�е㷨���ߣ�б�����⣬ָ���߿�������ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
void CMFCOpenGL01View::line_midpoint_square_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // б�ʾ���ֵ <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for (int i = -width / 2; i <= width / 2; i++) {
                for (int j = -width / 2; j <= width / 2; j++) {
                    pDC->SetPixel(x + i, y + j, color);
                }
            }
        }
    }
    else { // б�ʾ���ֵ > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++) {
                for (int j = -width / 2; j <= width / 2; j++) {
                    pDC->SetPixel(x + i, y + j, color);
                }
            }
        }
    }
    return;
}

//bresenham�����ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
void CMFCOpenGL01View::line_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = x0, y = y0, eps;

    eps = 0; dx = abs(dx); dy = abs(dy);
    if (dx > dy) {
        for (x = x0; x != x1; x += ux) {
            pDC->SetPixel(x, y, color);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy; eps -= dx;
            }
        }
    }
    else {
        for (y = y0; y != y1; y += uy) {
            pDC->SetPixel(x, y, color);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux; eps -= dy;
            }
        }
    }

    return;
}


//Cpen����

void CMFCOpenGL01View::line_dda_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    
    double delta_x = 0.0, delta_y = 0.0, x = 0.0, y = 0.0;
    int dx = 0, dy = 0, steps = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx)>abs(dy)) steps = abs(dx);
    else steps = abs(dy);
    delta_x = (double)dx / (double)steps;
    delta_y = (double)dy / (double)steps;
    x = x0, y = y0;
    pDC->MoveTo(x, y);
    pDC->LineTo(x, y);
    for (int i = 1; i <= steps; i++) {
        x += delta_x;
        y += delta_y;
        pDC->MoveTo(x, y);
        pDC->LineTo(x, y);
    }

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

void CMFCOpenGL01View::line_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // б�ʾ���ֵ <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
        }
    }
    else { // б�ʾ���ֵ > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
        }
    }
    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

void CMFCOpenGL01View::line_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = x0, y = y0, eps;

    eps = 0; dx = abs(dx); dy = abs(dy);
    if (dx > dy) {
        for (x = x0; x != x1; x += ux) {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy; eps -= dx;
            }
        }
    }
    else {
        for (y = y0; y != y1; y += uy) {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux; eps -= dy;
            }
        }
    }

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


/**********************************************�����㷨 ����****************************************/



/**********************************************��Բ�㷨 ��ʼ****************************************/

//bresenham������Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬�뾶
void CMFCOpenGL01View::circle_perfect_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x <= y; x++) {
        set_points_on_circle(pDC, color, x0, y0, x, y);
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }

    return;
}

//bresenham������Բ-gl�棻    ������������ɫR��������ɫG��������ɫB��Բ��x���꣬Բ��y���꣬�뾶
void CMFCOpenGL01View::circle_perfect_bresenham_gl(int colord1, int colord2, int colord3, int x0, int y0, int radius) {

    glBegin(GL_POINTS);
    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x < y; x++) {
        glVertex2d((x0 + x), (y0 + y));
        glVertex2d((x0 - x), (y0 + y));
        glVertex2d((x0 + x), (y0 - y));
        glVertex2d((x0 - x), (y0 - y));

        glVertex2d((x0 + y), (y0 + x));
        glVertex2d((x0 - y), (y0 + x));
        glVertex2d((x0 + y), (y0 - x));
        glVertex2d((x0 - y), (y0 - x));
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }
    glEnd();
    return;
}

//�е㷨����Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬�뾶
void CMFCOpenGL01View::circle_perfect_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

    int x = 0, y = 0, h = 0;
    x = 0, y = radius;
    h = 1 - radius;
    set_points_on_circle(pDC, color, x0, y0, x, y);
    while (x < y) {
        if (h < 0) h += 2 * x + 2;
        else {
            h += 2 * (x - y) + 5;
            y--;
        }
        x++;
        set_points_on_circle(pDC, color, x0, y0, x, y);
    }

    return;
}

//�ԳƵػ�Բ�ϵĵ㣻    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬Ŀ����x���꣬Ŀ����y����
void CMFCOpenGL01View::set_points_on_circle(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

    pDC->SetPixel((x0 + x), (y0 + y), color);
    pDC->SetPixel((x0 - x), (y0 + y), color);
    pDC->SetPixel((x0 + x), (y0 - y), color);
    pDC->SetPixel((x0 - x), (y0 - y), color);

    pDC->SetPixel((x0 + y), (y0 + x), color);
    pDC->SetPixel((x0 - y), (y0 + x), color);
    pDC->SetPixel((x0 + y), (y0 - x), color);
    pDC->SetPixel((x0 - y), (y0 - x), color);

    return;
}


//bresenham������Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬����ĳ��ȣ�����ĳ���
void CMFCOpenGL01View::circle_oval_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    int sqa = a * a, sqb = b * b;
    int x = 0, y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    int P_x = round((double)sqa / sqrt((double)(sqa + sqb)));
    while (x <= P_x){
        if (d < 0)
            d += 2 * sqb * (2 * x + 3);
        else{
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0){
        set_points_on_oval(pDC, color, x0, y0, x, y);
        y--;
        if (d < 0){
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
            d = d - 2 * sqa * y - sqa;
    }

    return;
}

//�е㷨����Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬����ĳ��ȣ�����ĳ���
void CMFCOpenGL01View::circle_oval_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    double sqa = a * a;
    double sqb = b * b;
    double d = sqb + sqa * (-b + 0.25);
    int x = 0;
    int y = b;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    while (sqb * (x + 1) < sqa * (y - 0.5)){
        if (d < 0) d += sqb * (2 * x + 3);
        else{
            d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0){
        if (d < 0){
            d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
            x++;
        }
        else d += sqa * (-2 * y + 3);
        y--;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }

    return;
}

//�ԳƵػ���Բ�ϵĵ㣻    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬Ŀ����x���꣬Ŀ����y����
void CMFCOpenGL01View::set_points_on_oval(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

    pDC->SetPixel((x0 + x), (y0 + y), color);
    pDC->SetPixel((x0 - x), (y0 + y), color);
    pDC->SetPixel((x0 + x), (y0 - y), color);
    pDC->SetPixel((x0 - x), (y0 - y), color);

    return;
}



//CPen����

void CMFCOpenGL01View::circle_perfect_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x <= y; x++) {
        set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }
    return;
}

void CMFCOpenGL01View::circle_perfect_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
    int x = 0, y = 0, h = 0;
    x = 0, y = radius;
    h = 1 - radius;
    set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
    while (x < y) {
        if (h < 0) h += 2 * x + 2;
        else {
            h += 2 * (x - y) + 5;
            y--;
        }
        x++;
        set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
    }
    return;
}

void CMFCOpenGL01View::set_points_on_circle_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    pDC->MoveTo((x0 + x), (y0 + y));
    pDC->LineTo((x0 + x), (y0 + y));
    pDC->MoveTo((x0 - x), (y0 + y));
    pDC->LineTo((x0 - x), (y0 + y));
    pDC->MoveTo((x0 + x), (y0 - y));
    pDC->LineTo((x0 + x), (y0 - y));
    pDC->MoveTo((x0 - x), (y0 - y));
    pDC->LineTo((x0 - x), (y0 - y));

    pDC->MoveTo((x0 + y), (y0 + x));
    pDC->LineTo((x0 + y), (y0 + x));
    pDC->MoveTo((x0 - y), (y0 + x));
    pDC->LineTo((x0 - y), (y0 + x));
    pDC->MoveTo((x0 + y), (y0 - x));
    pDC->LineTo((x0 + y), (y0 - x));
    pDC->MoveTo((x0 - y), (y0 - x));
    pDC->LineTo((x0 - y), (y0 - x));

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


void CMFCOpenGL01View::circle_oval_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

    size++;
    int sqa = a * a, sqb = b * b;
    int x = 0, y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    int P_x = round((double)sqa / sqrt((double)(sqa + sqb)));
    while (x <= P_x) {
        if (d < 0)
            d += 2 * sqb * (2 * x + 3);
        else {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0) {
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
        y--;
        if (d < 0) {
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
            d = d - 2 * sqa * y - sqa;
    }

    return;
}

void CMFCOpenGL01View::circle_oval_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

    size++;

    double sqa = a * a;
    double sqb = b * b;
    double d = sqb + sqa * (-b + 0.25);
    int x = 0;
    int y = b;
    set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    while (sqb * (x + 1) < sqa * (y - 0.5)) {
        if (d < 0) d += sqb * (2 * x + 3);
        else {
            d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
            y--;
        }
        x++;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0) {
        if (d < 0) {
            d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
            x++;
        }
        else d += sqa * (-2 * y + 3);
        y--;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }

    return;
}

void CMFCOpenGL01View::set_points_on_oval_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {

    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    pDC->MoveTo((x0 + x), (y0 + y));
    pDC->LineTo((x0 + x), (y0 + y));
    pDC->MoveTo((x0 - x), (y0 + y));
    pDC->LineTo((x0 - x), (y0 + y));
    pDC->MoveTo((x0 + x), (y0 - y));
    pDC->LineTo((x0 + x), (y0 - y));
    pDC->MoveTo((x0 - x), (y0 - y));
    pDC->LineTo((x0 - x), (y0 - y));

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


/**********************************************��Բ�㷨 ����****************************************/



/**********************************************��������㷨 ��ʼ****************************************/

void CMFCOpenGL01View::set_PolygonVertex(int num, int array_vertex[][2]) {

    PolygonVertex = new vertex[num];
    for (int i = 0; i < num; i++) {
        PolygonVertex[i].x = array_vertex[i][0];
        PolygonVertex[i].y = array_vertex[i][1];
    }

    return;
}

void CMFCOpenGL01View::init_EdgeTable(int num, vertex* PolygonVertex) {

    int y_max = -99999;
    for (int i = 0; i < num; i++) if (PolygonVertex[i].y > y_max) y_max = PolygonVertex[i].y;
    EdgeTable = new edge[y_max+1];

    //�Ѷ��㹹��ɱ�
    for (int i = 0; i < num-1; i++) {
        vertex vertex_left, vertex_right;
        if (PolygonVertex[i].x < PolygonVertex[i + 1].x) {
            vertex_left = PolygonVertex[i];
            vertex_right = PolygonVertex[i + 1];
        }
        else {
            vertex_left = PolygonVertex[i + 1];
            vertex_right = PolygonVertex[i];
        }
        
        if (vertex_left.y == vertex_right.y) continue; //����ˮƽ��
        edge* one_edge = new edge;
        one_edge->y_high = max(vertex_left.y, vertex_right.y);
        one_edge->delta_x = (double)(vertex_right.x - vertex_left.x) / (double)(vertex_right.y - vertex_left.y); //б�ʷ�֮һ��1/k
        //one_edge->x_intersection = 
    }
}


void CMFCOpenGL01View::insert_edge(edge* AELorET, int y, edge* one_edge) {

    edge* tail_edge = AELorET[y].next_edge;
    while (tail_edge != NULL) {
        tail_edge = tail_edge->next_edge;
    }
    tail_edge->next_edge = one_edge;
    one_edge->next_edge = NULL;

    return;
}

void CMFCOpenGL01View::del_edge(edge* AELorET, edge* one_edge) {



}


void CMFCOpenGL01View::flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt) {

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->ExtFloodFill(pt.x, pt.y, color_banned, FLOODFILLSURFACE);

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}



/**********************************************��������㷨 ����****************************************/




/**********************************************��άͼ�βü��㷨 ��ʼ****************************************/


//Cohen-Sutherland+�е�ָ�������+�е�ָ���߶βü�    ������pDC����ɫ���ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬�����ߣ����ü���ֱ��
void CMFCOpenGL01View::line_cut_Sutherland_midpoint(CDC *pDC, COLORREF color, vertex window_vertex_left_top, vertex window_vertex_right_bottom, int num, line lines[]){

    for (int i = 0; i < num; i++) {
        set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &lines[i].vertex_coded_begin);
        set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &lines[i].vertex_coded_end);
    }

    for (int i = 0; i < num; i++) {
        vertex_coded vb = lines[i].vertex_coded_begin;
        vertex_coded ve = lines[i].vertex_coded_end;
        if (vb.code == 0 && ve.code == 0) { //ȫ���ڲü���Χ�ڣ�ֱ������������
            line_midpoint(pDC, color, vb.x, vb.y, ve.x, ve.y);
            continue;
        }
        if ((vb.code & ve.code) != 0) { //ȫ�����ڲü���Χ�ڣ�ֱ��ɾ��
            //line_midpoint(pDC, RGB(0,255,0), vb.x, vb.y, ve.x, ve.y);
            continue;
        }
        if((vb.code & ve.code) == 0) {
            if ((vb.code == 0) || (ve.code == 0)) { //��һ�����⣬��һ������
                vertex_coded vd = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, lines[i]);
                if(vb.code == 0)
                    line_midpoint(pDC, color, vb.x, vb.y, vd.x, vd.y);
                else
                    line_midpoint(pDC, color, ve.x, ve.y, vd.x, vd.y);
            }
            else { //����ȫ�����棨�߶ιᴩ�ü��򣩣���Ҫ���߶ηָ�������ֱַ���
                vertex_coded vmid;
                //����->���µĶԽ�������ü��߶δ��ڽ��㣬�ô˽�����зָ��������
                if (judge_line_pos(window_vertex_left_top, window_vertex_right_bottom, lines[i].vertex_coded_begin, lines[i].vertex_coded_end)) {
                    vmid = get_mid_point(window_vertex_left_top, window_vertex_right_bottom, vb, ve);
                    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);
                }
                else { //����->���µĶԽ�������ü��߶δ��ڽ��㣬�ô˽�����зָ��������
                    vmid = get_mid_point(vertex(window_vertex_right_bottom.x, window_vertex_left_top.y), vertex(window_vertex_left_top.x, window_vertex_right_bottom.y), vb, ve);
                    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);
                }
                vertex_coded vd1 = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vb, vmid));
                vertex_coded vd2 = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vmid, ve));
                line_midpoint(pDC, color, vmid.x, vmid.y, vd1.x, vd1.y);
                line_midpoint(pDC, color, vmid.x, vmid.y, vd2.x, vd2.y);
            }
            
        }
    }

    return;
}

//�е�ָ�ݹ����ȷ���߶���ü��߿��ཻ����һ��    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬���ü���ֱ��
CMFCOpenGL01View::vertex_coded CMFCOpenGL01View::line_cut_midpoint(vertex window_vertex_left_top, vertex window_vertex_right_bottom, line single_line) {

    vertex_coded vin = single_line.vertex_coded_begin.code == 0 ? single_line.vertex_coded_begin : single_line.vertex_coded_end;
    vertex_coded vout = single_line.vertex_coded_begin.code != 0 ? single_line.vertex_coded_begin : single_line.vertex_coded_end;
    vertex_coded vmid = vertex_coded((vin.x + vout.x) / 2, (vin.y + vout.y) / 2);
    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);

    if (abs(vmid.x - vin.x) <= 1 || abs(vmid.y - vin.y) <= 1) return vmid;     //ȡ����

    if (vmid.code == 0) vin = vmid; //�е��ڲü����ڣ����ڲ��Ķ˵������е�
    else vout = vmid; //�е��ڲü����⣬���ⲿ�ĵ������е�
        
    return line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vin, vout));
}

//ȷ���߶εĶ˵������Ǹ����򣬻�ȡ���Ӧ�ı���    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬�˵�ָ��
void CMFCOpenGL01View::set_vertex_code(vertex window_vertex_left_top, vertex window_vertex_right_bottom, vertex_coded *v) {

    if (v->y >= window_vertex_left_top.y) v->code |= 8;    //1000 ��
    if (v->y <= window_vertex_right_bottom.y) v->code |= 4; //0100 ��
    if (v->x >= window_vertex_right_bottom.x) v->code |= 2;  //0010 ��
    if (v->x <= window_vertex_left_top.x) v->code |= 1;   //0001 ��

    return;
}

//�жϲü���Խ��ߺʹ��ü��߶ε�λ�ù�ϵ    �������ü��߿�ĶԽ��ߵ���㣬�ü��߿�Խ��ߵ��յ㣬���ü��߶ε���㣬���ü��߶ε��յ�
bool CMFCOpenGL01View::judge_line_pos(vertex window_vertex_a, vertex window_vertex_b, vertex_coded va, vertex_coded vb) {
    long long int d1, d2, d3, d4;
    d1 = (window_vertex_b.x - window_vertex_a.x)*(va.y - window_vertex_a.y) - (window_vertex_b.y - window_vertex_a.y)*(va.x - window_vertex_a.x);
    d2 = (window_vertex_b.x - window_vertex_a.x)*(vb.y - window_vertex_a.y) - (window_vertex_b.y - window_vertex_a.y)*(vb.x - window_vertex_a.x);
    d3 = (vb.x - va.x)*(window_vertex_a.y - va.y) - (vb.y - va.y)*(window_vertex_a.x - va.x);
    d4 = (vb.x - va.x)*(window_vertex_b.y - va.y) - (vb.y - va.y)*(window_vertex_b.x - va.x);
    if (d1*d2 <= 0 && d3*d4 <= 0)
        return true; //�ཻ���غ�
    else
        return false; //���ཻ
}

//�õ��߶���Խ��ߵĽ���    �������ü���Խ��ߵ���㣬�ü���Խ��ߵ��յ㣬���ü��ߵ���㣬���ü��ߵ��յ�
CMFCOpenGL01View::vertex_coded CMFCOpenGL01View::get_mid_point(vertex diagonal_vertex_a, vertex diagonal_vertex_b, vertex_coded va, vertex_coded vb) {
    int a = vb.x - va.x;
    int b = diagonal_vertex_a.x - diagonal_vertex_b.x;
    int c = vb.y - va.y;
    int d = diagonal_vertex_a.y - diagonal_vertex_b.y;
    int g = diagonal_vertex_a.x - va.x;
    int h = diagonal_vertex_a.y - va.y;
    int f = a*d - b*c;
    double t = double((d*g - b*h)) / double(f);
    vertex_coded m;
    m.x = va.x + t*(vb.x - va.x);
    m.y = va.y + t*(vb.y - va.y);
    return m;
}





//Sutherland-Hodgman����߲ü���������βü������زü���ɵ��¶���Σ�    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬���ü��Ķ����
CMFCOpenGL01View::polygon CMFCOpenGL01View::polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon) {

    polygon p1, p2, p3, p4;
    vertex vs, vp; //s->p
    //��߿�ü�
    for (int i = 0; i < src_polygon.vertex_num; i++) {
        vs = src_polygon.vertexes[i];
        if (i == src_polygon.vertex_num - 1) vp = src_polygon.vertexes[0];
        else vp = src_polygon.vertexes[i + 1];

        if (vs.x >= window_vertex_left_top.x && vp.x >= window_vertex_left_top.x) { //���һ��s��p�����ڲ࣬���p
            p1.vertexes.push_back(vp);
            p1.vertex_num++;
        }
        if (vs.x < window_vertex_left_top.x && vp.x < window_vertex_left_top.x) { //�������s��p������࣬�����
            continue;
        }
        if (vs.x >= window_vertex_left_top.x && vp.x < window_vertex_left_top.x) { //�������s���ڲ࣬p����࣬�������i
            vertex vi(window_vertex_left_top.x, get_intersection_point(vs, vp, window_vertex_left_top.x, true));
            p1.vertexes.push_back(vi);
            p1.vertex_num++;
        }
        if (vs.x < window_vertex_left_top.x && vp.x >= window_vertex_left_top.x) { //����ģ�s����࣬p���ڲ࣬���i��p
            vertex vi(window_vertex_left_top.x, get_intersection_point(vs, vp, window_vertex_left_top.x, true));
            p1.vertexes.push_back(vi);
            p1.vertexes.push_back(vp);
            p1.vertex_num += 2;
        }
    }

    //�ϱ߿�ü�
    for (int i = 0; i < p1.vertex_num; i++) {
        vs = p1.vertexes[i];
        if (i == p1.vertex_num - 1) vp = p1.vertexes[0];
        else vp = p1.vertexes[i + 1];

        if (vs.y <= window_vertex_left_top.y && vp.y <= window_vertex_left_top.y) { //���һ��s��p�����ڲ࣬���p
            p2.vertexes.push_back(vp);
            p2.vertex_num++;
        }
        if (vs.y > window_vertex_left_top.y && vp.y > window_vertex_left_top.y) { //�������s��p������࣬�����
            continue;
        }
        if (vs.y <= window_vertex_left_top.y && vp.y > window_vertex_left_top.y) { //�������s���ڲ࣬p����࣬�������i
            vertex vi(get_intersection_point(vs, vp, window_vertex_left_top.y, false), window_vertex_left_top.y);
            p2.vertexes.push_back(vi);
            p2.vertex_num++;
        }
        if (vs.y > window_vertex_left_top.y && vp.y <= window_vertex_left_top.y) { //����ģ�s����࣬p���ڲ࣬���i��p
            vertex vi(get_intersection_point(vs, vp, window_vertex_left_top.y, false), window_vertex_left_top.y);
            p2.vertexes.push_back(vi);
            p2.vertexes.push_back(vp);
            p2.vertex_num += 2;
        }
    }

    //�ұ߿�ü�
    for (int i = 0; i < p2.vertex_num; i++) {
        vs = p2.vertexes[i];
        if (i == p2.vertex_num - 1) vp = p2.vertexes[0];
        else vp = p2.vertexes[i + 1];

        if (vs.x <= window_vertex_right_bottom.x && vp.x <= window_vertex_right_bottom.x) { //���һ��s��p�����ڲ࣬���p
            p3.vertexes.push_back(vp);
            p3.vertex_num++;
        }
        if (vs.x > window_vertex_right_bottom.x && vp.x > window_vertex_right_bottom.x) { //�������s��p������࣬�����
            continue;
        }
        if (vs.x <= window_vertex_right_bottom.x && vp.x > window_vertex_right_bottom.x) { //�������s���ڲ࣬p����࣬�������i
            vertex vi(window_vertex_right_bottom.x, get_intersection_point(vs, vp, window_vertex_right_bottom.x, true));
            p3.vertexes.push_back(vi);
            p3.vertex_num++;
        }
        if (vs.x > window_vertex_right_bottom.x && vp.x <= window_vertex_right_bottom.x) { //����ģ�s����࣬p���ڲ࣬���i��p
            vertex vi(window_vertex_right_bottom.x, get_intersection_point(vs, vp, window_vertex_right_bottom.x, true));
            p3.vertexes.push_back(vi);
            p3.vertexes.push_back(vp);
            p3.vertex_num += 2;
        }
    }

    //�±߿�ü�
    for (int i = 0; i < p3.vertex_num; i++) {
        vs = p3.vertexes[i];
        if (i == p3.vertex_num - 1) vp = p3.vertexes[0];
        else vp = p3.vertexes[i + 1];

        if (vs.y >= window_vertex_right_bottom.y && vp.y >= window_vertex_right_bottom.y) { //���һ��s��p�����ڲ࣬���p
            p4.vertexes.push_back(vp);
            p4.vertex_num++;
        }
        if (vs.y < window_vertex_right_bottom.y && vp.y < window_vertex_right_bottom.y) { //�������s��p������࣬�����
            continue;
        }
        if (vs.y >= window_vertex_right_bottom.y && vp.y < window_vertex_right_bottom.y) { //�������s���ڲ࣬p����࣬�������i
            vertex vi(get_intersection_point(vs, vp, window_vertex_right_bottom.y, false), window_vertex_right_bottom.y);
            p4.vertexes.push_back(vi);
            p4.vertex_num++;
        }
        if (vs.y < window_vertex_right_bottom.y && vp.y >= window_vertex_right_bottom.y) { //����ģ�s����࣬p���ڲ࣬���i��p
            vertex vi(get_intersection_point(vs, vp, window_vertex_right_bottom.y, false), window_vertex_right_bottom.y);
            p4.vertexes.push_back(vi);
            p4.vertexes.push_back(vp);
            p4.vertex_num += 2;
        }
    }

    return p4;
}

//���ֱ�ߺͲü���Ľ��㣨���ؽ��㴦����ֵ��    ���������ü����ߵ���ʼ�㣬���ü����ߵĽ����㣬�ü��߿��ĳһ����x=value��y=value��valueֵ����x=����y=��trueΪx��falseΪy��
int CMFCOpenGL01View::get_intersection_point(vertex vb, vertex ve, int value, bool flag) {

    int result = 0;

    if (flag) { //��ֱ��x=value�ཻ������y
        if (vb.y == ve.y) { //k=0
            result = vb.y;
        }
        else {
            double k = 1.0*(ve.y - vb.y) / (ve.x - vb.x);
            double b = ve.y - (k * ve.x);
            result = k*value + b;
        }
    }
    else { //��ֱ��y=value�ཻ������x
        if (vb.x == ve.x) { //k������
            result = vb.x;
        }
        else {
            double k = 1.0*(ve.y - vb.y) / (ve.x - vb.x);
            double b = ve.y - (k * ve.x);
            result = (value - b) / k;
        }
    }

    return result;
}

//���ƶ����    ������PDC����ɫ����������������
void CMFCOpenGL01View::draw_polygon(CDC *pDC, COLORREF color, polygon p) {
    for (int i = 0; i < p.vertex_num-1; i++)
        line_midpoint(pDC, color, p.vertexes[i].x, p.vertexes[i].y, p.vertexes[i + 1].x, p.vertexes[i + 1].y);

    line_midpoint(pDC, color, p.vertexes[p.vertex_num-1].x, p.vertexes[p.vertex_num-1].y, p.vertexes[0].x, p.vertexes[0].y);

    return;
}


/**********************************************��άͼ�βü��㷨 ����****************************************/








/**********************************************��άͼ�α任�㷨 ��ʼ****************************************/

//�������ת�任    ������PDC����ɫ��ԭʼ����Σ���ת���ĵ㣬��ת�Ƕȣ��Ƕ��ƣ���������
void CMFCOpenGL01View::transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle) {

    double pi = 3.1415926;
    double arc = pi / 180.0*angle; //ת������

    polygon res_polygon = src_polygon;
    for (int i = 0; i < res_polygon.vertex_num; i++) {
        vertex t = res_polygon.vertexes[i];
        res_polygon.vertexes[i].x = center.x + (t.x - center.x)*std::cos(arc) - (t.y - center.y)*std::sin(arc);
        res_polygon.vertexes[i].y = center.y + (t.x - center.x)*std::sin(arc) + (t.y - center.y)*std::cos(arc);
    }

    draw_polygon(pDC, color, res_polygon);

    return;
}







/**********************************************��άͼ�α任�㷨 ����****************************************/


