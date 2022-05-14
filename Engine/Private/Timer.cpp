#include "..\Public\Timer.h"



CTimer::CTimer()
	:m_fTmDelta(0.f)
{
	ZeroMemory(&m_CurrentTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OriginTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTime, sizeof(LARGE_INTEGER));
}

HRESULT CTimer::Initialize()
{
	QueryPerformanceCounter(&m_CurrentTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_OriginTime);

	QueryPerformanceFrequency(&m_CpuTime);
	return S_OK;
}

void CTimer::Update()
{
	QueryPerformanceCounter(&m_CurrentTime);
	if (m_CurrentTime.QuadPart - m_OriginTime.QuadPart > m_CpuTime.QuadPart) {
		QueryPerformanceFrequency(&m_CpuTime);
		m_OriginTime = m_CurrentTime;
	}
	m_fTmDelta = float(m_CurrentTime.QuadPart - m_OldTime.QuadPart / m_CpuTime.QuadPart);
	m_OldTime = m_CurrentTime;
}

CTimer * CTimer::Create()
{
	CTimer* pInstance = new CTimer();
	if (FAILED(pInstance->Initialize())) {
		MSG_BOX("Failed to Create : CTimer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTimer::Free()
{
}
