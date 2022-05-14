#include "..\Public\TimerMgr.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimerMgr)
CTimerMgr::CTimerMgr()
{
}

_float CTimerMgr::Get_TimeDelta(const _tchar * pTmTag)
{
	CTimer* pTimer = Find_Timer(pTmTag);
	if (nullptr == pTimer)
		return 0.f;
	return pTimer->Get_TimeDelta();
}

HRESULT CTimerMgr::Add_Timer(const _tchar * pTmTag)
{
	if (nullptr != Find_Timer(pTmTag))
		return E_FAIL;
	m_Timer.emplace(pTmTag, CTimer::Create());
	return S_OK;
}

void CTimerMgr::Update(const _tchar * pTmTag)
{
}

CTimer * CTimerMgr::Find_Timer(const _tchar * pTmTag)
{
	auto iter = find_if(m_Timer.begin(), m_Timer.end(), CTag_Finder(pTmTag));
	if(iter == m_Timer.end())
		return nullptr;

	return iter->second;
}

void CTimerMgr::Free()
{
	for (auto& Pair : m_Timer)
		Safe_Release(Pair.second);

	m_Timer.clear();
}
