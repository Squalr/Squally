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

	static const float AnimationTimeBudget;

protected:
	CombatFadeInHud();
	virtual ~CombatFadeInHud();

	void onEnter() override;
	void fillSeams();

private:
	typedef Hud super;

	void buildBlackout();

	cocos2d::DrawNode* blackout;
};
