#pragma once

#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHud.h"

namespace cocos2d
{
	class DrawNode;
}

class TriangleFadeIn : public CombatFadeInHud
{
public:
	static TriangleFadeIn* create();

	void runAnim() override;

private:
	typedef CombatFadeInHud super;
	TriangleFadeIn();
	virtual ~TriangleFadeIn();
};
