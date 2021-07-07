#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__

class CObj abstract
{
public:
	explicit CObj();
	virtual ~CObj();

public:
	virtual HRESULT Initialize()PURE;
	virtual int Update()		PURE;
	virtual void Late_Update()	PURE;
	virtual void Render(HDC _DC)PURE;
	virtual void Release()		PURE;

public:
	const INFO	Get_Info()	const { return m_tInfo; }

public:
	void Set_Dead() { m_bDead = true; }

protected:
	INFO	m_tInfo;
	bool	m_bDead;

	float		m_fSpeed;
	D3DXVECTOR3 m_vQ[4];
	D3DXVECTOR3 m_vP[4];
	float		m_fAngle;
};

#endif // !__OBJ_H__
