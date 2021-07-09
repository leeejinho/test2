#include "stdafx.h"
#include "Bomb.h"


CBomb::CBomb()
	:myTarget(nullptr), dwTime(0), ChangeEffect(false)
	,Effect_Cnt(0)
{
}


CBomb::~CBomb()
{
}

HRESULT CBomb::Initialize()
{
	m_fSpeed = 4.f;
	m_tInfo.vSize = { 80.f, 80.f, 0.f };
	dwTime = GetTickCount();
	return S_OK;
}

int CBomb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Effect();
	
	if (Effect_Cnt == 1)
	{
		m_bDead = true;
	}

	return OBJ_NOEVENT;
}

void CBomb::Late_Update()
{
	m_tInfo.vPos = myTarget->Get_Info().vPos;
}

void CBomb::Render(HDC _DC)
{
	Ellipse(_DC, int(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f), int(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f), int(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f));
}

void CBomb::Release()
{
}

void CBomb::Effect()
{
	if (m_tInfo.vSize.x > 300.f)
		ChangeEffect = true;
	else if (m_tInfo.vSize.x < 80.f)
	{
		Effect_Cnt = 1;
		ChangeEffect = false;
	}

	if (ChangeEffect)
	{
		m_tInfo.vSize.x -= m_fSpeed;
		m_tInfo.vSize.y -= m_fSpeed;
	}
	else if(!ChangeEffect)
	{
		m_tInfo.vSize.x += m_fSpeed;
		m_tInfo.vSize.y += m_fSpeed;
	}

	

}
