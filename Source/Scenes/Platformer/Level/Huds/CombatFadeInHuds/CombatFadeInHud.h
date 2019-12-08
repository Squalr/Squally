#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;
}

class CombatFadeInHud : public Hud
{
public:
	virtual void runAnim() = 0;

protected:
	CombatFadeInHud();
	virtual ~CombatFadeInHud();

private:
	typedef Hud super;
};
