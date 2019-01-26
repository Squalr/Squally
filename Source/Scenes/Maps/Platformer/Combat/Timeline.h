#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingRectangleNode;
	class Sprite;
}

class CProgressBar;
class PlatformerEntity;

class Timeline : public SmartNode
{
public:
	static Timeline* create();

private:
	typedef SmartNode super;
	Timeline();
	virtual ~Timeline() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	CProgressBar* swordFill;
	cocos2d::Sprite* swordTop;

	static const float CastPercentage;
};
