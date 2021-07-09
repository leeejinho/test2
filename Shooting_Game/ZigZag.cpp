#include "stdafx.h"
#include "ZigZag.h"


CZigZag::CZigZag()
	:m_PatternNum(0), m_bLeft(false)
{
}


CZigZag::~CZigZag()
{
}

HRESULT CZigZag::Initialize()
{
	if (m_bLeft)
	{
		m_tInfo.vPos = { 300.f, 0.f, 0.f };
		m_tInfo.vSize = D3DXVECTOR3(25.f, 25.f, 0.f);

		m_ChangePos[0] = D3DXVECTOR3{ 30.f, 50.f, 0.f };
		m_ChangePos[1] = D3DXVECTOR3{ WINCX - 30.f, WINCY - 150.f, 0.f };
	}

	else if (!m_bLeft)
	{
		m_tInfo.vPos = { 500.f, 0.f, 0.f };
		m_tInfo.vSize = D3DXVECTOR3(25.f, 25.f, 0.f);

		m_ChangePos[0] = D3DXVECTOR3{ WINCX - 30.f , 50, 0.f };
		m_ChangePos[1] = D3DXVECTOR3{ 30.f, WINCY - 150.f, 0.f };
	}

	m_vP[4] = { 0.f, 0.f, 0.f };
	m_fSpeed = 5.f;

	return S_OK;
}

int CZigZag::Update()
{
	if (m_bDead)
	{
		Play_Dead_Effect(this);
		return OBJ_DEAD;
	}

	myPattern();

	return OBJ_NOEVENT;

}

void CZigZag::Late_Update()
{
}

void CZigZag::Render(HDC _DC)
{
	RECT rc{};
	rc.left =	LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	rc.top =	LONG(m_tInfo.vPos.y - (m_tInfo.vSize.x * 0.5f));
	rc.right =	LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.x * 0.5f));

	Rectangle(_DC, rc.left, rc.top, rc.right, rc.bottom);

}

void CZigZag::Release()
{
}

void CZigZag::myPattern()
{
	float fDist = 0;
	switch (m_PatternNum)
	{
	case 0:
		m_tInfo.vPos.y += m_fSpeed;
		if (m_tInfo.vPos.y >= 50.f)
		{
			m_tInfo.vPos.y = 50.f;
			++m_PatternNum;
		}
		break;

	case 1:
		if (m_bLeft)
		{
			m_tInfo.vPos.x -= m_fSpeed;
			if (m_tInfo.vPos.x <= m_ChangePos[0].x)
			{
				m_tInfo.vPos.x = m_ChangePos[0].x;
				++m_PatternNum;
			}
		}

		else
		{
			m_tInfo.vPos.x += m_fSpeed;
			if (m_tInfo.vPos.x >= m_ChangePos[0].x)
			{
				m_tInfo.vPos.x = m_ChangePos[0].x;
				++m_PatternNum;
			}
		}
		break;
	case 2:
		m_tInfo.vDir = m_ChangePos[1] - m_tInfo.vPos;
		fDist = D3DXVec3Length(&m_tInfo.vDir);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		if (fDist < 5.f)
		{
			m_tInfo.vPos = m_ChangePos[1];
			++m_PatternNum;
		}
		break;
	case 3:
		if (m_bLeft)
		{
			m_tInfo.vPos.x -= m_fSpeed;
			if (m_tInfo.vPos.x <= -300.f)
				m_bDead = true;
		}
		else
		{
			m_tInfo.vPos.x += m_fSpeed;
			if (m_tInfo.vPos.x >= WINCX + 300.f)
				m_bDead = true;
		}
		break;

	}
}
