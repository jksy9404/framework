#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"


CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CLevel_GamePlay::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);
	SetWindowText(g_hWnd, TEXT("게임플레이레벨"));
}

HRESULT CLevel_GamePlay::Render()
{
	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_GamePlay* pInstance = new CLevel_GamePlay(pGraphic_Device);
	if(FAILED(pInstance->NativeConstruct()))
		return nullptr;
	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();
}
