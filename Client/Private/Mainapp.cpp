#include "stdafx.h"
#include "..\Public\Mainapp.h"


CMainapp::CMainapp()
{
}

HRESULT CMainapp::NativeConstruct()
{
	return S_OK;
}

void CMainapp::Tick(float fDeltaTm)
{
}

HRESULT CMainapp::Render()
{
	return S_OK;
}

CMainapp * CMainapp::Create()
{
	CMainapp* pInstance = new CMainapp;
	if (FAILED(pInstance->NativeConstruct())) {
		
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainapp::Free()
{
	__super::Free();

}