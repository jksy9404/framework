#include "..\Public\Level.h"

CLevel::CLevel(LPDIRECT3DDEVICE9 pGraphicDevice)
	:m_pGraphic_Device(pGraphicDevice)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CLevel::NativeConstruct()
{
	return S_OK;
}

void CLevel::Tick(float fDeltaTm)
{
}

void CLevel::LateTick(float fDeltaTm)
{
}

HRESULT CLevel::Render()
{
	return S_OK;
}

void CLevel::Free()
{
	Safe_Release(m_pGraphic_Device);
}
