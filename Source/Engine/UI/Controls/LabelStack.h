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

protected:
	LabelStack(cocos2d::Size windowSize, float spacing);
	virtual ~LabelStack();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Node* labelsNode;
	std::vector<LocalizedLabel*> labels;
	cocos2d::Size windowSize;
	float spacing;
	float cumulativeHeight;
	cocos2d::Size padding;
};
