#pragma once
#include "Obj.h"

class CPlayer;
class CShield :
	public CObj
{
public:
	CShield();
	virtual ~CShield();

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
	CObj*	myTarget;
	DWORD	dwTime;
};

