// Ule4JisDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "KeyEmulator.h"

// Ule4JisDlg �_�C�A���O
class Ule4JisDlg : public CDialog
{
// �R���X�g���N�V����
public:
	Ule4JisDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ULE4JP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

private:
	// added
	enum Strategy { USonJISKeyboard, USonJISRemote };
	NOTIFYICONDATA notifyIconData;
	Strategy currentStrategy;

	void showTaskTrayPopupMenu();
	void changeTaskTrayIconToUS();
	void changeTaskTrayIconToJIS();
	void changeTaskTrayIconToRemote();
	void changeTaskTrayIconToKeyboard();
	void changeStorategyToRemote();
	void changeStorategyToKeyboard();
// ����
protected:
	HICON m_hIcon;
	std::auto_ptr<KeyEmulator> keyEmulator;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedHide();
};
