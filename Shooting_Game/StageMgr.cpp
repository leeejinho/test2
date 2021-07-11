#include "stdafx.h"
#include "StageMgr.h"
#include "Butterfly.h"
#include "ZigZag.h"
#include "ObjMgr.h"
#include "Circle_Monster.h"
#include "Monster.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;
CStageMgr::CStageMgr()
	:m_MonsterCnt{ 0 }, m_bClear(true), m_dwTime{ 0 }, m_eCurStage(0), m_fStage(0.f)

{
	ZeroMemory(myStage, sizeof(D3DXVECTOR3) * (X*Y));
	ZeroMemory(m_bMonster, sizeof(bool) * (X*Y));
}


CStageMgr::~CStageMgr()
{
}

void CStageMgr::Initialize()
{
	for (int i = 0; i < X; ++i)
	{
		for (int j = 0; j < Y; ++j)
		{
			myStage[i][j].x = i * 50.f + 100.f;
			myStage[i][j].y = j * 50.f + 50.f;
			myStage[i][j].z = 0;
		}
	}

	m_eCurStage = -1;
	m_bClear = true;


}

void CStageMgr::Update()
{
	Check_Clear();
	Start_Stage();
}

void CStageMgr::Start_Stage()
{
	if (m_bClear)
	{
		// debug
		//m_eCurStage = 4;

		m_eCurStage = rand() % 4;
		m_bClear = false;
		m_fStage += 0.5f;
	}

	switch (m_eCurStage)
	{
	case 0:
		Spawn_ButterFly_Left(6, 500);
		Spawn_ButterFly_Right(6, 500);
		Spawn_Circle_Monster(5, 300, 300.f);
		break;
	case 1:
		Spawn_ZigZag_Left(4, 250);
		Spawn_ButterFly_Right(12, 500);
		break;
	case 2:
		Spawn_ZigZag_Right(4, 250);
		Spawn_ButterFly_Left(12, 500);
		break;
	case 3:
		Spawn_Monster_Left(10, 500);
		Spawn_Monster_Right(10, 500);
		break;
	case 4:
		Spawn_Circle_Monster(5, 300, 300.f);
		break;
	default:
		break;
	}
}

void CStageMgr::Spawn_ButterFly_Left(int _Cnt, int _delay)		// delay 500 ±ÇÀå
{
	if (m_MonsterCnt[BUTTERFLY_LEFT] < _Cnt)
	{
		if (m_dwTime[BUTTERFLY_LEFT] + _delay < GetTickCount())
		{
			int x = 0;
			int y = 0;
			bool Check = false;
			for (int i = 0; i < 30; ++i)
			{
				x = rand() % X;
				y = rand() % Y;

				if (!Check_Monster(x, y))
				{
					Check = true;
					break;
				}
			}

			if (Check)
			{
				CObj* pObj = CAbstractFactory<CButterfly>::Create();
				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::LEFT);
				static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
				Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++m_MonsterCnt[BUTTERFLY_LEFT];
			}
			m_dwTime[BUTTERFLY_LEFT] = GetTickCount();
		}
	}
}

void CStageMgr::Spawn_ButterFly_Right(int _Cnt, int _delay)
{


	if (m_MonsterCnt[BUTTERFLY_RIGHT] < _Cnt)
	{
		if (m_dwTime[BUTTERFLY_RIGHT] + _delay < GetTickCount())
		{
			int x = 0;
			int y = 0;
			bool Check = false;
			for (int i = 0; i < 30; ++i)
			{
				x = rand() % X;
				y = rand() % Y;

				if (!Check_Monster(x, y))
				{
					Check = true;
					break;
				}
			}

			if (Check)
			{
				CObj* pObj = CAbstractFactory<CButterfly>::Create();
				static_cast<CButterfly*>(pObj)->Set_State(CButterfly::RIGHT);
				static_cast<CButterfly*>(pObj)->Set_TargetPos(GetVec(x, y));
				Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++m_MonsterCnt[BUTTERFLY_RIGHT];
			}

			m_dwTime[BUTTERFLY_RIGHT] = GetTickCount();
		}
	}

}

void CStageMgr::Spawn_ZigZag_Left(int _Cnt, int _delay)
{

	if (m_MonsterCnt[ZIGZAG_LEFT] < _Cnt)
	{
		if (m_dwTime[ZIGZAG_LEFT] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CZigZag>::Create_UnIntialize();
			static_cast<CZigZag*>(pObj)->Set_Left();
			pObj->Initialize();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[ZIGZAG_LEFT] = GetTickCount();

			++m_MonsterCnt[ZIGZAG_LEFT];
		}
	}
}

void CStageMgr::Spawn_ZigZag_Right(int _Cnt, int _delay)
{

	if (m_MonsterCnt[ZIGZAG_RIGHT] < _Cnt)
	{
		if (m_dwTime[ZIGZAG_RIGHT] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CZigZag>::Create_UnIntialize();
			pObj->Initialize();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[ZIGZAG_RIGHT] = GetTickCount();

			++m_MonsterCnt[ZIGZAG_RIGHT];
		}
	}
}

void CStageMgr::Spawn_Circle_Monster(int _Cnt, int _delay, float fX)
{

	if (m_MonsterCnt[CIRCLE_MONSTER] < _Cnt)
	{
		if (m_dwTime[CIRCLE_MONSTER] + _delay < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CCircle_Monster>::Create(300.f, 0.f);
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);

			pObj = CAbstractFactory<CCircle_Monster>::Create(300.f, 0.f);
			static_cast<CCircle_Monster*>(pObj)->Set_Left();
			CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
			m_dwTime[CIRCLE_MONSTER] = GetTickCount();

			++m_MonsterCnt[CIRCLE_MONSTER];
		}
	}
}

void CStageMgr::Spawn_Monster_Left(int _Cnt, int _delay)
{

	if (m_MonsterCnt[MONSTER_LEFT] < _Cnt)
	{
		if (m_dwTime[MONSTER_LEFT] + _delay < GetTickCount())
		{

			int x = 0;
			int y = 0;
			bool Check = false;
			for (int i = 0; i < 30; ++i)
			{
				x = rand() % X;
				y = rand() % Y;

				if (!Check_Monster(x, y))
				{
					Check = true;
					break;
				}
			}

			if(Check)
			{
				CObj* pObj = CAbstractFactory<CMonster>::Create();
				static_cast<CMonster*>(pObj)->Set_State(CMonster::LEFT);
				static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
				Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++m_MonsterCnt[MONSTER_LEFT];
			}
			m_dwTime[MONSTER_LEFT] = GetTickCount();
		}
	}
}

void CStageMgr::Spawn_Monster_Right(int _Cnt, int _delay)
{
	if (m_MonsterCnt[MONSTER_RIGHT] < _Cnt)
	{
		if (m_dwTime[MONSTER_RIGHT] + _delay < GetTickCount())
		{
			int x = 0;
			int y = 0;
			bool Check = false;
			for (int i = 0; i < 30; ++i)
			{
				 x = rand() % X;
				 y = rand() % Y;

				 if (!Check_Monster(x, y))
				 {
					 Check = true;
					 break;
				 }
			}

			if (Check)
			{
				CObj* pObj = CAbstractFactory<CMonster>::Create();
				static_cast<CMonster*>(pObj)->Set_State(CMonster::RIGHT);
				static_cast<CMonster*>(pObj)->Set_TargetPos(GetVec(x, y));
				Set_Check(x, y);
				CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::MONSTER);
				++m_MonsterCnt[MONSTER_RIGHT];

				m_dwTime[MONSTER_RIGHT] = GetTickCount();
			}
		}
	}
}


void CStageMgr::Check_Clear()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER).size() < 1)
	{
		m_bClear = true;
		m_eCurStage = -1;

		for (int i = 0; i < MONSTER_END; ++i)
		{
			m_MonsterCnt[i] = 0;
		}
		for (int i = 0; i < Y; ++i)
		{
			for (int j = 0; j < X; ++j)
			{
				m_bMonster[i][j] = false;
			}
		}
	}
}

bool CStageMgr::Check_Monster(int x, int y)
{
	if (m_bMonster[x][y])
		return true;

	else return false;
}

