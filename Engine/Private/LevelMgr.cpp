#include "..\Public\LevelMgr.h"
#include "Level.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CLevelMgr);

CLevelMgr::CLevelMgr()
{
}

HRESULT CLevelMgr::Change_Level(_uint iCurrentIdx, CLevel * pNextLevel)
{
	if (pNextLevel == nullptr)
		return E_FAIL;

	Safe_Release(m_iCurrentLevel);
	m_iCurrentLevel = pNextLevel;
	m_iCurrentLevelIdx = iCurrentIdx;

	return S_OK;
}

HRESULT CLevelMgr::Tick(_float fDeltaTm)
{
	if (m_iCurrentLevel == nullptr)
		return E_FAIL;
	m_iCurrentLevel->Tick(fDeltaTm);

	return S_OK;
}

HRESULT CLevelMgr::LateTick(_float fDeltaTm)
{
	if (nullptr == m_iCurrentLevel)
		return E_FAIL;

	m_iCurrentLevel->LateTick(fDeltaTm);
	return S_OK;
}

void CLevelMgr::Free()
{
	Safe_Release(m_iCurrentLevel);
}
