#include "stdafx.h"
#include "Level_Loding.h"
#include "Level_Loader.h"
#include "GameInstance.h"
#include "Level_Logo.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Loading::NativeConstruct(LEVEL eLevel)
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	m_eNextLevel = eLevel;

	m_pLoader = CLevel_Loader::Create(m_pGraphic_Device, m_eNextLevel);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CLevel_Loading::LateTick(_float fTmDelta)
{
	if (false == m_pLoader->isFinishing())
		OutputDebugString(m_pLoader->Get_LoadingText());

	if (m_pLoader->isFinishing()) {
		if (GetKeyState(VK_RETURN) & 0x8000) {
			CGameInstance* pGameInstance = CGameInstance::Get_Instance();
			Safe_AddRef(pGameInstance);

			CLevel* pLevel = nullptr;
			
			switch (m_eNextLevel) {
			case LEVEL_LOGO:
				pLevel = CLevel_Logo::Create(m_pGraphic_Device);
				break;
			case LEVEL_GAMEPLAY:
				pLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
				break;
			}

			if (nullptr == pLevel)
				return;

			if (FAILED(pGameInstance->Open_Level(m_eNextLevel, pLevel))) 
				return;
			
			Safe_Release(pGameInstance);

		}
	}

}

HRESULT CLevel_Loading::Render()
{
	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLv)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct(eLv))) {
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();
	Safe_Release(m_pLoader);
}
