#include "stdafx.h"
#include "Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loding.h"

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Logo::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	
	return S_OK;
}

void CLevel_Logo::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CLevel_Logo::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);

	if (GetKeyState(VK_RETURN) < 0) {
		CGameInstance* pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);
		 
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY))))
			return;

		Safe_Release(pGameInstance);
	}
	SetWindowText(g_hWnd, TEXT("로고레벨"));
}

HRESULT CLevel_Logo::Render()
{

	return S_OK;
}

CLevel_Logo * CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX("Failed to Create : CLevel_Logo");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}
