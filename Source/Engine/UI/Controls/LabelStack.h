#pragma once

#include "Engine/SmartNode.h"

class LocalizedLabel;

class LabelStack : public SmartNode
{
public:
	static LabelStack* create(cocos2d::Size windowSize, float spacing);

	void insert(LocalizedLabel* label);
	void insertNewline();
	void clear();
	void setAnchorPoint(const cocos2d::Vec2& anchorPoint) override;
	void setPadding(cocos2d::Size padding);

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
	cocos2d::Size padding;
};
