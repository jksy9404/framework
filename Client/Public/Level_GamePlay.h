#pragma once

#include "Clinet_Define.h"
#include "Level.h"

BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
private:
	CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_float fTmDelta) override;
	virtual void LateTick(_float fTmDelta) override;
	virtual HRESULT Render() override;

public:
	static CLevel_GamePlay* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END