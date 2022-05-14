#pragma once
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphicDevice);
	virtual ~CLevel() = default;

public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(float fDeltaTm);
	virtual void LateTick(float fDeltaTm);
	virtual HRESULT Render();


protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

public:
	virtual void Free() override;

};

END