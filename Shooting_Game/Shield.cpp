#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
	:myTarget(nullptr), dwTime(0), ChangeEffect(false)
{
}


CShield::~CShield()
{
}

HRESULT CShield::Initialize()
{
	m_fSpeed = 2.f;
	m_tInfo.vSize = { 80.f, 80.f, 0.f };
	dwTime = GetTickCount();
	return S_OK;
}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Effect();
	if (dwTime + 8000 < GetTickCount())
		m_bDead = true;

	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
	m_tInfo.vPos = myTarget->Get_INFO().vPos;
}

void CShield::Render(HDC _DC)
{
	Ellipse(_DC, int(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f), int(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f), int(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f));
}

void CShield::Release()
{
}

void CShield::Effect()
{
	m_fSpeed += 0.02f;

	if (m_fSpeed > 2.f)
		m_fSpeed = 2.f;


	if (m_tInfo.vSize.x > 120.f)
		ChangeEffect = true;
	else if (m_tInfo.vSize.x < 80.f)
		ChangeEffect = false;

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
