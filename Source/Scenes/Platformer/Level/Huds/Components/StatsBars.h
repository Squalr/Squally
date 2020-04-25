#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ConstantString;
class EqDisplay;
class LocalizedLabel;
class RuneBar;
class PlatformerEntity;
class ProgressBar;
class TimelineEntry;

class StatsBars : public SmartNode
{
public:
	static StatsBars* create(bool isFrameOnLeft = true, bool showExp = false);

	void toggleSelectionArrowVisibility(bool isVisible);
	bool canSelect();
	bool isSelected();
	void tryInteract();
	void setSelected(bool isSelected);
	void setStatsTargetAsTimelineEntry(TimelineEntry* targetAsTimelineEntry);
	TimelineEntry* getStatsTargetAsTimelineEntry();
	void setStatsTarget(PlatformerEntity* target);
	PlatformerEntity* getStatsTarget();
	void enableInteraction();
	void disableInteraction(int opacity = 255);
	int getFrameOpaicty();
	void setMouseOverCallback(std::function<void(StatsBars*)> onMouseOverCallback);
	void setClickCallback(std::function<void(StatsBars*)> onClickCallback);

protected:
	StatsBars(bool isFrameOnLeft, bool showExp);
	virtual ~StatsBars();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	PlatformerEntity* target;
	TimelineEntry* targetAsTimelineEntry;

	bool showExp;
	int cachedExp;
	int cachedMaxExp;
	int cachedMana;
	int cachedMaxMana;
	int cachedHealth;
	int cachedMaxHealth;

	bool isFrameOnLeft;
	ClickableNode* frame;
	cocos2d::Sprite* emblemGlow;
	cocos2d::Node* emblemNode;
	cocos2d::Sprite* emblem;
	ProgressBar* healthBar;
	ProgressBar* manaBar;
	ProgressBar* expBar;
	cocos2d::Sprite* healthSprite;
	cocos2d::Sprite* manaSprite;
	cocos2d::Sprite* expSprite;
	LocalizedLabel* healthLabel;
	ConstantString* healthNumerator;
	ConstantString* healthDenominator;
	LocalizedLabel* manaLabel;
	ConstantString* manaNumerator;
	ConstantString* manaDenominator;
	LocalizedLabel* expLabel;
	ConstantString* expNumerator;
	ConstantString* expDenominator;

	EqDisplay* eqDisplay;
	RuneBar* runeBar;
	cocos2d::Sprite* arrowSprite;
};
