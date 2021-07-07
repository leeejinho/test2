#include "stdafx.h"
#include "Butterfly.h"


CButterfly::CButterfly()
	:m_eCurState(END), m_bDiagonal(true), m_bRotation(true), m_fParentX(0.f), m_fParentY(0.f)
{
}


CButterfly::~CButterfly()
{
	Release();
}

HRESULT CButterfly::Initialize()
{
	m_tInfo.vPos = { 0.f, 500.f, 0.f };
	m_tInfo.vDir = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(40.f, 40.f, 0.f);

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };


	m_fSpeed = 2.f;

	return S_OK;
}

int CButterfly::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState == LEFT)
		Create_Butterfly_Left();
	if (m_eCurState == RIGHT)
		Create_Butterfly_Right();

	return OBJ_NOEVENT;
}

void CButterfly::Late_Update()
{
}

void CButterfly::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);

}

void CButterfly::Release()
{
}

int CButterfly::Create_Butterfly_Right()
{
	int iCount = 0;
	return 0;
}

int CButterfly::Create_Butterfly_Left()
{
	D3DXMATRIX matParentTrans;

	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	if (m_bDiagonal)				// 대각선
	{
		m_fAngle = 45.f;
		matWorld = matRotZ * matTrans;
		m_tInfo.vPos.x += m_fSpeed;
 		m_tInfo.vPos.y -= m_fSpeed;
	}
	if (m_tInfo.vPos.x >= 150.f && m_tInfo.vPos.y <= 350.f)
	{
		m_bDiagonal = false;
		m_fAngle = 180.f;
	}
	if (!m_bDiagonal)
	{
		D3DXMatrixTranslation(&matParentTrans, m_fParentX, m_fParentY, 0.f);

		if (m_bRotation)				// 회전
		{
			m_fParentX = 100.f;
			m_fParentY = 350.f;
			m_tInfo.vPos = { -50.f, 0.f, 0.f };
			matWorld = matTrans * matRelRotZ * matParentTrans;
			if (m_fAngle > -180.f)
				m_fAngle -= m_fSpeed;
			else
			{
				m_bRotation = false;
				m_tInfo.vPos = { 50.f, 0.f, 0.f };
			}
		}
		else					// 회전후 올라감
		{
			m_tInfo.vPos = { 50.f, 0.f, 0.f };
			matWorld = matTrans * matParentTrans;
			if (m_fParentY >= 50.f)
				m_fParentY -= m_fSpeed;
		}
	}

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

	return 0;
}
