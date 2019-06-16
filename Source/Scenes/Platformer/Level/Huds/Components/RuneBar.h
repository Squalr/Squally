#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class DrawNode;
	class Sprite;
}

class PlatformerEntity;
class SmartAnimationSequenceNode;
class Sound;

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
	std::vector<cocos2d::ClippingNode*> cooldownClips;
	std::vector<cocos2d::DrawNode*> cooldownCircles;
	std::vector<cocos2d::DrawNode*> cooldownStencils;
	std::vector<cocos2d::Sprite*> filledRunes;
	std::vector<SmartAnimationSequenceNode*> smokeFx;
	std::vector<Sound*> smokeSound;

	int cachedRunes;

	static const int RuneCipher;
};
