#pragma once
#include "Base.h"
#include "Clinet_Define.h"


BEGIN(Client)
class CMainapp final : public CBase
{
private:
	CMainapp();
	virtual ~CMainapp() = default;

public:
	HRESULT NativeConstruct();
	void Tick(float fDeltaTm);
	HRESULT Render();

public:
	static CMainapp* Create();
	virtual void Free() override;
};

END