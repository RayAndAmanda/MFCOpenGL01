#pragma once
#include "afxcolorbutton.h"


// DialogFill �Ի���

class DialogFill : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFill)

public:
	DialogFill(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogFill();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CMFCColorButton fill_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    afx_msg void OnBnClickedOk();
};
