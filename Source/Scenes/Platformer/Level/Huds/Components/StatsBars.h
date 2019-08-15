#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class EqDisplay;
class LocalizedLabel;
class RuneBar;
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
	~StatsBars();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	PlatformerEntity* target;

	int cachedMana;
	int cachedMaxMana;
	int cachedHealth;
	int cachedMaxHealth;

	bool isFrameOnLeft;
	cocos2d::Sprite* frame;
	cocos2d::Sprite* emblemGlow;
	cocos2d::Node* emblemNode;
	cocos2d::Sprite* emblem;
	ProgressBar* healthBar;
	ProgressBar* manaBar;
	cocos2d::Sprite* healthSprite;
	cocos2d::Sprite* manaSprite;
	LocalizedLabel* healthLabel;
	ConstantString* healthNumerator;
	ConstantString* healthDenominator;
	LocalizedLabel* manaLabel;
	ConstantString* manaNumerator;
	ConstantString* manaDenominator;

	EqDisplay* eqDisplay;
	RuneBar* runeBar;
};
