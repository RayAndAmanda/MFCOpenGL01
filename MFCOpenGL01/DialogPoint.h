#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogPoint �Ի���

class DialogPoint : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPoint)

public:
	DialogPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogPoint();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;
    

public:
    afx_msg void OnBnClickedOk();
    CMFCColorButton point_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    int point_radio_group;
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
};
