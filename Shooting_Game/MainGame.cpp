#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "Player.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER);

	CObj* pObj = CAbstractFactory<CMonster>::Create();
	static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);

	pObj = CAbstractFactory<CMonster>::Create();
	static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);

	CObjMgr::Get_Instance();
}

void CMainGame::Update()
{
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
