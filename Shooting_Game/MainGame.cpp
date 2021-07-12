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
#include "KeyMgr.h"

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
	srand(unsigned(time(NULL)));

	m_hDC = GetDC(g_hWnd);
	m_BackDC = CreateCompatibleDC(m_hDC);
	m_backBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_oldBit = (HBITMAP)SelectObject(m_BackDC, m_backBit);


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

	Rectangle(m_BackDC, rc.left, rc.top, rc.right, rc.bottom);

	CObjMgr::Get_Instance()->Render(m_BackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_BackDC, 0, 0, SRCCOPY);



}

void CMainGame::Release()
{
	CObjMgr::Destroy_Instance();
	CStageMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();

	SelectObject(m_BackDC, m_oldBit);
	DeleteDC(m_BackDC);
	DeleteObject(m_backBit);

	ReleaseDC(g_hWnd, m_hDC);
	

}
