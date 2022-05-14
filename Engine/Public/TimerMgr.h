#pragma once
#include "Base.h"

BEGIN(Engine)

class CTimerMgr final : public CBase
{
	DECLARE_SINGLETON(CTimerMgr)
private:
	CTimerMgr();
	virtual ~CTimerMgr() = default;

public:
	_float Get_TimeDelta(const _tchar* pTmTag);

public:
	HRESULT Add_Timer(const _tchar* pTmTag);
	void Update(const _tchar* pTmTag);

private:
	map<const _tchar*, class CTimer*> m_Timer;
	typedef map<const _tchar*, class CTimer*> TIMERS;

private:
	class CTimer* Find_Timer(const _tchar* pTmTag);
public:
	virtual void Free() override;
};

END