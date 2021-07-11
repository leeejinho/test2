#include "stdafx.h"
#include "DeadEffect.h"


CDeadEffect::CDeadEffect()
	:dwTime(0)
{
}


CDeadEffect::~CDeadEffect()
{
}

HRESULT CDeadEffect::Initialize()
{
	dwTime = GetTickCount();
	
	m_tInfo.vPos = m_pTarget->Get_Pos();
	m_tInfo.vSize = { 5.f, 5.f, 0.f };

	m_fSpeed = 1.f;
	m_fAngle =(float)(rand() % 360);

	return S_OK;
}

int CDeadEffect::Update()
{
	if(m_bDead)
		return OBJ_DEAD;

	if (dwTime + 1000 < GetTickCount())
		m_bDead = true;

	m_tInfo.vSize.x += 0.1f;
	m_tInfo.vSize.y += 0.1f;

	m_tInfo.vPos.x -= sinf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y += cosf(m_fAngle) * m_fSpeed;

	return OBJ_NOEVENT;
}

void CDeadEffect::Late_Update()
{
}

void CDeadEffect::Render(HDC _DC)
{
	RECT rc{};
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y * 0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y * 0.5f));

	Ellipse(_DC, rc.left, rc.top, rc.right, rc.bottom);
}

void CDeadEffect::Release()
{
}
