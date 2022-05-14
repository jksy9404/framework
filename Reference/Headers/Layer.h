#pragma once
#include "Base.h"

BEGIN(Engine)
class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObj(class CGameObject* pGameObj);

public:
	HRESULT NativeConstruct();
	void Tick(_float fTmDelta);
	void LateTick(_float fTmDelta);

private:
	list<class CGameObject*> m_ObjectList;
	typedef list<class CGameObject*> OBJECTS;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END