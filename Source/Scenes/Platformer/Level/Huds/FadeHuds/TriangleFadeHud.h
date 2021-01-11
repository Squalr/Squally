#pragma once

#include "Scenes/Platformer/Level/Huds/FadeHuds/FadeHudBase.h"

namespace cocos2d
{
	class DrawNode;
}

class TriangleFadeHud : public FadeHudBase
{
public:
	static TriangleFadeHud* create();

	void runAnim() override;
	void resetAnim() override;

protected:
	TriangleFadeHud();
	virtual ~TriangleFadeHud();

	void initializePositions() override;

private:
	typedef FadeHudBase super;

	void buildShapes();

	cocos2d::DrawNode* upperTraingle;
	cocos2d::DrawNode* leftTriangle;
	cocos2d::DrawNode* rightTriangle;
	cocos2d::DrawNode* bottomTriangle;
};
