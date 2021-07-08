#pragma once
#include "Obj.h"
class CDeadEffect :
	public CObj
{
public:
	CDeadEffect();
	virtual ~CDeadEffect();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;


	
private:
	DWORD	dwTime;
};

