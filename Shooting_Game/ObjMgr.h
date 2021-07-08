#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(CObj* _pObj, OBJID::ID _eID) { m_listObj[_eID].emplace_back(_pObj); }
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Delete_ID(OBJID::ID _eID);

public:
	CObj* Get_Player() { return m_listObj[OBJID::PLAYER].front(); }
	list<CObj*>&	Get_List(OBJID::ID  _eID) { return m_listObj[_eID]; }

public:
	static CObjMgr* Get_Instance()
	{
		if(!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CObjMgr*		m_pInstance;

	list<CObj*>			m_listObj[OBJID::END];
	
};


#endif // !__OBJMGR_H__
