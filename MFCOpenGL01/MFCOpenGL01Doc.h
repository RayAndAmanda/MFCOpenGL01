
// MFCOpenGL01Doc.h : CMFCOpenGL01Doc ��Ľӿ�
//


#pragma once

class CMFCOpenGL01Doc : public CDocument
{
protected: // �������л�����
	CMFCOpenGL01Doc();
	DECLARE_DYNCREATE(CMFCOpenGL01Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMFCOpenGL01Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // ���ɵ���Ϣӳ�亯��
protected:
    DECLARE_MESSAGE_MAP()



///�Զ����ݽṹ
public:

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

    //�Զ����������ݽṹ
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




    ///����ֱ�����ڻ�ͼ�����ݽṹ

    typedef struct draw_point {
        CPoint p;
        int type; //ָ �������
        int size;
        COLORREF color;

        draw_point(CPoint p, int type, int size, COLORREF color) {
            this->p = p;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_point;

    typedef struct draw_line {
        CPoint p1, p2;
        int type; //ָ �ߵ��㷨
        int size;
        COLORREF color;

        draw_line(CPoint p1, CPoint p2, int type, int size, COLORREF color) {
            this->p1 = p1;
            this->p2 = p2;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_line;

    typedef struct draw_perfect_circle {
        CPoint p0;
        int radius;
        int type;
        int size;
        COLORREF color;

        draw_perfect_circle(CPoint p0, int radius, int type, int size, COLORREF color) {
            this->p0 = p0;
            this->radius = radius;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_perf_circle;

    typedef struct draw_oval_circle {
        CPoint p0;
        int a, b;
        int angle; //˳ʱ����ת�Ƕ�
        int type;
        int size;
        COLORREF color;

        draw_oval_circle(CPoint p0, int a, int b, int angle, int type, int size, COLORREF color) {
            this->p0 = p0;
            this->a = a;
            this->b = b;
            this->angle = angle;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_oval_circle;

    typedef struct draw_polygon {
        std::vector<CPoint> ps;
        int size;
        COLORREF color;

        draw_polygon(std::vector<CPoint> ps, int size, COLORREF color) {
            this->ps = ps;
            this->size = size;
            this->color = color;
        }
    }d_polygon;

    typedef struct draw_fill {
        CPoint p;
        COLORREF color;

        draw_fill(CPoint p, COLORREF color) {
            this->p = p;
            this->color = color;
        }
    }d_fill;




///��ͼ���ݴ洢
public:

    //�洢���л�ͼ����
    std::vector<d_point> v_point;
    std::vector<d_line> v_line;
    std::vector<d_perf_circle> v_perf_circle;
    std::vector<d_oval_circle> v_oval_circle;
    std::vector<d_polygon> v_polygon;
    std::vector<d_fill> v_fill;


    double pi = acos(-1.0);

    //��ǰ��������ǰ��ɫ����ǰ�߿�
    int m_operation; //0�ޣ�1�㣬2�ߣ�3��Բ��4��Բ��5����Σ�10��䣬20/21�ü���30��Ƥ��
    COLORREF m_color;
    int m_size;


    //�Ի����еı���
    //������͡��ߵ����͡���Բ�����͡���Բ�����ͣ�����ָ��ͬ���㷨��
    int point_type, line_type, circle_perfect_type, circle_oval_type;

    //�����
    polygon m_polygon;
    BOOL is_drawing_polygon = FALSE;




    //�ϴα�ѡ�е�ͼ��
    int selected_point = -1, selected_line = -1, selected_perfect_circle = -1, selected_oval_circle = -1, selected_polygon = -1;


    ///Ѱ������Ƿ�ѡ��ͼ��

    void select_all(CDC *pDC, CPoint point);

    //ѡ�е�
    int select_point(CPoint pos);

    //ѡ����
    int select_line(CPoint pos);

    //ѡ����Բ
    int select_perfect_circle(CPoint pos);

    //ѡ����Բ
    int select_oval_circle(CPoint pos);

    //ѡ�ж����
    int select_polygon(CPoint pos);
    



    //ˢ�����л��Ƶ�ͼ��
    void flush_all_drawing(CDC *pDC);

    //���ƶ����
    void draw_polygon_cpen(CDC *pDC, d_polygon p);

    



    ///���� ��ʼ

    //����Բ�εĵ�
    void point_circle(CDC *pDC, COLORREF color, int x, int y, int size);

    //����ʮ�ֵĵ�
    void point_cross(CDC *pDC, COLORREF color, int x, int y, int size);

    //�������εĵ�
    void point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size);







    ///�����㷨 ��ʼ

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





    ///��Բ�㷨 ��ʼ

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

    //������ת�Ƕȵ���Բ��˳ʱ����ת  ������pDC����ɫ��Բ��x��Բ��y������a������b����ת�Ƕȣ��Ƕ��ƣ����߿�
    void circle_oval_angle_cpen(CDC *pDC, COLORREF color, float x0, float y0, float a, float b, double angle, int size);




    ///��������㷨 ��ʼ

    //CPen

    void flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt);







    ///��άͼ�βü��㷨 ��ʼ


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



    //Sutherland-Hodgman����߲ü���������βü������زü���ɵ��¶���Σ�    �������ü����ڷ�Χ�����Ϸ������꣬�ü����ڷ�Χ�����·������꣬���ü��Ķ����
    polygon polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon);

    //���ֱ�ߺͲü���Ľ��㣨���ؽ��㴦����ֵ��    ���������ü����ߵ���ʼ�㣬���ü����ߵĽ����㣬�ü��߿��ĳһ����x=value��y=value��valueֵ����x=����y=��trueΪx��falseΪy��
    int get_intersection_point(vertex vb, vertex ve, int value, bool flag);

    //���ƶ����    ������PDC����ɫ����������������
    void draw_polygon(CDC *pDC, COLORREF color, polygon p);


    //CPen









    ///��άͼ�α任�㷨 ��ʼ

    //ƽ��
    void transform_translate();

    //�������ת�任    ������PDC����ɫ��ԭʼ����Σ���ת���ĵ㣬��ת�Ƕȣ��Ƕ��ƣ���������
    void transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle);

    //��ת
    void transform_rotate();

    //����
    void transform_scale();

    //�Գ�
    void transform_symmetry();

    //����
    void transform_shear();

    //����
    void transform_affline();

    //����
    void transform_compound();


#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
