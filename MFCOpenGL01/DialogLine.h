#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogLine �Ի���

class DialogLine : public CDialogEx
{
	DECLARE_DYNAMIC(DialogLine)

public:
	DialogLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogLine();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;

public:
    CMFCColorButton line_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    afx_msg void OnBnClickedLineDda();
    afx_msg void OnBnClickedLineMidpoint();
    afx_msg void OnBnClickedLineBresenham();
};
