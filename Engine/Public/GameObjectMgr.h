#pragma once
#include "Base.h"

BEGIN(Engine)
class CGameObjectMgr final : public CBase
{
	DECLARE_SINGLETON(CGameObjectMgr);
private:
	CGameObjectMgr();
	virtual ~CGameObjectMgr() = default;

public:
	HRESULT Reserve_Container(_uint iNumLv);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pGameObj); // 원형추가
	HRESULT Clone_GameObject(_uint iLvIdx, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg); // 사본생성후 layer에 추가

public:
	void Tick(_float fTmDelta);
	void Late(_float fTmDelta);

public:
	HRESULT Clear(_uint iLvIdx);

private:
	map<const _tchar*, class CGameObject*>		m_Prototypes;
	typedef map<const _tchar*, class CGameObject*> PROTOTYPES;

	map<const _tchar*, class CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*>	LAYERS;

	_uint  m_iNumLv = 0;
private:
	class CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	class CLayer* Find_Layer(_uint iLvIdx, const _tchar* pLayerTag);
	
public:
	virtual void Free() override;
};

END