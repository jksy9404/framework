#pragma once

#include "Clinet_Define.h"
#include "Level.h"

BEGIN(Client)
class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT NativeConstruct(LEVEL eLevel);
	virtual void Tick(_float fTmDelta) override;
	virtual void LateTick(_float fTmDelta) override;
	virtual HRESULT Render() override;

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device,LEVEL eLv);
	virtual void Free() override;

private:
	LEVEL	m_eNextLevel = LEVEL_END;
	class CLevel_Loader* m_pLoader = nullptr;
	
};

END