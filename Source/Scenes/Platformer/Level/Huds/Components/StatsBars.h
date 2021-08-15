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
	void setSelectable(bool selectable);
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

	PlatformerEntity* target = nullptr;
	TimelineEntry* targetAsTimelineEntry = nullptr;

	bool selectable = false;
	bool showExp = false;
	int cachedExp = -1;
	int cachedMaxExp = -1;
	int cachedMana = -1;
	int cachedMaxMana = -1;
	int cachedHealth = -1;
	int cachedMaxHealth = -1;

	bool isFrameOnLeft = false;
	ClickableNode* frame = nullptr;
	cocos2d::Sprite* emblemGlow = nullptr;
	cocos2d::Node* emblemNode = nullptr;
	cocos2d::Sprite* emblem = nullptr;
	ProgressBar* healthBar = nullptr;
	ProgressBar* manaBar = nullptr;
	ProgressBar* expBar = nullptr;
	cocos2d::Sprite* healthSprite = nullptr;
	cocos2d::Sprite* manaSprite = nullptr;
	cocos2d::Sprite* expSprite = nullptr;
	LocalizedLabel* healthLabel = nullptr;
	ConstantString* healthNumerator = nullptr;
	ConstantString* healthDenominator = nullptr;
	LocalizedLabel* manaLabel = nullptr;
	ConstantString* manaNumerator = nullptr;
	ConstantString* manaDenominator = nullptr;
	LocalizedLabel* expLabel = nullptr;
	ConstantString* expNumerator = nullptr;
	ConstantString* expDenominator = nullptr;

	EqDisplay* eqDisplay = nullptr;
	RuneBar* runeBar = nullptr;
	cocos2d::Sprite* arrowSprite = nullptr;
};
