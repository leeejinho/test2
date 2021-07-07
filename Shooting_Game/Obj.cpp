#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_fSpeed(0.f)
	, m_fAngle(0.f), m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(m_vP, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(m_vQ, sizeof(D3DXVECTOR3) * 4);
	
}


CObj::~CObj()
{
}
