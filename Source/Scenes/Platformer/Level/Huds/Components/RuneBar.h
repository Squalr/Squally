#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class RuneBar : public SmartNode
{
public:
	static RuneBar* create(bool isFrameOnLeft = true);

	void setStatsTarget(PlatformerEntity* target);

private:
	typedef SmartNode super;
	RuneBar(bool isFrameOnLeft = true);
	virtual ~RuneBar();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	PlatformerEntity* target;

	std::vector<cocos2d::Sprite*> emptyRunes;
	std::vector<cocos2d::Sprite*> filledRunes;
};
