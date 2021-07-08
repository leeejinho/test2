#pragma once
#include "Obj.h"
class CCircle_Monster :
	public CObj
{
public:
	CCircle_Monster();
	virtual ~CCircle_Monster();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


public:
	void		Set_Left() { m_bLeft = true; }

private:
	bool	m_bSavePos;
	int		RotateCnt;
	bool	m_bLeft;

private:
	void myPattern();
};

