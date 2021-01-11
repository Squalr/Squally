#pragma once

#include "Scenes/Platformer/Level/Huds/FadeHuds/FadeHudBase.h"

namespace cocos2d
{
	class DrawNode;
}

class NormalFadeHud : public FadeHudBase
{
public:
	static NormalFadeHud* create();

	void runAnim() override;
	void resetAnim() override;

protected:
	NormalFadeHud();
	virtual ~NormalFadeHud();

private:
	typedef FadeHudBase super;

	void buildShapes();

	cocos2d::DrawNode* fadeScreen;
};
