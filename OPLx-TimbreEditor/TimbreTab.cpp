


#include "pch.h"
#include "TimbreEditor.h"
#include "afxdialogex.h"
#include "TimbreTab.h"
#include "ModuleTab.h"



IMPLEMENT_DYNAMIC(CTimbreTab, CDialogEx)



CTimbreTab::~CTimbreTab()
{
}



CTimbreTab::CTimbreTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_TIMBRE_TAB, pParent)
,mx(-1)
,my(-1)
,m_bEditing(false)
,m_iOperator(-1)
,m_bHighLight(false)
{
}



void CTimbreTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIMBRE_ALG0_STATIC, m_aCStaticCON[0]);
	DDX_Control(pDX, IDC_TIMBRE_ALG1_STATIC, m_aCStaticCON[1]);
}



BEGIN_MESSAGE_MAP(CTimbreTab, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



void CTimbreTab::OnCancel(){}



HBRUSH CTimbreTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	auto hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch (pWnd->GetDlgCtrlID()){
		case IDC_TIMBRE_CON_STATIC:{	SetColor(pDC, 0, 0); break; }
		case IDC_TIMBRE_FB_STATIC:{		SetColor(pDC, 1, 0); break; }
		case IDC_TIMBRE_NUM_STATIC:{	SetColor(pDC, 2, 0); break; }
		case IDC_TIMBRE_KML_STATIC:{	SetColor(pDC, 3, 0); break; }
		case IDC_TIMBRE_KMH_STATIC:{	SetColor(pDC, 4, 0); break; }
		case IDC_TIMBRE_EN_STATIC:{		SetColor(pDC, 5, 0); break; }
		case IDC_TIMBRE_FDE_STATIC:{	SetColor(pDC, 6, 0); break; }
		case IDC_TIMBRE_SEL_STATIC:{	SetColor(pDC, 7, 0); break; }
		case IDC_TIMBRE_AMD_STATIC:{	SetColor(pDC, 8, 0); break; }
		case IDC_TIMBRE_VBD_STATIC:{	SetColor(pDC, 9, 0); break; }
		case IDC_TIMBRE_KT_STATIC:{		SetColor(pDC, 10, 0); break; }
		case IDC_TIMBRE_FDT_STATIC:{	SetColor(pDC, 11, 0); break; }
		case IDC_TIMBRE_OPLL_STATIC:{	SetColor(pDC, 12, 0); break; }
		case IDC_TIMBRE_INST_STATIC:{	SetColor(pDC, 13, 0); break; }
		case IDC_TIMBRE_VOL_STATIC:{	SetColor(pDC, 14, 0); break; }
		case IDC_TIMBRE_SUS_STATIC:{	SetColor(pDC, 15, 0); break; }
		
		case IDC_TIMBRE_AR1_STATIC:{	SetColor(pDC, 0, 1); break; }
		case IDC_TIMBRE_DR1_STATIC:{	SetColor(pDC, 1, 1); break; }
		case IDC_TIMBRE_SL1_STATIC:{	SetColor(pDC, 2, 1); break; }
		case IDC_TIMBRE_RR1_STATIC:{	SetColor(pDC, 3, 1); break; }
		case IDC_TIMBRE_KSL1_STATIC:{	SetColor(pDC, 4, 1); break; }
		case IDC_TIMBRE_TL1_STATIC:{	SetColor(pDC, 5, 1); break; }
		case IDC_TIMBRE_MT1_STATIC:{	SetColor(pDC, 6, 1); break; }
		case IDC_TIMBRE_AM1_STATIC:{	SetColor(pDC, 7, 1); break; }
		case IDC_TIMBRE_VIB1_STATIC:{	SetColor(pDC, 8, 1); break; }
		case IDC_TIMBRE_EGT1_STATIC:{	SetColor(pDC, 9, 1); break; }
		case IDC_TIMBRE_KSR1_STATIC:{	SetColor(pDC, 10, 1); break; }
		case IDC_TIMBRE_VOID1_0_STATIC:{SetColor(pDC, 11, 1); break; }
		case IDC_TIMBRE_WF1_STATIC:{	SetColor(pDC, 12, 1); break; }
		case IDC_TIMBRE_VOID1_1_STATIC:{SetColor(pDC, 13, 1); break; }
		case IDC_TIMBRE_VOID1_2_STATIC:{SetColor(pDC, 14, 1); break; }
		case IDC_TIMBRE_VOID1_3_STATIC:{SetColor(pDC, 15, 1); break; }
		
		case IDC_TIMBRE_AR2_STATIC:{	SetColor(pDC, 0, 2); break; }
		case IDC_TIMBRE_DR2_STATIC:{	SetColor(pDC, 1, 2); break; }
		case IDC_TIMBRE_SL2_STATIC:{	SetColor(pDC, 2, 2); break; }
		case IDC_TIMBRE_RR2_STATIC:{	SetColor(pDC, 3, 2); break; }
		case IDC_TIMBRE_KSL2_STATIC:{	SetColor(pDC, 4, 2); break; }
		case IDC_TIMBRE_TL2_STATIC:{	SetColor(pDC, 5, 2); break; }
		case IDC_TIMBRE_MT2_STATIC:{	SetColor(pDC, 6, 2); break; }
		case IDC_TIMBRE_AM2_STATIC:{	SetColor(pDC, 7, 2); break; }
		case IDC_TIMBRE_VIB2_STATIC:{	SetColor(pDC, 8, 2); break; }
		case IDC_TIMBRE_EGT2_STATIC:{	SetColor(pDC, 9, 2); break; }
		case IDC_TIMBRE_KSR2_STATIC:{	SetColor(pDC, 10, 2); break; }
		case IDC_TIMBRE_VOID2_0_STATIC:{SetColor(pDC, 11, 2); break; }
		case IDC_TIMBRE_WF2_STATIC:{	SetColor(pDC, 12, 2); break; }
		case IDC_TIMBRE_VOID2_1_STATIC:{SetColor(pDC, 13, 2); break; }
		case IDC_TIMBRE_VOID2_2_STATIC:{SetColor(pDC, 14, 2); break; }
		case IDC_TIMBRE_VOID2_3_STATIC:{SetColor(pDC, 15, 2); break; }
		
		case IDC_TIMBRE_OP1_STATIC:{	SetColor(pDC, 0); break; }
		case IDC_TIMBRE_OP2_STATIC:{	SetColor(pDC, 1); break; }
	}
	
	return hbr;//(HBRUSH)GetStockObject(DKGRAY_BRUSH);
}



BOOL CTimbreTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	SetPicture(0);
	
	return FALSE;
}



void CTimbreTab::SetColor(CDC* pDC, int x, int y)
{
	auto b = (mx == x && my == y);
	pDC->SetTextColor((b)? ((m_bEditing)? RGB(255,160,128): GetSysColor(COLOR_3DFACE)): GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkColor((b)? GetSysColor(COLOR_WINDOWTEXT): GetSysColor(COLOR_3DFACE));
}



void CTimbreTab::SetColor(CDC* pDC, int iOperator)
{
	auto b = (m_iOperator == iOperator && m_bHighLight);
	pDC->SetTextColor((b)? RGB(255,160,128): GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkColor((b)? GetSysColor(COLOR_WINDOWTEXT): GetSysColor(COLOR_3DFACE));
}



void CTimbreTab::SetCur(int x, int y, bool bEditing)
{
	mx = x;
	my = y;
	m_bEditing = bEditing;
}



void CTimbreTab::SetPicture(int CON)
{
	for (int i = 0; i <= 1; ++i){
		m_aCStaticCON[i].ShowWindow((CON == i)? SW_SHOW: SW_HIDE);
	}
}



void CTimbreTab::SetOperator(int iOperator, bool bHighLight)
{
	m_iOperator = iOperator;
	m_bHighLight = bHighLight;
	
	switch (m_iOperator){
		case 0:{	GetDlgItem(IDC_TIMBRE_OP1_STATIC)->RedrawWindow();	break;	}
		case 1:{	GetDlgItem(IDC_TIMBRE_OP2_STATIC)->RedrawWindow();	break;	}
	}
}
