#include "LabelStack.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/Controls/MenuLabel.h"

#include "Strings/Strings.h"

using namespace cocos2d;
using namespace cocos2d::ui;

LabelStack* LabelStack::create(cocos2d::Size windowSize, float spacing)
{
	LabelStack* instance = new LabelStack(windowSize, spacing);

	instance->autorelease();

	return instance;
}

LabelStack::LabelStack(cocos2d::Size windowSize, float spacing)
{
	this->windowSize = windowSize;
	this->spacing = spacing;
	this->cumulativeHeight = 0.0f;
	this->labelsNode = Node::create();
	this->labels = std::vector<LocalizedLabel*>();

	this->addChild(this->labelsNode);
}

void LabelStack::onEnter()
{
	super::onEnter();
}

void LabelStack::initializePositions()
{
	super::initializePositions();
}

void LabelStack::initializeListeners()
{
	super::initializeListeners();
}

void LabelStack::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
{
	super::setAnchorPoint(anchorPoint);

	this->labelsNode->setAnchorPoint(anchorPoint);
}

void LabelStack::insert(LocalizedLabel* label)
{
	this->labelsNode->addChild(label);

	label->setAnchorPoint(Vec2(0.0f, 1.0f));
	label->setPositionX(this->padding.width);
	label->setOverflow(Label::Overflow::RESIZE_HEIGHT);
	label->setDimensions(this->windowSize.width - this->padding.width * 2, 0.0f);

	if (!this->labels.empty())
	{
		this->cumulativeHeight += this->labels.back()->getContentSize().height + this->spacing;
	}
	else
	{
		this->cumulativeHeight += this->padding.height + this->spacing;
	}

	label->setPositionY(-this->cumulativeHeight);

	this->labels.push_back(label);
}

void LabelStack::insertNewline()
{
	if (!this->labels.empty())
	{
		this->cumulativeHeight += this->labels.back()->getContentSize().height + this->spacing;
	}
	else
	{
		this->cumulativeHeight += this->spacing;
	}
}

void LabelStack::clear()
{
	this->labelsNode->removeAllChildren();
	this->labels.clear();
	this->cumulativeHeight = 0.0f;
}

void LabelStack::setPadding(cocos2d::Size padding)
{
	this->padding = padding;

	// Should probably adjust existing labels, but this shouldn't be an issue in our use cases so im not gonna implement it
}
