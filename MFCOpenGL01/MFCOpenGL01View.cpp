
// MFCOpenGL01View.cpp : CMFCOpenGL01View ���ʵ��
//


#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCOpenGL01.h"

#endif

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
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILE_SAVE, &CMFCOpenGL01View::OnFileSave)
    ON_COMMAND(ID_FILE_OPEN, &CMFCOpenGL01View::OnFileOpen)
END_MESSAGE_MAP()

// CMFCOpenGL01View ����/����

CMFCOpenGL01View::CMFCOpenGL01View()
{   
    m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
    m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

}

CMFCOpenGL01View::~CMFCOpenGL01View()
{
    m_pDoc = NULL;
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

void CMFCOpenGL01View::OnDraw(CDC* pDC){
    
    CMFCOpenGL01Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc) return;

    if (!m_pDoc) m_pDoc = GetDocument();

    // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

    //��ҵ
    COLORREF red = RGB(255, 0, 0), green = RGB(0, 255, 0), blue = RGB(0 ,0 ,255),  black = RGB(0, 0, 0);
    
    m_pDoc->flush_all_drawing(pDC);
    


    if (EntName.Compare(_T("bmp")) == 0){
        ShowBitmap(pDC, BmpName);               //��ʾͼƬ
        EntName = "";
    }
    
}




///MFC���ںͰ�ť��� ��ʼ


//�˵����Ĳ˵���

void CMFCOpenGL01View::OnDrawRuler()
{
    // TODO: �ڴ���������������

    //�򵥿̶ȣ�ÿ50����һ�̶ȣ�
    CDC* dc1 = GetDC();
    for (int i = 0; i <= 1920; i += 50) m_pDoc->line_dda(dc1, RGB(0, 0, 0), i, 0, i, 10);
    for (int i = 0; i <= 1920; i += 50) m_pDoc->line_dda(dc1, RGB(0, 0, 0), 0, i, 10, i);
    ReleaseDC(dc1);
}

void CMFCOpenGL01View::OnDrawOrtho()
{
    // TODO: �ڴ���������������

    //ģ��ѿ�������ϵ������ԭ����(900,400)��ÿ��50����Ϊ��λ1��
    int xx = 900, yy = 400;
    CDC* dc1 = GetDC();
    m_pDoc->line_dda(dc1, RGB(0, 0, 0), xx, 0, xx, 1080); for (int j = 0; j <= 1080; j += 50)  m_pDoc->line_dda(dc1, RGB(0, 0, 0), xx, j, xx + 10, j);
    m_pDoc->line_dda(dc1, RGB(0, 0, 0), 0, yy, 1960, yy); for (int j = 0; j <= 1920; j += 50)  m_pDoc->line_dda(dc1, RGB(0, 0, 0), j, yy - 10, j, yy);
    ReleaseDC(dc1);
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
    if (pWnd == this && m_pDoc->m_operation != 0) {
        HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
        ::SetCursor(hCur);
        return TRUE;
    }
    return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint parentPoint, oldPoint, newPoint;
//����Ŀ����������ݣ�ѡ����ٴ��Ƶ���ĵط�ȥ��Ҫ���ȥ
CRect rect_parent, rect_old, rect_new;
int clk_inside = 0;

std::vector<CPoint> temp_ps;

void CMFCOpenGL01View::OnLButtonDown(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC();
    
    if (m_pDoc->m_operation == 0) {
        m_pDoc->select_all(dc1, point);
    }

    else if (m_pDoc->m_operation == 2) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 4) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 5) {
        if (!m_pDoc->is_drawing_polygon) {
            parentPoint = point;
            oldPoint = point;
            newPoint = point;
            m_pDoc->is_drawing_polygon = TRUE;
            temp_ps.clear();
            temp_ps.push_back(parentPoint);
        }
        else {
            newPoint = point;
            temp_ps.push_back(newPoint);
        }
    }
    else if (m_pDoc->m_operation == 20) {
        
        m_RectTracker.TrackRubberBand(this, point, TRUE);
        m_RectTracker.m_rect.NormalizeRect();
        m_RectTracker.Draw(GetDC());

        rect_parent = m_RectTracker.m_rect;
        rect_old = m_RectTracker.m_rect;

        m_pDoc->m_operation = 21;
    }
    else if (m_pDoc->m_operation == 21) {
        
        int judge = m_RectTracker.HitTest(point);
        if (judge < 0) { //���λ����ѡ���ⲿ������ѡ���
            m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
            m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

            if (clk_inside > 0) {
                rect_parent.top--; rect_parent.bottom++; rect_parent.left--; rect_parent.right++;
                dc1->FillSolidRect(rect_parent, RGB(255, 255, 255));
            }
            
            clk_inside = 0;
            m_pDoc->m_operation = 0;
        }
        else { //��ѡ����ڵ�����ȫ�����Ƶ�Ŀ������
            clk_inside++;

            rect_old = m_RectTracker.m_rect;
            

            m_RectTracker.Track(this, point, TRUE);
            //Invalidate(TRUE);
            m_RectTracker.Draw(dc1);

            //BitBlt(GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, rect_old.Width(), rect_old.Height(), dc_backup.m_hDC, 0, 0, SRCCOPY);

            rect_new = m_RectTracker.m_rect;
            int x = m_RectTracker.m_rect.TopLeft().x, y = m_RectTracker.m_rect.TopLeft().y;
            int width = m_RectTracker.m_rect.Width(), height = m_RectTracker.m_rect.Height();

            //����Ŀ�긲�������ͼ��
            //BitBlt(dc_backup.m_hDC, 0, 0, width, height, GetDC()->m_hDC, x, y, SRCCOPY);

            
            //����ͼ��
            BitBlt(GetDC()->m_hDC, x, y, width, height, dc1->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, SRCCOPY);

            rect_old.top--; rect_old.bottom++; rect_old.left--; rect_old.right++;
            dc1->FillSolidRect(rect_old, RGB(255, 255, 255));
        }
    }

    ReleaseDC(dc1);
    CView::OnLButtonDown(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonUp(UINT nFlags, CPoint point)
{
    CDC* dc1 = GetDC(), *dc2 = GetDC();
    dc1->SetROP2(R2_NOT);

    if (m_pDoc->m_operation == 1) {
        if (m_pDoc->point_type == 0) m_pDoc->point_circle(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->point_type == 1) m_pDoc->point_cross(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->point_type == 2) m_pDoc->point_rhombus(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);

        m_pDoc->v_point.push_back(CMFCOpenGL01Doc::d_point(point, m_pDoc->point_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 2) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        if (m_pDoc->line_type == 0) m_pDoc->line_dda_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->line_type == 1) m_pDoc->line_midpoint_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->line_type == 2) m_pDoc->line_bresenham_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, point.x, point.y, m_pDoc->m_size);

        m_pDoc->v_line.push_back(CMFCOpenGL01Doc::d_line(oldPoint, newPoint, m_pDoc->line_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        if (m_pDoc->circle_perfect_type == 0) m_pDoc->circle_perfect_bresenham_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, radius, m_pDoc->m_size);
        else if (m_pDoc->circle_perfect_type == 1) m_pDoc->circle_perfect_midpoint_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, radius, m_pDoc->m_size);
        else if (m_pDoc->circle_perfect_type == 2) m_pDoc->circle_perfect_midpoint_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, radius, m_pDoc->m_size);

        m_pDoc->v_perf_circle.push_back(CMFCOpenGL01Doc::d_perf_circle(oldPoint, radius, m_pDoc->circle_perfect_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 4) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        int x0 = (oldPoint.x + newPoint.x) / 2, y0 = (oldPoint.y + newPoint.y) / 2;
        int a = std::abs(x0 - oldPoint.x), b = std::abs(y0 - oldPoint.y);
        if (m_pDoc->circle_oval_type == 0) m_pDoc->circle_oval_bresenham_cpen(dc2, m_pDoc->m_color, x0, y0, a, b, m_pDoc->m_size);
        else if (m_pDoc->circle_oval_type == 1) m_pDoc->circle_oval_midpoint_cpen(dc2, m_pDoc->m_color, x0, y0, a, b, m_pDoc->m_size);
        else if (m_pDoc->circle_oval_type == 2) m_pDoc->circle_oval_midpoint_cpen(dc2, m_pDoc->m_color, x0, y0, a, b, m_pDoc->m_size);

        m_pDoc->v_oval_circle.push_back(CMFCOpenGL01Doc::d_oval_circle(CPoint(x0, y0), a, b, 0, m_pDoc->circle_oval_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 5) {
        //Ĩȥ���һ�ε���ͼ��ʾ��
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
        
        m_pDoc->point_circle(dc2, m_pDoc->m_color, newPoint.x, newPoint.y, m_pDoc->m_size);
        m_pDoc->line_midpoint_cpen(dc2, m_pDoc->m_color, oldPoint.x, oldPoint.y, newPoint.x, newPoint.y, m_pDoc->m_size);

        oldPoint = newPoint;
    }
    else if (m_pDoc->m_operation == 10) {
        m_pDoc->flood_fill_cbrush(dc2, m_pDoc->m_color, GetDC()->GetPixel(point.x, point.y), point);

        m_pDoc->v_fill.push_back(CMFCOpenGL01Doc::d_fill(point, m_pDoc->m_color));
    }
    
    //Invalidate();
    ReleaseDC(dc2);
    ReleaseDC(dc1);
    CView::OnLButtonUp(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC();
    if (m_pDoc->m_operation == 5) {
        m_pDoc->line_midpoint_cpen(dc1, m_pDoc->m_color, newPoint.x, newPoint.y, parentPoint.x, parentPoint.y, m_pDoc->m_size);
        m_pDoc->is_drawing_polygon = FALSE;

        m_pDoc->v_polygon.push_back(CMFCOpenGL01Doc::d_polygon(temp_ps, m_pDoc->m_size, m_pDoc->m_color));
    }

    ReleaseDC(dc1);
    CView::OnLButtonDblClk(nFlags, point);
}


void CMFCOpenGL01View::OnMouseMove(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC(), *dc2 = GetDC();
    dc1->SetROP2(R2_NOT);

    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 2) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        newPoint = point;
        radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 4) {
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        newPoint = point;
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));
    }
    if (m_pDoc->m_operation == 5 && m_pDoc->is_drawing_polygon) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 30) {
        CRect rect_eraser;
        rect_eraser.SetRect(CPoint(point.x - 25, point.y - 25), CPoint(point.x + 25, point.y + 25));
        dc2->FillSolidRect(&rect_eraser, RGB(255, 255, 255));
        //InvalidateRect(rect_eraser);
    }

    ReleaseDC(dc2);
    ReleaseDC(dc1);
    CView::OnMouseMove(nFlags, point);
}




