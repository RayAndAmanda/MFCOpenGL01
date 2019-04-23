
// MFCOpenGL01View.h : CMFCOpenGL01View ��Ľӿ�
//

#pragma once
#include "MFCOpenGL01Doc.h"

class CMFCOpenGL01View : public CView
{
protected: // �������л�����
	CMFCOpenGL01View();
    DECLARE_DYNCREATE(CMFCOpenGL01View)

// ����
public:
	CMFCOpenGL01Doc* GetDocument() const;

// ����
public:

// ��д
public:
    //virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCOpenGL01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


/***************************************************************************************************/
/****************************************OpenGL��غ��Ĵ��� ��ʼ************************************/
/***************************************************************************************************/

protected:
    HGLRC m_hRC;

    CRectTracker m_RectTracker; //ѡ���


    //����λͼ
    bool saveTag = false;
    CString saveFilePath = _T("D:\\");

    //��λͼ
    CString BmpName;                               //����ͼ���ļ��ļ���
    CString EntName;                               //����ͼ���ļ���չ��
    CBitmap m_bitmap;                              //����λͼ����

public:
    //afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); //����OpenGL����
    //afx_msg void OnSize(UINT nType, int cx, int cy); //����OpenGL����������С
    //afx_msg void ReSizeGLScene(int width, int height); //�Զ��庯������OpenGL�Ļ�����С���Ŵ��ڴ�С����
    virtual void OnDraw(CDC* pDC);  //����ͼ�εĺ�����OpenGL��ͼ��glBegin()��ʼ��glEnd()��β
    //afx_msg BOOL OnEraseBkgnd(CDC* pDC); //ǿ�Ʒ���TRUE����ֹˢ�±������´�����˸
    //afx_msg void OnDestroy(); //�������ͷ��ڴ�

/***************************************************************************************************/
/****************************************OpenGL��غ��Ĵ��� ����************************************/
/***************************************************************************************************/



/**********************************************MFC���ںͰ�ť��� ��ʼ****************************************/

    afx_msg void OnDrawRuler();
    afx_msg void OnDrawOrtho();
    afx_msg void OnDrawLine();
    afx_msg void OnDrawPoint();
    afx_msg void OnDrawCirclePerfect();
    afx_msg void OnDrawCircleOval();
    afx_msg void OnDrawPolygon();
    afx_msg void OnDrawFill();
    afx_msg void OnDrawSelect();
    afx_msg void OnDrawErase();
    afx_msg void OnDrawClear();

    afx_msg void OnFileSave();
    afx_msg void OnFileOpen();
    void ShowBitmap(CDC *pDC, CString BmpName);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

/**********************************************MFC���ںͰ�ť��� ����****************************************/






/**********************************************���� ��ʼ****************************************/

    //����Բ�εĵ�
    void point_circle(CDC *pDC, COLORREF color, int x, int y, int size);

    //����ʮ�ֵĵ�
    void point_cross(CDC *pDC, COLORREF color, int x, int y, int size);

    //�������εĵ�
    void point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size);

/**********************************************���� ��ʼ****************************************/





/**********************************************�����㷨 ��ʼ****************************************/

    //DDA��ֵ΢�ַ������ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
    void line_dda(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);

    //�е㷨���ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
    void line_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);

    //�е㷨���ߣ�б�����⣬ָ���߿���ֱ��ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
    void line_midpoint_vertical_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //�е㷨���ߣ�б�����⣬ָ���߿�ˮƽ��ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
    void line_midpoint_horizontal_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //�е㷨���ߣ�б�����⣬ָ���߿�������ˢ�ӣ�    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y���꣬�߿�
    void line_midpoint_square_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //bresenham�����ߣ�б�����⣻    ������pDC����ɫ�����x���꣬���y���꣬�յ�x���꣬�յ�y����
    void line_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);


    //CPen����
    void line_dda_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);
    void line_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);
    void line_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);

/**********************************************�����㷨 ����****************************************/


/**********************************************��Բ�㷨 ��ʼ****************************************/

    //bresenham������Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬�뾶
    void circle_perfect_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int radius);

    //bresenham������Բ-gl�棻    ������������ɫR��������ɫG��������ɫB��Բ��x���꣬Բ��y���꣬�뾶
    void circle_perfect_bresenham_gl(int colord1, int colord2, int colord3, int x0, int y0, int radius);

    //�е㷨����Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬�뾶
    void circle_perfect_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int radius);

    //�ԳƵػ�Բ�ϵĵ㣻    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬Ŀ����x���꣬Ŀ����y����
    void set_points_on_circle(CDC *pDC, COLORREF color, int x0, int y0, int x, int y);


    //bresenham������Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬����ĳ��ȣ�����ĳ���
    void circle_oval_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int a, int b);

    //�е㷨����Բ��    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬����ĳ��ȣ�����ĳ���
    void circle_oval_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int a, int b);
    
    //�ԳƵػ���Բ�ϵĵ㣻    ������pDC����ɫ��Բ��x���꣬Բ��y���꣬Ŀ����x���꣬Ŀ����y����
    void set_points_on_oval(CDC *pDC, COLORREF color, int x0, int y0, int x, int y);



    //CPen����
    void circle_perfect_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size);
    void circle_perfect_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size);
    void set_points_on_circle_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size);

    void circle_oval_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size);
    void circle_oval_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size);
    void set_points_on_oval_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size);

/**********************************************��Բ�㷨 ����****************************************/


/**********************************************��������㷨 ��ʼ****************************************/

    //����ζ�������ݽṹ
    typedef struct one_vertex_info {
        int x;
        int y;

        one_vertex_info() {}
        one_vertex_info(int xx, int yy) {
            this->x = xx;
            this->y = yy;
        }

    }vertex;

    //����ζ����
    vertex* PolygonVertex;

    //�ߵ����ݽṹ
    typedef struct one_edge_info {
        double y_high;         //�ߵ��϶˵��y����
        double x_intersection; //ɨ������ߵĽ����x����
        double delta_x;        //�ߵ�б�ʷ�֮һ��1/k
        struct one_edge_info* next_edge; //��һ���ߵ�ָ��
    }edge;

    //����߱�ET �� ���Ա߱�AEL
    edge* EdgeTable;
    edge* ActiveEdgeList;

    //����ε�ɨ��������㷨
    void set_PolygonVertex(int num, int array_vertex[][2]);
    void init_EdgeTable(int num, vertex* PolygonVertex);
    void insert_edge(edge* AELorET, int y, edge* one_edge);
    void del_edge(edge* AELorET, edge* one_edge);

    //CPen

    void flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt);

/**********************************************��������㷨 ����****************************************/


/**********************************************��άͼ�βü��㷨 ��ʼ****************************************/

    //���б���Ķ˵����ݽṹ
    typedef struct one_coded_vertex_info {
        int x;
        int y;
        int code;

        one_coded_vertex_info() {
            this->code = 0;
        }
        one_coded_vertex_info(int xx, int yy) {
            this->x = xx;
            this->y = yy;
            this->code = 0;
        }

    }vertex_coded;

    //���б����ֱ�߶ε����ݽṹ
    typedef struct one_line_info {
        vertex_coded vertex_coded_begin;
        vertex_coded vertex_coded_end;

        one_line_info() {}
        one_line_info(one_coded_vertex_info vb, one_coded_vertex_info ve) {
            this->vertex_coded_begin = vb;
            this->vertex_coded_end = ve;
        }

    }line;

    //Cohen-Sutherland+�е�ָ�������+�е�ָ���߶βü�    ������pDC����ɫ���ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬�����ߣ����ü���ֱ��
    void line_cut_Sutherland_midpoint(CDC *pDC, COLORREF color, vertex window_vertex_left_top, vertex window_vertex_right_bottom, int num, line lines[]);
    //�е�ָ�ݹ����ȷ���߶���ü��߿��ཻ����һ��    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬���ü���ֱ��
    vertex_coded line_cut_midpoint(vertex window_vertex_left_top, vertex window_vertex_right_bottom, line single_line);

    //ȷ���߶εĶ˵������Ǹ����򣬻�ȡ���Ӧ�ı���    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬�˵�ָ��
    void set_vertex_code(vertex window_vertex_left_top, vertex window_vertex_right_bottom, vertex_coded *v);


    //�жϲü���Խ��ߺʹ��ü��߶ε�λ�ù�ϵ    �������ü��߿�ĶԽ��ߵ���㣬�ü��߿�Խ��ߵ��յ㣬���ü��߶ε���㣬���ü��߶ε��յ�
    bool judge_line_pos(vertex window_vertex_a, vertex window_vertex_b, vertex_coded va, vertex_coded vb);

    //�õ��߶���Խ��ߵĽ���    �������ü���Խ��ߵ���㣬�ü���Խ��ߵ��յ㣬���ü��ߵ���㣬���ü��ߵ��յ�
    vertex_coded get_mid_point(vertex diagonal_vertex_a, vertex diagonal_vertex_b, vertex_coded va, vertex_coded vb);



    typedef struct one_polygon {
        int vertex_num;
        std::vector<vertex> vertexes;

        one_polygon() {
            this->vertex_num = 0;
            this->vertexes = {};
        }
        one_polygon(int n, std::vector<vertex> v) {
            this->vertex_num = n;
            this->vertexes = v;
        }
    }polygon;

    //Sutherland-Hodgman����߲ü���������βü������زü���ɵ��¶���Σ�    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬���ü��Ķ����
    polygon polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon);

    //���ֱ�ߺͲü���Ľ��㣨���ؽ��㴦����ֵ��    ���������ü����ߵ���ʼ�㣬���ü����ߵĽ����㣬�ü��߿��ĳһ����x=value��y=value��valueֵ����x=����y=��trueΪx��falseΪy��
    int get_intersection_point(vertex vb, vertex ve, int value, bool flag);

    //���ƶ����    ������PDC����ɫ����������������
    void draw_polygon(CDC *pDC, COLORREF color, polygon p);


    //CPen




/**********************************************��άͼ�βü��㷨 ����****************************************/



    /*
Ctrl+M+O �۵����з���
Ctrl+M+M �۵�����չ����ǰ����
Ctrl+M+L չ�����з���
    */


/**********************************************��άͼ�α任�㷨 ��ʼ****************************************/

    //�������ת�任    ������PDC����ɫ��ԭʼ����Σ���ת���ĵ㣬��ת�Ƕȣ��Ƕ��ƣ���������
    void transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle);




/**********************************************��άͼ�α任�㷨 ����****************************************/
    

    
    
};

#ifndef _DEBUG  // MFCOpenGL01View.cpp �еĵ��԰汾
inline CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const
   { return reinterpret_cast<CMFCOpenGL01Doc*>(m_pDocument); }
#endif

