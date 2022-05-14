#pragma once
#include "Clinet_Define.h"
#include "GameObject.h"

BEGIN(Client)
class CBackGround final : public CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;
};

END	