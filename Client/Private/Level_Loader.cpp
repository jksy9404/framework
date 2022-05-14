#include "stdafx.h"
#include "..\Public\Level_Loader.h"
#include "GameInstance.h"

CLevel_Loader::CLevel_Loader(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}


unsigned int APIENTRY ThreadEntryFunc(void *pArg) {
	
	CLevel_Loader* pLoader = (CLevel_Loader*)pArg;

	EnterCriticalSection(pLoader->Get_CriticalSection());
	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}

	LeaveCriticalSection(pLoader->Get_CriticalSection());
	return 0;
}

HRESULT CLevel_Loader::NativeConstruct(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;
	InitializeCriticalSection(&m_CriticalSection);
	//m_hThread = (HANDLE)_beginthreadex()
	return S_OK;
}

HRESULT CLevel_Loader::Loading_ForLogoLevel()
{
	wsprintf(m_szLoading, TEXT("로고용 텍스쳐를 로딩 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("로고용 모델를 로딩 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("로고용 객체원형 들을 생성 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("로딩이 완료되었습니다. \n"));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLevel_Loader::Loading_ForGamePlayLevel()
{
	wsprintf(m_szLoading, TEXT("게임플레이용 텍스쳐를 로딩 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("게임플레이용 모델를 로딩 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("게임플레이용 객체들을 생성 중입니다. \n"));
	wsprintf(m_szLoading, TEXT("게임플레이용 완료되었습니다. \n"));
	
	m_isFinished = true;

	return S_OK;
}

CLevel_Loader * CLevel_Loader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLv)
{
	CLevel_Loader*		pInstance = new CLevel_Loader(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct(eLv)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Loader::Free()
{
	Safe_Release(m_pGraphic_Device);
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CriticalSection);
	CloseHandle(m_hThread);
}
