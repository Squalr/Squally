#pragma once

#include "Scenes/Platformer/Level/Huds/FadeHuds/FadeHudBase.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class TvFadeHud : public FadeHudBase
{
public:
	static TvFadeHud* create();

	void runAnim() override;
	void resetAnim() override;

protected:
	TvFadeHud();
	virtual ~TvFadeHud();

	void initializePositions() override;

private:
	typedef FadeHudBase super;

	void buildShapes();

	cocos2d::DrawNode* upperRectangle = nullptr;
	cocos2d::DrawNode* bottomRectangle = nullptr;
	cocos2d::Sprite* glowSmall = nullptr;
	cocos2d::Sprite* glowLarge = nullptr;
};
