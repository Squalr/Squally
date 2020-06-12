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

	int currentTick;
	float elapsed;

	cocos2d::Sprite* timeBomb;
	ConstantString* tickStr;
	LocalizedLabel* tick;
	SmartAnimationSequenceNode* explosionAnim;

	static const int MaxTick;
};
