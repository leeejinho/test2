#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Monster.h"


#include "Butterfly.h"
#include "Player.h"
#include "StageMgr.h"
#include "ZigZag.h"
#include "Circle_Monster.h"

#include <time.h>

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	srand(unsigned(time(NULL)));


	CObj* pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::PLAYER);
	CStageMgr::Get_Instance()->Initialize();


	CObjMgr::Get_Instance();
}

void CMainGame::Update()
{
	CStageMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	RECT rc{ 0, 0, WINCX, WINCY };

	Rectangle(m_hDC, rc.left, rc.top, rc.right, rc.bottom);

	CObjMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	CObjMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
