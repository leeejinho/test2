#include "stdafx.h"
#include "Circle_Monster.h"


CCircle_Monster::CCircle_Monster()
	:m_bSavePos(false), RotateCnt(1)
{
}


CCircle_Monster::~CCircle_Monster()
{
}

HRESULT CCircle_Monster::Initialize()
{
	m_tInfo.vSize = D3DXVECTOR3(25.f, 25.f, 0.f);


	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[4] = { 0.f, 0.f, 0.f };

	m_fSpeed = 2.f;
	m_fAngle = 0;
	return S_OK;


}

int CCircle_Monster::Update()
{
	if (m_bDead)
	{
		Play_Dead_Effect(this);
		return OBJ_DEAD;
	}

	myPattern();

	return OBJ_NOEVENT;
}

void CCircle_Monster::Late_Update()
{
}

void CCircle_Monster::Render(HDC _DC)
{
	RECT rc{};
	rc.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	rc.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.x * 0.5f));
	rc.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	rc.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.x * 0.5f));

	Rectangle(_DC, rc.left, rc.top, rc.right, rc.bottom);
}

void CCircle_Monster::Release()
{
}

void CCircle_Monster::myPattern()
{
	D3DXMATRIX matRotZ, matTrans, matRelRotZ, matWorld, matParentTrans;


	if (m_tInfo.vPos.y >= 150.f)
	{
		if (!m_bSavePos)
		{
			m_bSavePos = true;
			m_vP[4] = m_tInfo.vPos;
		}
		if (!m_bLeft)
		{
			m_fAngle += m_fSpeed * 2;
			if (m_fAngle >= 180.f)
			{
				m_fAngle = 0;
				++RotateCnt;
			}
		}
		else
		{
			m_fAngle -= m_fSpeed * 2;
			if (m_fAngle <= -180.f)
			{
				m_fAngle = 0;
				++RotateCnt;
			}
		}
		if(RotateCnt == 1)
			D3DXMatrixTranslation(&matParentTrans, 300.f, 200.f, 0.f);
		else
			D3DXMatrixTranslation(&matParentTrans, 300.f, 100.f + 100.f * RotateCnt, 0.f);	


		D3DXMatrixTranslation(&matTrans, 0, -50.f, 0.f);
		D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));


		matWorld =  matTrans * matRelRotZ * matParentTrans;

		m_vP[4] = D3DXVECTOR3{ matWorld._41, matWorld._42, matWorld._43 };

		m_tInfo.vPos = m_vP[4];

	}
	else
	{
		m_tInfo.vPos.y += m_fSpeed;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		matWorld = matTrans;
	}



	if (matParentTrans._42 >= WINCY + 100.f)
	{
		m_tInfo.vPos.y = WINCY + 100.f;
		m_bDead = true;
	}
}
