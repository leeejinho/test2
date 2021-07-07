#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * _Dst, CObj * _Src)
{
	float fX = abs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
	float fY = abs(_Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y);
	float fDia = sqrtf(fX * fX + fY * fY);

	float fDis = ((_Dst->Get_Info().vSize.x + _Src->Get_Info().vSize.x) * 0.5f);
	
	if(fDis > fDia)
		return true;
	return false;
}
