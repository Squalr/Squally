#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class PlatformerEntity;
class ProgressBar;

class StatsBars : public SmartNode
{
public:
	static StatsBars* create(bool isFrameOnLeft = true);

	void setStatsTarget(PlatformerEntity* target);

private:
	typedef SmartNode super;
	StatsBars(bool isFrameOnLeft = true);
	virtual ~StatsBars();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	PlatformerEntity* target;

	bool isFrameOnLeft;
	cocos2d::Sprite* statBackground;
	cocos2d::Sprite* frame;
	cocos2d::Sprite* emblem;
	cocos2d::Sprite* frameTop;
	ProgressBar* healthBar;
	ProgressBar* manaBar;
	LocalizedLabel* healthLabel;
	ConstantString* healthNumerator;
	ConstantString* healthDenominator;
	LocalizedLabel* manaLabel;
	ConstantString* manaNumerator;
	ConstantString* manaDenominator;
};
