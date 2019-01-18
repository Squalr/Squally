#pragma once

#include "Engine/SmartNode.h"

class MenuLabel;

class LocalizedLabel;

class LabelStack : public SmartNode
{
public:
	static LabelStack* create(cocos2d::Size windowSize, float spacing);

	void insert(LocalizedLabel* label);
	void insertNewline();
	void clear();
	void setAnchorPoint(const cocos2d::Vec2& anchorPoint) override;

private:
	typedef SmartNode super;
	LabelStack(cocos2d::Size windowSize, float spacing);
	virtual ~LabelStack() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* labelsNode;
	std::vector<LocalizedLabel*> labels;
	cocos2d::Size windowSize;
	float spacing;
	float cumulativeHeight;
};
