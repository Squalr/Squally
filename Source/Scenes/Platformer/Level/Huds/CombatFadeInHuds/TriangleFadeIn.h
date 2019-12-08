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

protected:
	TriangleFadeIn();
	virtual ~TriangleFadeIn();

	void initializePositions() override;

private:
	typedef CombatFadeInHud super;

	void buildShapes();

	cocos2d::DrawNode* upperTraingle;
	cocos2d::DrawNode* leftTriangle;
	cocos2d::DrawNode* rightTriangle;
	cocos2d::DrawNode* bottomTriangle;
};
