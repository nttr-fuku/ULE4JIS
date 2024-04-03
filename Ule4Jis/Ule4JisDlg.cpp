// Ule4JisDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Ule4Jis.h"
#include "Ule4JisDlg.h"
#include "KeyEmulator.h"
#include "USonJISStrategy.h"
#include "USonJISRemoteStrategy.h"
#include "USonJISKeyboardStrategy.h"
#include "Constants.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CStatic urlLabel;
	HCURSOR handCursor;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT_URL, urlLabel);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// Ule4JisDlg �_�C�A���O




Ule4JisDlg::Ule4JisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ule4JisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ule4JisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ule4JisDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_HIDE, &Ule4JisDlg::OnBnClickedHide)
END_MESSAGE_MAP()


// Ule4JisDlg ���b�Z�[�W �n���h��

BOOL Ule4JisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	// add icon into task tray
	NOTIFYICONDATA &nid = this->notifyIconData;
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = MSG_TASKTRAY_CALLBACK;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CString title;
	GetWindowText(title);
	_tcscpy_s(nid.szTip, sizeof(nid.szTip) / sizeof(TCHAR), title);

	if (!Shell_NotifyIcon(NIM_ADD, &nid)) {
		MessageBox(_T("failed to initialize tasktray icon."), NULL, MB_OK | MB_ICONEXCLAMATION);
		::PostQuitMessage(-1);
		return FALSE;
	}

	// initialize emulator
	USonJISStrategy strategy;
	this->keyEmulator.reset(new KeyEmulator(&strategy));
	this->keyEmulator->start();

	// save current strategy type
	this->currentStrategy = USonJISRemote;

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void Ule4JisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void Ule4JisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR Ule4JisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL Ule4JisDlg::DestroyWindow()
{
	// delete icon from tasktray
	::Shell_NotifyIcon(NIM_DELETE, &this->notifyIconData);

	return CDialog::DestroyWindow();
}

LRESULT Ule4JisDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_TASKTRAY_CALLBACK:
		// dispatch tasktray callback message
		switch (lParam) {
		case WM_RBUTTONUP:
			// show popup menu
			showTaskTrayPopupMenu();
			break;
		case WM_LBUTTONDBLCLK:
			ShowWindow(SW_SHOW);
			ShowWindow(SW_RESTORE);
			break;
		default:
			break;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_TASKTRAY_START:
			this->keyEmulator->start();
			changeTaskTrayIconToUS();
			break;
		case ID_TASKTRAY_STOP:
			this->keyEmulator->end();
			changeTaskTrayIconToJIS();
			break;
		case ID_TASKTRAY_RESTART:
			this->keyEmulator->end();
			this->keyEmulator->start();
			break;
		case ID_TASKTRAY_EXIT:
			::PostQuitMessage(0);
			break;
		case ID_STRATEGY_REMOTE:
			this->keyEmulator->end();
			changeStorategyToRemote();
			this->keyEmulator->start();
			changeTaskTrayIconToRemote();
			break;
		case ID_STRATEGY_KEYBOARD:
			this->keyEmulator->end();
			changeStorategyToKeyboard();
			this->keyEmulator->start();
			changeTaskTrayIconToKeyboard();
		default:
			break;
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void Ule4JisDlg::changeTaskTrayIconToUS() {
	this->notifyIconData.hIcon = ::AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	::Shell_NotifyIcon(NIM_MODIFY, &this->notifyIconData);
}

void Ule4JisDlg::changeTaskTrayIconToJIS() {
	this->notifyIconData.hIcon = ::AfxGetApp()->LoadIcon(IDR_ICON_JIS);
	::Shell_NotifyIcon(NIM_MODIFY, &this->notifyIconData);
}
void Ule4JisDlg::changeTaskTrayIconToRemote() {
	this->notifyIconData.hIcon = ::AfxGetApp()->LoadIcon(IDR_ICON_REMOTE);
	::Shell_NotifyIcon(NIM_MODIFY, &this->notifyIconData);
}
void Ule4JisDlg::changeTaskTrayIconToKeyboard() {
	this->notifyIconData.hIcon = ::AfxGetApp()->LoadIcon(IDR_ICON_KEYBOARD);
	::Shell_NotifyIcon(NIM_MODIFY, &this->notifyIconData);
}

void Ule4JisDlg::changeStorategyToRemote() {
	USonJISRemoteStrategy strategy;
	this->keyEmulator.reset(new KeyEmulator(&strategy));
	this->currentStrategy = USonJISRemote;
}
void Ule4JisDlg::changeStorategyToKeyboard() {
	USonJISKeyboardStrategy strategy;
	this->keyEmulator.reset(new KeyEmulator(&strategy));
	this->currentStrategy = USonJISKeyboard;
}


void Ule4JisDlg::showTaskTrayPopupMenu() {
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.LoadMenu(IDR_MENU_TASKTRAY);

	CMenu *subMenu = menu.GetSubMenu(0);
	
	// set menu state
	if (this->keyEmulator->isStarted()) {
		subMenu->EnableMenuItem(ID_TASKTRAY_START, MF_GRAYED);
	} else {
		subMenu->EnableMenuItem(ID_TASKTRAY_STOP, MF_GRAYED);
	}

	if (this->currentStrategy == USonJISRemote) {
		subMenu->EnableMenuItem(ID_STRATEGY_REMOTE, MF_GRAYED);
	} else {
		subMenu->EnableMenuItem(ID_STRATEGY_KEYBOARD, MF_GRAYED);
	}

	//if (this->currentStrategy == USonJIS) {
	//	subMenu->GetSubMenu(0)->EnableMenuItem(ID_STRATEGY_USONJIS, MF_GRAYED);
	//} else {
	//	subMenu->GetSubMenu(0)->EnableMenuItem(ID_STRATEGY_JISONUS, MF_GRAYED);
	//}
	subMenu->TrackPopupMenu(TPM_BOTTOMALIGN | TPM_RIGHTALIGN, point.x, point.y, this);
}

void Ule4JisDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
	if (nType == SIZE_MINIMIZED) {
		ShowWindow(SW_HIDE);
	}
}

void Ule4JisDlg::OnBnClickedHide()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	ShowWindow(SW_MINIMIZE);
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ������ DC �̑�����ύX���Ă��������B

	// TODO:  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B

	// set color 'blue' to draw URL text.
	if (pWnd == &this->urlLabel) {
		pDC->SetTextColor(RGB(0, 0, 0xFF));
	}

	return hbr;
}

BOOL CAboutDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDC_ABOUT_URL) {
		if (HIWORD(wParam) == STN_CLICKED) {
			HINSTANCE result = ::ShellExecute(NULL, _T("open"), DEZZ_NETWORKS_URL, NULL, NULL, SW_SHOWNORMAL);
			if ((LONG)result <= 32) {
				// error. but since this is not critical problem, i ignore this :P
			}
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// set hand cursor if a pointer is over url-label
	if (pWnd == &this->urlLabel) {
		SetCursor(this->handCursor);
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������

	// get hand cursor handle
	this->handCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
