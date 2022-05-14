#include "..\Public\GameObjectMgr.h"
#include "Layer.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CGameObjectMgr)
CGameObjectMgr::CGameObjectMgr()
{
}

HRESULT CGameObjectMgr::Reserve_Container(_uint iNumLv)
{
	if (nullptr != m_pLayers)
		return E_FAIL;

	m_pLayers = new LAYERS[iNumLv];
	m_iNumLv = iNumLv;
	return S_OK;
}

HRESULT CGameObjectMgr::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pGameObj)
{
	if (nullptr != Find_Prototype(pPrototypeTag))
		return E_FAIL;

	m_Prototypes.emplace(pPrototypeTag, pGameObj);
	return S_OK;
}

HRESULT CGameObjectMgr::Clone_GameObject(_uint iLvIdx, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (iLvIdx >= m_iNumLv || nullptr == m_pLayers)
		return E_FAIL;

	CGameObject* pPrototype = Find_Prototype(pPrototypeTag);
	if (nullptr == pPrototype)
		return E_FAIL;

	CGameObject* pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject)
		return E_FAIL;

	CLayer* pLayer = Find_Layer(iLvIdx,pLayerTag);

	if (nullptr == pLayer) {
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;
		if (FAILED(pLayer->Add_GameObj(pGameObject)))
			return E_FAIL;
		m_pLayers[iLvIdx].emplace(pLayerTag, pLayer);
	}
	else
		pLayer->Add_GameObj(pGameObject);
	return S_OK;
}

void CGameObjectMgr::Tick(_float fTmDelta)
{
	for (_uint i = 0; i < m_iNumLv; ++i) {
		for (auto& Pair : m_pLayers[i]) {
			if (nullptr != Pair.second)
				Pair.second->Tick(fTmDelta);
		}			
	}
}

void CGameObjectMgr::Late(_float fTmDelta)
{
	for (_uint i = 0; i < m_iNumLv; ++i) {
		for (auto& Pair : m_pLayers[i]) {
			if (nullptr != Pair.second)
				Pair.second->LateTick(fTmDelta);
		}
	}
}

HRESULT CGameObjectMgr::Clear(_uint iLvIdx)
{
	for (auto& Pair : m_pLayers[iLvIdx])
		Safe_Release(Pair.second);
	
	m_pLayers[iLvIdx].clear();

	return S_OK;
}

CGameObject * CGameObjectMgr::Find_Prototype(const _tchar * pPrototypeTag)
{
	auto iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder(pPrototypeTag));
	if(iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer * CGameObjectMgr::Find_Layer(_uint iLvIdx, const _tchar * pLayerTag)
{
	auto iter = find_if(m_pLayers[iLvIdx].begin(), m_pLayers[iLvIdx].end(), CTag_Finder(pLayerTag));
	if(iter == m_pLayers[iLvIdx].end())
		return nullptr;
	return iter->second;
}

void CGameObjectMgr::Free()
{
	for (_uint i = 0; i < m_iNumLv; i++) {
		for (auto& Pair : m_pLayers[i])
			Safe_Release(Pair.second);

		m_pLayers[i].clear();
	}

	Safe_Delete_Array(m_pLayers);

	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();
}
