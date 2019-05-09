
// MFCOpenGL01Doc.cpp : CMFCOpenGL01Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCOpenGL01.h"
#endif

#include "MFCOpenGL01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCOpenGL01Doc

IMPLEMENT_DYNCREATE(CMFCOpenGL01Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCOpenGL01Doc, CDocument)
END_MESSAGE_MAP()


// CMFCOpenGL01Doc ����/����

CMFCOpenGL01Doc::CMFCOpenGL01Doc()
{
	// TODO: �ڴ����һ���Թ������
    m_operation = 0;
    m_color = RGB(0, 0, 0);
    m_size = 1;
}

CMFCOpenGL01Doc::~CMFCOpenGL01Doc()
{
}

BOOL CMFCOpenGL01Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMFCOpenGL01Doc ���л�

void CMFCOpenGL01Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMFCOpenGL01Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);

}

// ������������֧��
void CMFCOpenGL01Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);

    
}

void CMFCOpenGL01Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCOpenGL01Doc ���

#ifdef _DEBUG
void CMFCOpenGL01Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCOpenGL01Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCOpenGL01Doc ����






///ˢ�����л��Ƶ�ͼ��
void CMFCOpenGL01Doc::flush_all_drawing(CDC * pDC){
    
    for (int i = 0; i < v_point.size(); i++) {
        if (v_point[i].type == 0) point_circle(pDC, v_point[i].color, v_point[i].p.x, v_point[i].p.y, v_point[i].size);
        else if(v_point[i].type == 1) point_cross(pDC, v_point[i].color, v_point[i].p.x, v_point[i].p.y, v_point[i].size);
        else if(v_point[i].type == 2) point_rhombus(pDC, v_point[i].color, v_point[i].p.x, v_point[i].p.y, v_point[i].size);
    }

    for (int i = 0; i < v_line.size(); i++) {
        if (v_line[i].type == 0) line_dda_cpen(pDC, v_line[i].color, v_line[i].p1.x, v_line[i].p1.y, v_line[i].p2.x, v_line[i].p2.y, v_line[i].size);
        else if (v_line[i].type == 1) line_midpoint_cpen(pDC, v_line[i].color, v_line[i].p1.x, v_line[i].p1.y, v_line[i].p2.x, v_line[i].p2.y, v_line[i].size);
        else if (v_line[i].type == 2) line_bresenham_cpen(pDC, v_line[i].color, v_line[i].p1.x, v_line[i].p1.y, v_line[i].p2.x, v_line[i].p2.y, v_line[i].size);
    }

    for (int i = 0; i < v_perf_circle.size(); i++) {
        if (v_perf_circle[i].type == 0) circle_perfect_bresenham_cpen(pDC, v_perf_circle[i].color, v_perf_circle[i].p0.x, v_perf_circle[i].p0.y, v_perf_circle[i].radius, v_perf_circle[i].size);
        else if(v_perf_circle[i].type == 1) circle_perfect_midpoint_cpen(pDC, v_perf_circle[i].color, v_perf_circle[i].p0.x, v_perf_circle[i].p0.y, v_perf_circle[i].radius, v_perf_circle[i].size);
        else if (v_perf_circle[i].type == 2) circle_perfect_bresenham_cpen(pDC, v_perf_circle[i].color, v_perf_circle[i].p0.x, v_perf_circle[i].p0.y, v_perf_circle[i].radius, v_perf_circle[i].size);
    }

    for (int i = 0; i < v_oval_circle.size(); i++) {
        if (v_oval_circle[i].type == 0) circle_oval_bresenham_cpen(pDC, v_oval_circle[i].color, v_oval_circle[i].p0.x, v_oval_circle[i].p0.y, v_oval_circle[i].a, v_oval_circle[i].b, v_oval_circle[i].size);
        else if (v_oval_circle[i].type == 1) circle_oval_midpoint_cpen(pDC, v_oval_circle[i].color, v_oval_circle[i].p0.x, v_oval_circle[i].p0.y, v_oval_circle[i].a, v_oval_circle[i].b, v_oval_circle[i].size);
        else if (v_oval_circle[i].type == 2) circle_oval_midpoint_cpen(pDC, v_oval_circle[i].color, v_oval_circle[i].p0.x, v_oval_circle[i].p0.y, v_oval_circle[i].a, v_oval_circle[i].b, v_oval_circle[i].size);
    }

    for (int i = 0; i < v_polygon.size(); i++) {
        draw_polygon_cpen(pDC, v_polygon[i]);
    }

    for (int i = 0; i < v_fill.size(); i++) {
        flood_fill_cbrush(pDC, v_fill[i].color, pDC->GetPixel(v_fill[i].p.x, v_fill[i].p.y), v_fill[i].p);
    }

}



void CMFCOpenGL01Doc::draw_polygon_cpen(CDC * pDC, d_polygon p){

    for (int i = 0; i < p.ps.size() - 1; i++)
        line_midpoint_cpen(pDC, p.color, p.ps[i].x, p.ps[i].y, p.ps[i + 1].x, p.ps[i + 1].y, p.size);

    line_midpoint_cpen(pDC, p.color, p.ps[p.ps.size()-1].x, p.ps[p.ps.size()-1].y, p.ps[0].x, p.ps[0].y, p.size);

}







///���� ��ʼ

//����Բ�εĵ�
void CMFCOpenGL01Doc::point_circle(CDC *pDC, COLORREF color, int x, int y, int size) {
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
void CMFCOpenGL01Doc::point_cross(CDC *pDC, COLORREF color, int x, int y, int size) {

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
void CMFCOpenGL01Doc::point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size) {

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










///�����㷨 ��ʼ

//DDA��ֵ΢�ַ������ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
void CMFCOpenGL01Doc::line_dda(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

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
    for (int i = 1; i <= steps; i++) {
        x += delta_x;
        y += delta_y;
        pDC->SetPixel(x, y, color);
    }

    return;
}

//�е㷨���ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
void CMFCOpenGL01Doc::line_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

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
void CMFCOpenGL01Doc::line_midpoint_vertical_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

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
                pDC->SetPixel(x, y + i, color);
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
                pDC->SetPixel(x, y + i, color);
        }
    }
    return;
}

//�е㷨���ߣ�б�ʾ���ֵ(1,+oo)��ָ���߿�ˮƽ��ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
void CMFCOpenGL01Doc::line_midpoint_horizontal_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

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
                pDC->SetPixel(x + i, y, color);
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
                pDC->SetPixel(x + i, y, color);
        }
    }
    return;
}

//�е㷨���ߣ�б�����⣬ָ���߿�������ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
void CMFCOpenGL01Doc::line_midpoint_square_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

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
void CMFCOpenGL01Doc::line_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

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

void CMFCOpenGL01Doc::line_dda_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
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

void CMFCOpenGL01Doc::line_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
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

void CMFCOpenGL01Doc::line_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
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








///��Բ�㷨 ��ʼ

//bresenham������Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬�뾶
void CMFCOpenGL01Doc::circle_perfect_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

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
void CMFCOpenGL01Doc::circle_perfect_bresenham_gl(int colord1, int colord2, int colord3, int x0, int y0, int radius) {

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
void CMFCOpenGL01Doc::circle_perfect_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

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
void CMFCOpenGL01Doc::set_points_on_circle(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

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
void CMFCOpenGL01Doc::circle_oval_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    int sqa = a * a, sqb = b * b;
    int x = 0, y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    int P_x = round((double)sqa / sqrt((double)(sqa + sqb)));
    while (x <= P_x) {
        if (d < 0)
            d += 2 * sqb * (2 * x + 3);
        else {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0) {
        set_points_on_oval(pDC, color, x0, y0, x, y);
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

//�е㷨����Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬����ĳ��ȣ�����ĳ���
void CMFCOpenGL01Doc::circle_oval_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    double sqa = a * a;
    double sqb = b * b;
    double d = sqb + sqa * (-b + 0.25);
    int x = 0;
    int y = b;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    while (sqb * (x + 1) < sqa * (y - 0.5)) {
        if (d < 0) d += sqb * (2 * x + 3);
        else {
            d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0) {
        if (d < 0) {
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
void CMFCOpenGL01Doc::set_points_on_oval(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

    pDC->SetPixel((x0 + x), (y0 + y), color);
    pDC->SetPixel((x0 - x), (y0 + y), color);
    pDC->SetPixel((x0 + x), (y0 - y), color);
    pDC->SetPixel((x0 - x), (y0 - y), color);

    return;
}



//CPen����

void CMFCOpenGL01Doc::circle_perfect_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
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

void CMFCOpenGL01Doc::circle_perfect_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
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

void CMFCOpenGL01Doc::set_points_on_circle_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {
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


void CMFCOpenGL01Doc::circle_oval_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

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

void CMFCOpenGL01Doc::circle_oval_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

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

void CMFCOpenGL01Doc::set_points_on_oval_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {

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








///��������㷨 ��ʼ

void CMFCOpenGL01Doc::flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt) {

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->ExtFloodFill(pt.x, pt.y, color_banned, FLOODFILLSURFACE);

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}






///��άͼ�βü��㷨 ��ʼ


//Cohen-Sutherland+�е�ָ�������+�е�ָ���߶βü�    ������pDC����ɫ���ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬�����ߣ����ü���ֱ��
void CMFCOpenGL01Doc::line_cut_Sutherland_midpoint(CDC *pDC, COLORREF color, vertex window_vertex_left_top, vertex window_vertex_right_bottom, int num, line lines[]) {

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
        if ((vb.code & ve.code) == 0) {
            if ((vb.code == 0) || (ve.code == 0)) { //��һ�����⣬��һ������
                vertex_coded vd = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, lines[i]);
                if (vb.code == 0)
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
CMFCOpenGL01Doc::vertex_coded CMFCOpenGL01Doc::line_cut_midpoint(vertex window_vertex_left_top, vertex window_vertex_right_bottom, line single_line) {

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
void CMFCOpenGL01Doc::set_vertex_code(vertex window_vertex_left_top, vertex window_vertex_right_bottom, vertex_coded *v) {

    if (v->y >= window_vertex_left_top.y) v->code |= 8;    //1000 ��
    if (v->y <= window_vertex_right_bottom.y) v->code |= 4; //0100 ��
    if (v->x >= window_vertex_right_bottom.x) v->code |= 2;  //0010 ��
    if (v->x <= window_vertex_left_top.x) v->code |= 1;   //0001 ��

    return;
}

//�жϲü���Խ��ߺʹ��ü��߶ε�λ�ù�ϵ    �������ü��߿�ĶԽ��ߵ���㣬�ü��߿�Խ��ߵ��յ㣬���ü��߶ε���㣬���ü��߶ε��յ�
bool CMFCOpenGL01Doc::judge_line_pos(vertex window_vertex_a, vertex window_vertex_b, vertex_coded va, vertex_coded vb) {
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
CMFCOpenGL01Doc::vertex_coded CMFCOpenGL01Doc::get_mid_point(vertex diagonal_vertex_a, vertex diagonal_vertex_b, vertex_coded va, vertex_coded vb) {
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
CMFCOpenGL01Doc::polygon CMFCOpenGL01Doc::polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon) {

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
int CMFCOpenGL01Doc::get_intersection_point(vertex vb, vertex ve, int value, bool flag) {

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
void CMFCOpenGL01Doc::draw_polygon(CDC *pDC, COLORREF color, polygon p) {
    for (int i = 0; i < p.vertex_num - 1; i++)
        line_midpoint(pDC, color, p.vertexes[i].x, p.vertexes[i].y, p.vertexes[i + 1].x, p.vertexes[i + 1].y);

    line_midpoint(pDC, color, p.vertexes[p.vertex_num - 1].x, p.vertexes[p.vertex_num - 1].y, p.vertexes[0].x, p.vertexes[0].y);

    return;
}









///��άͼ�α任�㷨 ��ʼ

//ƽ��
void CMFCOpenGL01Doc::transform_translate(){
}

//�������ת�任    ������PDC����ɫ��ԭʼ����Σ���ת���ĵ㣬��ת�Ƕȣ��Ƕ��ƣ���������
void CMFCOpenGL01Doc::transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle) {

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


//��ת
void CMFCOpenGL01Doc::transform_rotate(){



}

//����
void CMFCOpenGL01Doc::transform_scale(){


}


//�Գ�
void CMFCOpenGL01Doc::transform_symmetry(){


}
//����
void CMFCOpenGL01Doc::transform_shear(){


}


//����
void CMFCOpenGL01Doc::transform_affline(){


}

//����
void CMFCOpenGL01Doc::transform_compound(){


}








