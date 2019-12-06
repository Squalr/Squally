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

void RadialScrollMenu::addEntry(ClickableTextNode* entry)
{
	this->buttons.push_back(entry);
	this->buttonsNode->addChild(entry);
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
