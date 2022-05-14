#include "..\Public\GameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance);

CGameInstance::CGameInstance()
	:m_pLevel_Mgr(CLevelMgr::Get_Instance())
	,m_pGraphic_Device(CGraphic_Device::Get_Instance())
	,m_pTimer_Mgr(CTimerMgr::Get_Instance())
{
	Safe_AddRef(m_pLevel_Mgr);
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pTimer_Mgr);
}

HRESULT CGameInstance::Initialze_Engine(_uint iNumLevel, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;


	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTmDelta)
{
	if (nullptr == m_pLevel_Mgr)
		return;

	m_pLevel_Mgr->Tick(fTmDelta);
}

HRESULT CGameInstance::Render_Engine()
{
	return S_OK;
}

HRESULT CGameInstance::Clear_Container(_uint iLevelIdx)
{
	return S_OK;
}

void CGameInstance::Render_Begin()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_End();
}

_float CGameInstance::Get_TmDelta(const _tchar * pTmTag)
{
	if (nullptr == m_pTimer_Mgr)
		return E_FAIL;

	return m_pTimer_Mgr->Get_TimeDelta(pTmTag);
}

HRESULT CGameInstance::Add_Timer(const _tchar * pTmTag)
{
	if (nullptr == m_pTimer_Mgr)
		return E_FAIL;

	return m_pTimer_Mgr->Add_Timer(pTmTag);
}

void CGameInstance::Update_Timer(const _tchar * pTmTag)
{
	if (nullptr == m_pTimer_Mgr)
		return;

	m_pTimer_Mgr->Update(pTmTag);
}

HRESULT CGameInstance::Open_Level(_uint iCurrentLevelIdx, CLevel * pNextLevel)
{
	if (nullptr == m_pLevel_Mgr)
		return E_FAIL;

	return m_pLevel_Mgr->Change_Level(iCurrentLevelIdx, pNextLevel);
}
