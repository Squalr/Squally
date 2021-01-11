#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;
}

class FadeHudBase : public Hud
{
public:
	virtual void runAnim() = 0;
	virtual void resetAnim() = 0;

protected:
	FadeHudBase();
	virtual ~FadeHudBase();

	void onEnter() override;
	void fillSeams();

private:
	typedef Hud super;

	void buildBlackout();

	cocos2d::DrawNode* blackout;
};
