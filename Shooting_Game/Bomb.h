#pragma once
#include "Obj.h"
#ifndef __SHIELD_H__
#define __SHIELD_H__


class CPlayer;
class CBomb :
	public CObj
{
public:
	CBomb();
	virtual ~CBomb();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


public:
	void Set_Player(CObj* m_pPlayer) { myTarget = m_pPlayer; }

private:
	void Effect();

private:
	bool ChangeEffect;
	int		Effect_Cnt;
	CObj*	myTarget;
	DWORD	dwTime;
};

#endif //__SHIELD_H__
