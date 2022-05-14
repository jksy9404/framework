#pragma once
#include "Base.h"

BEGIN(Engine)
class CLevelMgr final : public CBase
{
	DECLARE_SINGLETON(CLevelMgr);

private:
	CLevelMgr();
	virtual ~CLevelMgr() = default;
	
public:
	HRESULT Change_Level(_uint iCurrentIdx, class CLevel* iNextLevel);
	HRESULT Tick(_float fDeltaTm);
	HRESULT LateTick(_float fDeltaTm);

private:
	class CLevel* m_iCurrentLevel = nullptr;
	_uint m_iCurrentLevelIdx = 0;

public:
	virtual void Free() override;

};

END	