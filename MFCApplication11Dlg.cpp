
// MFCApplication11Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication11.h"
#include "MFCApplication11Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Stage(int Step);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication11Dlg 대화 상자



CMFCApplication11Dlg::CMFCApplication11Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION11_DIALOG, pParent)
	, Edit_Score(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, Edit_Score);
}

BEGIN_MESSAGE_MAP(CMFCApplication11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTT_START, &CMFCApplication11Dlg::OnClickedButtStart)
	ON_BN_CLICKED(IDC_BUTT_EXIT, &CMFCApplication11Dlg::OnClickedButtExit)
	ON_BN_CLICKED(IDC_BUTT_CONTINEW, &CMFCApplication11Dlg::OnBnClickedButtContinew)
END_MESSAGE_MAP()


// CMFCApplication11Dlg 메시지 처리기

BOOL CMFCApplication11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_STATIC_SCORE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_SCORE)->EnableWindow(FALSE);

	CClientDC dc(this);
	memDC.CreateCompatibleDC(&dc);
	bm.CreateCompatibleBitmap(&dc, 1920, 1080);
	memDC.SelectObject(&bm);

	srand((unsigned)time(NULL));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication11Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMFCApplication11Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.3
	bool truth = false;
	switch (pMsg->wParam)
	{
	case VK_RIGHT:
		if (Game_START) {
			if (playerbar_Rect.right >= 900);
			else {
				playerbar_left += 10;
				playerbar_right += 10;
				playerbar_Rect.OffsetRect(10, 0);
				ball_Rect[0].OffsetRect(10, 0);
				for (int i = 0; i < 3; i++) {
					playerbar_hitbox[i].OffsetRect(10, 0);
				}
			}
		}
		else {
			if (playerbar_Rect.right >= 900);
			else {
				playerbar_left += 10;
				playerbar_right += 10;
				playerbar_Rect.OffsetRect(10, 0);
				for (int i = 0; i < 3; i++) {
					playerbar_hitbox[i].OffsetRect(10, 0);
				}
			}
		}
		break;
	case VK_LEFT:
		if (Game_START) {
			if (playerbar_Rect.left <= 0);
			else {
				playerbar_left -= 10;
				playerbar_right -= 10;
				playerbar_Rect.OffsetRect(-10, 0);
				ball_Rect[0].OffsetRect(-10, 0);
				for (int i = 0; i < 3; i++) {
					playerbar_hitbox[i].OffsetRect(-10, 0);
				}
			}
		}
		else {
			if (playerbar_Rect.left <= 0);
			else {
				playerbar_left -= 10;
				playerbar_right -= 10;
				playerbar_Rect.OffsetRect(-10, 0);
				for (int i = 0; i < 3; i++) {
					playerbar_hitbox[i].OffsetRect(-10, 0);
				}
			}
		}
		break;
	case VK_UP:
		if (Game_START) {
			if (catch_item)
			{
				for (int i = 0; i < 3; i++)
				{
					if (ball_truth[i])
					{
						ball_x[i] = ball_x_speed_save;
						ball_y[i] = ball_y_speed_save;
						Up = false;
						Game_START = false;
					}
				}
			}
			else
			{
				ball_y[0] = -2;
				ball_x[0] = 1;
				Game_START = false;
			}
		}
		break;
	case VK_ESCAPE:
		KillTimer(1);
		OnOK();
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCApplication11Dlg::OnClickedButtStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int x, y;
	GetDlgItem(IDC_BUTT_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_EXIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_CONTINEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_CONTINEW)->EnableWindow(FALSE);


	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT_SCORE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_SCORE)->EnableWindow(TRUE);

	playerbar_Rect.SetRect(325, 725, 425, 750);
	ball_Rect[0].SetRect(368, 711, 382, 725);
	ball_Rect[1].SetRect(-5, -5, -5, -5);
	ball_Rect[2].SetRect(-5, -5, -5, -5);
	
	playerbar_hitbox[0].SetRect(325, 725, 341, 750);
	playerbar_hitbox[1].SetRect(341, 725, 409, 750);
	playerbar_hitbox[2].SetRect(409, 725, 425, 750);

	UpdateData(FALSE);
	Game_START = true;
	SetTimer(1, 1, NULL);
}
void CMFCApplication11Dlg::OnClickedButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
void CMFCApplication11Dlg::OnBnClickedButtContinew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTT_START)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_EXIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_CONTINEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_CONTINEW)->EnableWindow(FALSE);


	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_EDIT_SCORE)->ShowWindow(SW_SHOWNORMAL);
	GetDlgItem(IDC_STATIC_SCORE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SCORE)->EnableWindow(TRUE);
	
	
	SetTimer(1, 1, NULL);
	SetTimer(2, 1, NULL);
}
void CMFCApplication11Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static int ball_count = 1, ball_Timer = 0, ballcatch_save_speed = 0, stage = 1, block_Count = 0;
	static bool item_truth[7] = { false,false,false,false,false,false }, stage_Turn = true;
	int i, index;
	CClientDC dc(this);
	CBrush playerbar_Color, ball_Color, block_Color, background_Color, playerbar_life_Color, item_Color[7];

	playerbar_Color.CreateSolidBrush(RGB(140, 140, 140));		// playerbar 색
	ball_Color.CreateSolidBrush(RGB(92, 209, 229));				// ball 색
	background_Color.CreateSolidBrush(RGB(255, 255, 255));
	block_Color.CreateSolidBrush(RGB(255, 217, 236));
	playerbar_life_Color.CreateSolidBrush(RGB(140, 140, 140));

	item_Color[0].CreateSolidBrush(RGB(95, 0, 255));		// 목숨추가 아이템
	item_Color[1].CreateSolidBrush(RGB(255, 54, 54));		// 레이저 아이템
	item_Color[2].CreateSolidBrush(RGB(19, 19, 255));		// plyaerbar 길이 증가 아이템
	item_Color[3].CreateSolidBrush(RGB(47, 237, 40));		// ball이 playerbar에 달라붙는 아이템
	item_Color[4].CreateSolidBrush(RGB(255, 187, 0));		// ball 속도가 느려지는 아이템
	item_Color[5].CreateSolidBrush(RGB(255, 18, 239));		// 스테이지 넘기는 아이템
	item_Color[6].CreateSolidBrush(RGB(0, 216, 255));		// ball이 3개로 나뉘는 아이템
	UpdateData(TRUE);
	if (stage_Turn)
		Stage(stage);
	memDC.SelectObject(&background_Color);
	memDC.Rectangle(0, 0, 900, 800); // 맵 크기

	memDC.SelectObject(&playerbar_Color);
	memDC.Rectangle(playerbar_Rect);
	index = 0;
	for (i = 0; i < life; i++)
	{
		playerbar_life[i].SetRect(index, 785, index + 50, 797);
		index += 51;
		memDC.SelectObject(&playerbar_life_Color);
		memDC.Rectangle(playerbar_life[i]);
	}

	memDC.SelectObject(&block_Color); // block 그리기
	for (i = 0; i < 91; i++)
	{
		memDC.Rectangle(block[i]);
	}
	for (index = 0; index < 3; index++) // ball과 block 판정
	{
		for (i = 0; i < 91; i++)
		{
			if (ball_truth[index])
			{
				ball_block(index, i, ball_count, &stage_Turn, item_truth);
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (item_truth[i]) // 아이템 생성 및 효과
		{
			item_Effect(i, item_Color, &ball_count, &stage_Turn, item_truth);
		}
	}

	Ball_Speed();
	for (i = 0; i < 3; i++) // ball과 playerbar 판정
	{
		if (ball_truth[i])
		{
			for (index = 0; index < 3; index++)
			{
				playerbar_Move(i, index);
			}
			Ball_Move(i, ball_count, item_truth);// 공이 벽에 부딪혔을 때
		}
	}
	memDC.SelectObject(&ball_Color);
	for (int i = 0; i < 3; i++) // ball 이동방향
	{
		if (ball_truth[i])
		{
			memDC.Ellipse(ball_Rect[i]);
			ball_Rect[i].OffsetRect(ball_x[i], ball_y[i]);
		}
	}
	dc.BitBlt(0, 0, 900, 800, &memDC, 0, 0, SRCCOPY);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication11Dlg::playerbar_Move(int i, int index)
{
	static int ball_speed = 3;
	bool ball_up_down = false;
	if (block_judgment.IntersectRect(ball_Rect[i], playerbar_hitbox[index]))
	{
		if (catch_item && Up == false)
		{
			ball_x_speed_save = ball_x[i];
			ball_y_speed_save = ball_y[i] * -1;
			Game_START = true;
			ball_x[i] = 0;
			ball_y[i] = 0;
			ball_Rect[i].SetRect(ball_Rect[i].left, ball_Rect[i].top - 3, ball_Rect[i].right, ball_Rect[i].bottom - 3);
			Up = true;
		}
		else
		{
			if (ball_x[i] < 0)
			{
				ball_up_down = false;
			}
			else
			{
				ball_up_down = true;
			}
			if (index == 0)
			{
				if (ball_up_down)
				{
					ball_x[i] *= -1;
				}
				else
				{
					ball_x[i] -= 1;
				}
			}
			else if (index == 2)
			{
				if (ball_up_down == false)
				{
					ball_x[i] *= -1;
				}
				else
				{
					ball_x[i] += 1;
				}
			}
			else
			{
				if (playerbar_left - playerbar_save_left > 0)
				{
					ball_x[i] += 1;
				}
				else if (playerbar_left - playerbar_save_left < 0)
				{
					ball_x[i] -= 1;
				}
				if (ball_x[i] + ball_y[i] > ball_speed)
				{
					ball_x[i] = ball_speed - ball_y[i];
				}
				if (ball_x[i] == 0 && ball_up_down)
				{
					ball_x[i] = 1;
				}
				else if (ball_x[i] == 0 && ball_up_down == false)
				{
					ball_x[i] = -1;
				}
			}
			ball_y[i] *= -1;
		}
	}
}

void CMFCApplication11Dlg::Ball_Move(int ball_number, int ball_count, bool *item_truth)
{
	if (ball_Rect[ball_number].left <= 0 || ball_Rect[ball_number].right >= 900)
	{
		ball_x[ball_number] *= -1;
	}
	if (ball_Rect[ball_number].top <= 0)
	{
		ball_y[ball_number] *= -1;
	}
	if (ball_Rect[ball_number].bottom <= 800)
	{
		ball_truth[ball_number] = false;
		ball_count -= 1;
		ball_x[ball_number] = 0;
		ball_y[ball_number] = 0;
		ball_Rect[ball_number].SetRect(-10, -10, -10, -10);
		if (ball_count == 1)
			item_truth[6] = false;
		else if (ball_count <= 0) // 공이 없어졌을때
		{
			catch_item = false;
			life -= 1;
			for (int a = 0; a < 7; a++)
			{
				item_Rect[a].SetRect(-10, -10, -10, -10);
				item_truth[a] = false;
			}
			catch_item = false;
			if (life < 0)
			{ // 목숨이 없을때
				KillTimer(1);
				MessageBox("GAME OVER", "알림", NULL);
				OnOK();
			}
			else
			{ // 목숨이 있을때
				ball_Rect[0].SetRect(playerbar_left + 43, 711, playerbar_right - 43, 725);
				playerbar_Rect.SetRect(playerbar_left, 725, playerbar_right, 750);
				playerbar_hitbox[0].SetRect(playerbar_left, 725, playerbar_left + 16, 750);
				playerbar_hitbox[1].SetRect(playerbar_left + 16, 725, playerbar_left + 84, 750);
				playerbar_hitbox[2].SetRect(playerbar_left + 84, 725, playerbar_left + 100, 750);
				ball_count = 1;
				ball_truth[0] = true;
				Game_START = true;
			}
		}
	}
}

void CMFCApplication11Dlg::Ball_Speed()
{
	static int ball_Timer = 0, speed_Up = 0;
	ball_Timer++;
	if (ball_Timer >= 100)
	{
		playerbar_save_left = playerbar_left;
		ball_Timer = 0;
		speed_Up++;
	}
	if (speed_Up >= 20)
	{
		for (int i = 0; i < 3; i++)
		{
			if (ball_truth[i])
			{
				if (ball_y[i] > 0)
					ball_y[i]++;
				else
					ball_y[i]--;
			}
		}
		speed_Up = 0;
	}
}

void CMFCApplication11Dlg::Stage(int Step)
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	switch (Step)
	{
	case 1:
		x = 2, y = 100;
		for (int i = 0; i < 91; i++) {
			block[i].SetRect(x, y, x + 68, y + 30);
			x += 69;
			if (x >= 897) {
				x = 2;
				y += 31;
			}
		}
		break;
	case 2:
		x = 2, y = 60;
		int a = 0;
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < i + 1; j++)
			{
				block[a++].SetRect(x, y, x + 68, y + 30);
				x += 69;
			}
			x = 2;
			y += 31;
		}
	}
}

void CMFCApplication11Dlg::ball_block(int index, int i, int ball_count, bool* stage_Turn, bool* item_truth)
{
	static int block_Count = 0;
	bool bounce = true;
	if (block_judgment.IntersectRect(ball_Rect[index], block[i]))
	{
		block_Count++;
		Edit_Score += 50;
		if (bounce)
		{
			bounce = false;
			if (ball_Rect[index].top < block[i].top)
			{
				ball_y[index] *= -1;
			}
			else if (ball_Rect[index].bottom > block[i].bottom)
			{
				ball_y[index] *= -1;
			}
			else if (ball_Rect[index].left < block[i].left)
			{
				ball_x[index] *= -1;
			}
			else if (ball_Rect[index].right > block[i].right)
			{
				ball_x[index] *= -1;
			}
		}
		int Randomitem = rand() % 100;
		if (Randomitem >= 0 && Randomitem < 6)
		{
			if (item_truth[Randomitem] == false)
			{
				item_Rect[Randomitem].SetRect(block[i].left, block[i].top, block[i].right, block[i].bottom);
				item_truth[Randomitem] = true;
			}
		}
		else if (Randomitem == 6 && ball_count == 1)
		{
			if (item_truth[Randomitem] == false)
			{
				item_Rect[Randomitem].SetRect(block[i].left, block[i].top, block[i].right, block[i].bottom);
				item_truth[Randomitem] = true;
			}
		}
		block[i].SetRect(-5, -5, -5, -5);
		if ((block_Count >= 91) || (block_Count >= 90))
		{
			block_Count = 0;
			*stage_Turn = true;
			Game_START = true;
			for (int i = 0; i < 3; i++)
			{
				ball_x[i] = 0;
				ball_y[i] = 0;
			}
			KillTimer(1);
			MessageBox("clear", "알림", NULL);
			SetTimer(1, 1, NULL);
			playerbar_Rect.SetRect(325, 725, 425, 750);
			playerbar_left = 325;
			ball_Rect[0].SetRect(368, 711, 382, 725);
			ball_Rect[1].SetRect(-5, -5, -5, -5);
			ball_Rect[2].SetRect(-5, -5, -5, -5);

			for (int a = 0; a < 7; a++)
			{
				item_Rect[a].SetRect(-10, -10, -10, -10);
				item_truth[a] = false;
			}
			catch_item = false;
			playerbar_hitbox[0].SetRect(325, 725, 341, 750);
			playerbar_hitbox[1].SetRect(341, 725, 409, 750);
			playerbar_hitbox[2].SetRect(409, 725, 425, 750);

		}
	}
}

void CMFCApplication11Dlg::item_Effect(int i, CBrush *item_Color, int *ball_count, bool * stage_Turn, bool *item_truth)
{
	memDC.SelectObject(&item_Color[i]);
	memDC.Rectangle(item_Rect[i]);
	if (block_judgment.IntersectRect(item_Rect[i], playerbar_Rect))
	{
		item_Rect[i].SetRect(-10, -10, -10, -10);
		switch (i)
		{
		case 0:
			life++;
			break;
		case 1:
			break;
		case 2:
			playerbar_Rect.SetRect(playerbar_left - 25, 725, playerbar_left + 125, 750);
			playerbar_hitbox[0].SetRect(playerbar_Rect.left, 725, playerbar_Rect.left + 25, 750);
			playerbar_hitbox[1].SetRect(playerbar_Rect.left + 26, 725, playerbar_Rect.left + 99, 750);
			playerbar_hitbox[2].SetRect(playerbar_Rect.left + 100, 725, playerbar_left + 125, 750);
			break;
		case 3:
			if (*ball_count > 1)
				catch_item = false;
			else
				catch_item = true;

			break;
		case 4: // ball 느려지는 아이템
			for (int index = 0; index < 3; index++)
			{
				if (ball_y[index] > 0)
					ball_y[index] = 1;
				else
					ball_y[index] = -1;
			}
			break;
		case 5:
			*stage_Turn = true;
			Game_START = true;
			for (int i = 0; i < 3; i++)
			{
				ball_x[i] = 0;
				ball_y[i] = 0;
			}
			KillTimer(1);
			MessageBox("clear", "알림", NULL);
			SetTimer(1, 1, NULL);
			playerbar_Rect.SetRect(325, 725, 425, 750);
			ball_Rect[0].SetRect(368, 711, 382, 725);
			ball_Rect[1].SetRect(-5, -5, -5, -5);
			ball_Rect[2].SetRect(-5, -5, -5, -5);

			playerbar_hitbox[0].SetRect(325, 725, 341, 750);
			playerbar_hitbox[1].SetRect(341, 725, 409, 750);
			playerbar_hitbox[2].SetRect(409, 725, 425, 750);
			break;
		case 6:
			int save;
			for (int index = 0; index < 3; index++)
			{
				if (ball_truth[index])
				{
					save = index;
				}
				ball_truth[index] = true;
			}
			*ball_count = 3;
			ball_x[0] = ball_x[save];
			ball_y[0] = ball_y[save];
			for (int index = 0; index < 3; index++)
			{
				if (ball_x[0] > 0 && index != 0)
				{
					ball_x[index] = ball_x[0] + index;
				}
				else if (ball_x[0] < 0 && index != 0)
				{
					ball_x[index] = ball_x[0] - index;
				}
				ball_y[index] = ball_y[0];
				ball_Rect[index].SetRect(ball_Rect[save].left, ball_Rect[save].top, ball_Rect[save].right, ball_Rect[save].bottom);
			}
			break;
		}
		item_Rect[i] = false;
	}
	item_Rect[i].OffsetRect(0, 2);
	if (item_Rect[i].top >= 800)
	{
		item_truth[i] = false;
	}
}