
// MFCApplication11Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication11Dlg 대화 상자
class CMFCApplication11Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication11Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION11_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedButtStart();
	afx_msg void OnClickedButtExit();
	afx_msg void OnBnClickedButtContinew();
	CRect playerbar_Rect, ball_Rect[3], lazer_beam[100], item_Rect[7], block[100], playerbar_life[10], playerbar_hitbox[3], razer_beam[20];
	CRect block_judgment;
	CDC memDC;
	CBitmap bm;
	int ball_x[3] = { 0,0,0 }, ball_y[3] = { 0,0,0 }, playerbar_left = 325, playerbar_right = 425, life = 10, playerbar_save_left = 0;
	bool Game_START = false, catch_item = false;
	int Edit_Score;
	int ball_x_speed_save = 0;
	int ball_y_speed_save = 0;
	bool ball_truth[3] = { true,false,false };
	bool Up = false;
	void CMFCApplication11Dlg::Stage(int Step);
	void CMFCApplication11Dlg::Ball_Move(int ball_number, int ball_count, bool *item_truth);
	void CMFCApplication11Dlg::Ball_Speed();
	void CMFCApplication11Dlg::ball_block(int index, int i, int ball_count, bool* stage_Turn, bool* item_truth);
	void CMFCApplication11Dlg::item_Effect(int i, CBrush* item_Color, int *ball_count, bool* stage_Turn, bool* item_truth);
	void CMFCApplication11Dlg::playerbar_Move(int i, int index);
};
