#pragma once

#include "Clinet_Define.h"
#include "Base.h"

BEGIN(Client)
class CLevel_Loader final : public CBase
{
private:
	CLevel_Loader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loader() = default;

public:
	LEVEL Get_NextLevelID()					{ return m_eNextLevel; }
	CRITICAL_SECTION* Get_CriticalSection() { return &m_CriticalSection; }
	const _tchar* Get_LoadingText()			{ return m_szLoading; }
	_bool isFinishing()						{ return m_isFinished; }

public:
	HRESULT NativeConstruct(LEVEL eLevel);

public:
	HRESULT Loading_ForLogoLevel();
	HRESULT Loading_ForGamePlayLevel();

public:
	static CLevel_Loader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLv);
	virtual void Free() override;

private:
	LEVEL				m_eNextLevel = LEVEL_END;
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	_bool				m_isFinished = false;
	_tchar				m_szLoading[MAX_PATH] = TEXT("");

private:
	HANDLE				m_hThread = 0;
	CRITICAL_SECTION	m_CriticalSection;

};

END