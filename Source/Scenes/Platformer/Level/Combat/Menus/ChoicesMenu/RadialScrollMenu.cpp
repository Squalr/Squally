#include "RadialScrollMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RadialScrollMenu* RadialScrollMenu::create(float radius)
{
	RadialScrollMenu* instance = new RadialScrollMenu(radius);

	instance->autorelease();

	return instance;
}

RadialScrollMenu::RadialScrollMenu(float radius)
{
	this->radius = radius;
	this->buttonsNode = Node::create();
	this->buttons = std::vector<ClickableTextNode*>();
	
	this->addChild(this->buttonsNode);
}

RadialScrollMenu::~RadialScrollMenu()
{
}

void RadialScrollMenu::clearItems()
{
	this->buttons.clear();
	this->buttonsNode->removeAllChildren();
}

ClickableTextNode* RadialScrollMenu::addEntry(LocalizedString* labelStr, cocos2d::Node* iconNode, std::string backgroundResource, std::function<void()> callback)
{
	LocalizedLabel* attackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, labelStr);
	LocalizedLabel* attackLabelSelected = attackLabel->clone();

	attackLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	attackLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	attackLabel->enableOutline(Color4B::BLACK, 2);
	attackLabelSelected->enableOutline(Color4B::BLACK, 2);
	attackLabelSelected->setTextColor(Color4B::YELLOW);

	ClickableTextNode* entry = ClickableTextNode::create(attackLabel, attackLabelSelected, backgroundResource, backgroundResource);

	entry->setTextOffset(Vec2(48.0f, 0.0f));

	if (iconNode != nullptr)
	{
		entry->addChild(iconNode);
	}

	if (callback != nullptr)
	{
		entry->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			callback();
		});
	}

	this->buttons.push_back(entry);
	this->buttonsNode->addChild(entry);

	this->positionButtons();

	return entry;
}

void RadialScrollMenu::disableAll()
{
	for (auto button : this->buttons)
	{
		button->disableInteraction(127);
		button->setTextVisible(false);
	}
}

void RadialScrollMenu::enableAll()
{
	for (auto button : this->buttons)
	{
		button->enableInteraction();
		button->setTextVisible(true);
	}
}

void RadialScrollMenu::positionButtons()
{
	const float AngleDelta = float(M_PI) / 6.0f;
	float currentAngle = 0.0f;
	
	for (auto button : this->buttons)
	{
		button->setTextOffset(Vec2(48.0f, 0.0f));
		button->setPosition(Vec2(this->radius * std::cos(currentAngle), this->radius * std::sin(currentAngle)));

		currentAngle = (currentAngle <= 0.0f ? 1.0f : -1.0f) * (std::abs(currentAngle) + (currentAngle <= 0.0f ? AngleDelta : 0.0f));
	}
}
