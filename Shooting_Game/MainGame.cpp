#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Monster.h"

#include "Butterfly.h"
#include "Player.h"
#include "StageMgr.h"

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
	static int iCount = 0;

	if (iCount < 12)
	{
		if (m_dwTime + 500 < GetTickCount())
		{

			int x = rand() % X;
			int y = rand() % Y;

		/*	if (!CStageMgr::Get_Instance()->Check_Monster(x, y))
			{
				CObj* pObj = CAbstractFactory<CButterfly>::Create();
				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
				static_cast<CButterfly*>(pObj)->Set_TargetPos(CStageMgr::Get_Instance()->GetVec(x, y));
				CStageMgr::Get_Instance()->Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);
				++iCount;
			}

			x = rand() % X;
			y = rand() % Y;
			if (!CStageMgr::Get_Instance()->Check_Monster(x, y))
			{
				CObj* pObj = CAbstractFactory<CButterfly>::Create();
				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
				static_cast<CButterfly*>(pObj)->Set_TargetPos(CStageMgr::Get_Instance()->GetVec(x, y));
				CStageMgr::Get_Instance()->Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::BUTTERFLY);
				++iCount;
			}

			 x = rand() % X;
			 y = rand() % Y;*/

			if (!CStageMgr::Get_Instance()->Check_Monster(x, y))
			{
				CObj* pObj = CAbstractFactory<CMonster>::Create();
				static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
				static_cast<CMonster*>(pObj)->Set_TargetPos(CStageMgr::Get_Instance()->GetVec(x, y));
				CStageMgr::Get_Instance()->Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++iCount;
			}

			x = rand() % X;
			 y = rand() % Y;

			if (!CStageMgr::Get_Instance()->Check_Monster(x, y))
			{
				CObj* pObj = CAbstractFactory<CMonster>::Create();
				static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
				static_cast<CMonster*>(pObj)->Set_TargetPos(CStageMgr::Get_Instance()->GetVec(x, y));
				CStageMgr::Get_Instance()->Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++iCount;
			}
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
