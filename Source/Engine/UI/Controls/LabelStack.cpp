#include "LabelStack.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/Controls/MenuLabel.h"

#include "Strings/Generics/Newline.h"

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
	this->currentNewlineSpacing = 0.0f;
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

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->setDimensions(this->windowSize.width, 0.0f);

	if (!this->labels.empty())
	{
		LocalizedLabel* previousLabel = this->labels.back();

		label->setPositionY(previousLabel->getContentSize().height - this->spacing - this->currentNewlineSpacing);

		this->currentNewlineSpacing = 0.0f;
	}

	this->labels.push_back(label);
}

void LabelStack::insertNewline()
{
	if (!this->labels.empty())
	{
		this->currentNewlineSpacing += this->labels.back()->getContentSize().height + this->spacing;
	}
}

void LabelStack::clear()
{
	this->labelsNode->removeAllChildren();
	this->labels.clear();
}
