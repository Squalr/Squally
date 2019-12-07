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
	this->focused = true;
	this->backCallback = nullptr;

	this->addChild(this->buttonsNode);
}

RadialScrollMenu::~RadialScrollMenu()
{
}
	
void RadialScrollMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused)
		{
			args->handle();
			this->scrollUp();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused)
		{
			args->handle();
			this->scrollDown();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE, EventKeyboard::KeyCode::KEY_BACKSPACE, EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused && this->backCallback != nullptr)
		{
			args->handle();
			this->goBack();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE, EventKeyboard::KeyCode::KEY_ENTER, EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused)
		{
			if (this->currentIndex >= 0 && this->currentIndex < int(this->buttons.size()))
			{
				args->handle();
				this->buttons[this->currentIndex]->interact();
			}
		}
	});
}

void RadialScrollMenu::setBackCallback(std::function<void()> backCallback)
{
	this->backCallback = backCallback;
}

void RadialScrollMenu::goBack()
{
	if (this->focused)
	{
		if (this->backCallback != nullptr)
		{
			this->backCallback();
		}
	}
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

	if (this->currentIndex == 0 && this->buttons.size() == 2)
	{
		this->currentIndex = 1;
	}

	this->positionButtons();

	return entry;
}

void RadialScrollMenu::disableAll(bool retainOpacity, bool disableInteraction)
{
	for (auto button : this->buttons)
	{
		if (disableInteraction)
		{
			button->disable(retainOpacity ? button->getOpacity() : 127);
		}

		button->setTextVisible(false);
	}
}

void RadialScrollMenu::enableAll()
{
	this->positionButtons();
}

void RadialScrollMenu::focus()
{
	this->focused = true;
}

void RadialScrollMenu::unfocus()
{
	this->focused = false;
}

void RadialScrollMenu::scrollUp()
{
	if (!this->focused)
	{
		return;
	}

	this->currentIndex = MathUtils::clamp(this->currentIndex - 1, 0, this->buttons.size() - 1);
	this->positionButtons();
}

void RadialScrollMenu::scrollDown()
{
	if (!this->focused)
	{
		return;
	}
	
	this->currentIndex = MathUtils::clamp(this->currentIndex + 1, 0, this->buttons.size() - 1);
	this->positionButtons();
}

void RadialScrollMenu::scrollTo(int index)
{
	this->currentIndex = MathUtils::clamp(index, 0, this->buttons.size() - 1);
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
		int distance = std::abs(effectiveIndex);
		float currentAngle = float(effectiveIndex) * AngleDelta;

		button->setTextOffset(Vec2(48.0f, 0.0f));
		button->setPosition(Vec2(this->radius * std::cos(currentAngle), this->radius * -std::sin(currentAngle)));

		switch(distance)
		{
			case 0:
			{
				button->setTextVisible(true);
				button->setScale(1.0f);
				button->enable();
				break;
			}
			case 1:
			{
				button->setTextVisible(true);
				button->setScale(0.85f);
				button->enable();
				break;
			}
			case 2:
			{
				button->setTextVisible(false);
				button->setScale(0.75f);
				button->disable(64);
				break;
			}
			default:
			{
				button->setTextVisible(false);
				button->setScale(1.0f);
				button->disable(0);
				break;
			}
		}
	}
}
