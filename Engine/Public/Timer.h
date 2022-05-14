#pragma once
#include "Base.h"

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	CTimer();
	virtual ~CTimer() = default;

public:
	float Get_TimeDelta() { return m_fTmDelta; }

public:
	HRESULT Initialize();
	void Update();

private:
	LARGE_INTEGER m_CurrentTime;
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_OriginTime;
	LARGE_INTEGER m_CpuTime;

public:
	static CTimer* Create();
	virtual void Free() override;

private:
	float m_fTmDelta;
};

END