#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogCirclePerfect �Ի���

class DialogCirclePerfect : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCirclePerfect)

public:
	DialogCirclePerfect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCirclePerfect();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CIRCLE_PERFECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;

public:
    CMFCColorButton circle_perfect_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    afx_msg void OnBnClickedCirclePerfectBresenham();
    afx_msg void OnBnClickedCirclePerfectMidpoint();
    afx_msg void OnBnClickedButtonCirclePerfectXxx();
};
