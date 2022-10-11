#include "LabelStack.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Strings.h"

using namespace cocos2d;
using namespace cocos2d::ui;

LabelStack* LabelStack::create(cocos2d::CSize windowSize, float spacing)
{
	LabelStack* instance = new LabelStack(windowSize, spacing);

	instance->autorelease();

	return instance;
}

LabelStack::LabelStack(cocos2d::CSize windowSize, float spacing)
{
	this->windowSize = windowSize;
	this->spacing = spacing;
	this->labelsNode = Node::create();

	this->addChild(this->labelsNode);
}

LabelStack::~LabelStack()
{
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

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		// Defer a frame to give labels a chance to update localization first
		this->defer([=]()
		{
			this->positionLabels();
		});
	}));
}

void LabelStack::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
{
	super::setAnchorPoint(anchorPoint);

	this->labelsNode->setAnchorPoint(anchorPoint);
}

void LabelStack::insert(LocalizedLabel* label)
{
	this->labelsNode->addChild(label);
	this->labels.push_back(label);
	this->positionLabels();
}

void LabelStack::insertNewline()
{
	this->labels.push_back(nullptr);
	this->positionLabels();
}

void LabelStack::clear()
{
	this->labelsNode->removeAllChildren();
	this->labels.clear();
	this->cumulativeHeight = 0.0f;
}

void LabelStack::setPadding(cocos2d::CSize padding)
{
	this->padding = padding;

	this->positionLabels();
}

void LabelStack::positionLabels()
{
	switch(Localization::getLanguage())
	{
		default:
		{
			this->padding.height = 0.0f;
			break;
		}
		case LanguageType::ARABIC:
		{
			this->padding.height = -12.0f;
			break;
		}
	}

	this->cumulativeHeight = 0.0f;
	
	for (int index = 0; index < int(this->labels.size()); index++)
	{
		Label* label = this->labels[index];

		if (label == nullptr)
		{
			this->cumulativeHeight += this->spacing;
			continue;
		}

		label->setAnchorPoint(Vec2(0.0f, 1.0f));
		label->setPositionX(this->padding.width);
		label->setOverflow(Label::Overflow::RESIZE_HEIGHT);
		label->setDimensions(this->windowSize.width - this->padding.width * 2.0f, 0.0f);
		label->setPositionY(-this->cumulativeHeight);

		this->cumulativeHeight += label->getContentSize().height + this->padding.height + this->spacing;
	}
}
