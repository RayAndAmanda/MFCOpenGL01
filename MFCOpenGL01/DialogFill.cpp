// DialogFill.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogFill.h"
#include "afxdialogex.h"

// DialogFill �Ի���

IMPLEMENT_DYNAMIC(DialogFill, CDialogEx)

DialogFill::DialogFill(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILL, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogFill::~DialogFill()
{
    m_pDoc = NULL;
}

void DialogFill::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, fill_color);
}


BEGIN_MESSAGE_MAP(DialogFill, CDialogEx)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogFill::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDOK, &DialogFill::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogFill ��Ϣ�������


void DialogFill::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = fill_color.GetColor();
}


void DialogFill::OnBnClickedOk()
{
    m_pDoc->m_operation = 10;

    EndDialog(0);
}
