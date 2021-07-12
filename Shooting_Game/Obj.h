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
	virtual int Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC _DC)PURE;
	virtual void Release()PURE;

public:
	INFO Get_Info() { return m_tInfo; }
	D3DXVECTOR3 Get_Pos() { return m_vQ[4]; }

public:
	void Set_Pos(float _fX, float _fY) { m_tInfo.vPos.x = _fX; m_tInfo.vPos.y = _fY; }
	void Set_Dead() { m_bDead = true; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	void Play_Dead_Effect(CObj* pObj);

	void CheckPos_Dead();

private:
	int		Dead_Effect_Cnt;

protected:
	INFO		m_tInfo;
	bool		m_bDead;
	float		m_fSpeed;
	D3DXVECTOR3 m_vQ[5];
	D3DXVECTOR3 m_vP[5];
	float		m_fAngle;

	CObj*		m_pTarget;

};

#endif // !__OBJ_H__
