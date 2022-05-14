#include "..\Public\Layer.h"
#include "GameObject.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObj(CGameObject * pGameObj)
{
	m_ObjectList.push_back(pGameObj);
	return S_OK;
}

HRESULT CLayer::NativeConstruct()
{

	return S_OK;
}

void CLayer::Tick(_float fTmDelta)
{
	for (auto& pGameObj : m_ObjectList) {
		if (nullptr != pGameObj)
			pGameObj->Tick(fTmDelta);
	}
}

void CLayer::LateTick(_float fTmDelta)
{
	for (auto& pGameObj : m_ObjectList) {
		if (nullptr != pGameObj)
			pGameObj->LateTick(fTmDelta);
	}
}

CLayer * CLayer::Create()
{
	CLayer* pInstance = new CLayer();
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX("Failed to Created : CLayer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObj : m_ObjectList)
		Safe_Release(pGameObj);

	m_ObjectList.clear();
}
