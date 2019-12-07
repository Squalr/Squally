#include "RadialScrollMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/EntryContainer.h"

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
	this->buttons = std::vector<EntryContainer*>();
	this->currentIndex = 0;
	
	this->addChild(this->buttonsNode);
}

RadialScrollMenu::~RadialScrollMenu()
{
}
	
void RadialScrollMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs*)
	{
		this->scrollUp();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs*)
	{
		this->scrollDown();
	});
}

void RadialScrollMenu::clearItems()
{
	this->buttons.clear();
	this->buttonsNode->removeAllChildren();
	this->currentIndex = 0;
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

	EntryContainer* entry = EntryContainer::create(attackLabel, attackLabelSelected, Sprite::create(backgroundResource), Sprite::create(backgroundResource));

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

	Node* container = Node::create();

	container->addChild(entry);
	this->buttons.push_back(entry);
	this->buttonsNode->addChild(container);

	if (this->currentIndex == 0 && this->buttons.size() == 1)
	{
		this->scrollDown();
	}
	else
	{
		this->positionButtons();
	}

	return entry;
}

void RadialScrollMenu::disableAll(bool disableInteraction)
{
	for (auto button : this->buttons)
	{
		if (disableInteraction)
		{
			button->disableInteraction(127);
		}
		else
		{

		}

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

void RadialScrollMenu::scrollUp()
{
	this->currentIndex = MathUtils::clamp(this->currentIndex - 1, 0, this->buttons.size() - 1);
	this->positionButtons();
}

void RadialScrollMenu::scrollDown()
{
	this->currentIndex = MathUtils::clamp(this->currentIndex + 1, 0, this->buttons.size() - 1);
	this->positionButtons();
}

void RadialScrollMenu::positionButtons()
{
	const float AngleDelta = float(M_PI) / 6.0f;
	int buttonIndex = 0;

	for (int buttonIndex = 0; buttonIndex < int(this->buttons.size()); buttonIndex++)
	{
		EntryContainer* button = this->buttons[buttonIndex];

		int effectiveIndex = buttonIndex - this->currentIndex;
		float currentAngle = float(effectiveIndex) * AngleDelta;

		button->setTextOffset(Vec2(48.0f, 0.0f));
		button->setPosition(Vec2(this->radius * std::cos(currentAngle), this->radius * -std::sin(currentAngle)));
		
		if (effectiveIndex == -2 || effectiveIndex == 2)
		{
			button->disable(64);
		}
		else if (effectiveIndex < -2 || effectiveIndex > 2)
		{
			button->disable(0);
		}
		else
		{
			button->enable();
		}
	}
}
