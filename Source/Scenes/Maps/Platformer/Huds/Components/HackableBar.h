#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class HackableBar : public SmartNode
{
public:
	static HackableBar* create(bool isFrameOnLeft = true);

	void setStatsTarget(PlatformerEntity* target);

private:
	typedef SmartNode super;
	HackableBar(bool isFrameOnLeft = true);
	virtual ~HackableBar() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	PlatformerEntity* target;

	std::vector<cocos2d::Sprite*> emptyRunes;
	std::vector<cocos2d::Sprite*> filledRunes;

	static const int RuneCount;
};
