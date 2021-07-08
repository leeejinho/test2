#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Monster.h"

#include "Butterfly.h"
=======
#include "Player.h"


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

	/*CObj* pObj = CAbstractFactory<CMonster>::Create();
	static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);

	pObj = CAbstractFactory<CMonster>::Create();
	static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);*/

	//if (m_dwTime + 100 < GetTickCount())
	//{
	//	CObj* pObj = CAbstractFactory<CButterfly>::Create();
	//	static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
	//	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);


	//	pObj = CAbstractFactory<CButterfly>::Create();
	//	static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
	//	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);
	//	m_dwTime = GetTickCount();
	//}
=======
	pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::PLAYER);



	CObjMgr::Get_Instance();
}

void CMainGame::Update()
{
	static int iCount = 0;

	if (iCount < 6)
	{
		if (m_dwTime + 500 < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CButterfly>::Create();
			static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);

			pObj = CAbstractFactory<CButterfly>::Create();
			static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);

			++iCount;

			m_dwTime = GetTickCount();
		}

	}
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
