#pragma once
#include "Graphic_Device.h"
#include "LevelMgr.h"
#include "TimerMgr.h"

BEGIN(Engine)
class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	HRESULT Initialze_Engine(_uint iNumLevel, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut); // 엔진사용을 위한 초기화
	void Tick_Engine(_float fTmDelta);
	HRESULT Render_Engine();
	HRESULT Clear_Container(_uint iLevelIdx);

public:
	void Render_Begin();
	void Render_End();

public:
	_float Get_TmDelta(const _tchar* pTmTag);
	HRESULT Add_Timer(const _tchar* pTmTag);
	void Update_Timer(const _tchar* pTmTag);
	// levelmgr
public:
	HRESULT Open_Level(_uint iCurrentLevelIdx, class CLevel* pNextLevel);

private:
	CGraphic_Device*	m_pGraphic_Device = nullptr;
	CLevelMgr*	m_pLevel_Mgr = nullptr;
	CTimerMgr*	m_pTimer_Mgr = nullptr;
};

END