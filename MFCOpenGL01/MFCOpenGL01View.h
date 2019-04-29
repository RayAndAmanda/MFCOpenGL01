/*
Ctrl+M+O �۵����з���
Ctrl+M+M �۵�����չ����ǰ����
Ctrl+M+L չ�����з���
*/

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
    virtual void OnDraw(CDC* pDC);
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




///��Ա����

protected:
    HGLRC m_hRC;

    CMFCOpenGL01Doc* m_pDoc = NULL;

    CRectTracker m_RectTracker; //ѡ���


    //����λͼ
    bool saveTag = false;
    CString saveFilePath = _T("D:\\");

    //��λͼ
    CString BmpName;                               //����ͼ���ļ��ļ���
    CString EntName;                               //����ͼ���ļ���չ��
    CBitmap m_bitmap;                              //����λͼ����






///MFC���ںͰ�ť���
public:
    afx_msg void OnDrawRuler();
    afx_msg void OnDrawOrtho();

    afx_msg void OnFileSave();
    afx_msg void OnFileOpen();
    void ShowBitmap(CDC *pDC, CString BmpName);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    
    
};

#ifndef _DEBUG  // MFCOpenGL01View.cpp �еĵ��԰汾
inline CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const
   { return reinterpret_cast<CMFCOpenGL01Doc*>(m_pDocument); }
#endif

