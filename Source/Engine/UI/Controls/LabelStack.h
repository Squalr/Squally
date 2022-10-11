#pragma once

#include "Engine/SmartNode.h"

class LocalizedLabel;

class LabelStack : public SmartNode
{
public:
	static LabelStack* create(cocos2d::CSize windowSize, float spacing);

	void insert(LocalizedLabel* label);
	void insertNewline();
	void clear();
	void setAnchorPoint(const cocos2d::Vec2& anchorPoint) override;
	void setPadding(cocos2d::CSize padding);

protected:
	LabelStack(cocos2d::CSize windowSize, float spacing);
	virtual ~LabelStack();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void positionLabels();

	cocos2d::Node* labelsNode = nullptr;
	std::vector<LocalizedLabel*> labels;
	cocos2d::CSize windowSize;
	float spacing = 0.0f;
	float cumulativeHeight = 0.0f;
	cocos2d::CSize padding;
};
