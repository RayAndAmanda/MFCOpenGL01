#pragma once

#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"
// DialogBezier �Ի���

class DialogBezier : public CDialogEx
{
	DECLARE_DYNAMIC(DialogBezier)

public:
	DialogBezier(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogBezier();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BEZIER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;
    CMFCColorButton bezier_color;


public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedMfccolorbutton1();
    
};
