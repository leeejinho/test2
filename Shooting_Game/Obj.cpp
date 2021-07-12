#include "stdafx.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "DeadEffect.h"


CObj::CObj()
	:m_fSpeed(0.f)
	, m_fAngle(0.f), m_bDead(false)
	, Dead_Effect_Cnt(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(m_vP, sizeof(D3DXVECTOR3) * 5);
	ZeroMemory(m_vQ, sizeof(D3DXVECTOR3) * 5);
	
}


CObj::~CObj()
{
}

void CObj::Play_Dead_Effect(CObj* pObj)
{
	while (Dead_Effect_Cnt < 30)
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CDeadEffect>::Create(pObj), OBJID::EFFECT);
		++Dead_Effect_Cnt;
	}
}

void CObj::CheckPos_Dead()
{
	if (m_tInfo.vPos.x < -WINCX * 0.5f ||
		m_tInfo.vPos.x > WINCX * 1.5f ||
		m_tInfo.vPos.y < -WINCY * 0.5f ||
		m_tInfo.vPos.y > WINCY * 1.5f)

		m_bDead = true;
}


