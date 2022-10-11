#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class TimeBombTickPreview : public HackablePreview
{
public:
	static TimeBombTickPreview* create();

	HackablePreview* clone() override;

protected:
	TimeBombTickPreview();
	virtual ~TimeBombTickPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	int currentTick = 0;
	float elapsed = 0.0f;

	cocos2d::Sprite* timeBomb = nullptr;
	ConstantString* tickStr = nullptr;
	LocalizedLabel* tick = nullptr;
	SmartAnimationSequenceNode* explosionAnim = nullptr;

	static const int MaxTick;
};
