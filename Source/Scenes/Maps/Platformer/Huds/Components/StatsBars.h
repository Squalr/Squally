#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class CProgressBar;
class LocalizedLabel;
class PlatformerEntity;

class StatsBars : public SmartNode
{
public:
	static StatsBars* create(bool isFrameOnLeft = true);

	void setStatsTarget(PlatformerEntity* target);

private:
	typedef SmartNode super;
	StatsBars(bool isFrameOnLeft = true);
	virtual ~StatsBars() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	PlatformerEntity* target;

	bool isFrameOnLeft;
	cocos2d::Sprite* frame;
	cocos2d::Sprite* emblem;
	CProgressBar* healthBar;
	CProgressBar* manaBar;
	LocalizedLabel* healthLabel;
	ConstantString* healthNumerator;
	ConstantString* healthDenominator;
	LocalizedLabel* manaLabel;
	ConstantString* manaNumerator;
	ConstantString* manaDenominator;
};
