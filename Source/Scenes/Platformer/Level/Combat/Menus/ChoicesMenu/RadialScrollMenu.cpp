#include "RadialScrollMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

RadialScrollMenu* RadialScrollMenu::create(float radius, float angleDelta)
{
	RadialScrollMenu* instance = new RadialScrollMenu(radius, angleDelta);

	instance->autorelease();

	return instance;
}

RadialScrollMenu::RadialScrollMenu(float radius, float angleDelta)
{
	this->radius = radius;
	this->buttonsNode = Node::create();
	this->arrow = Sprite::create(UIResources::Combat_Arrow);
	this->buttons = std::vector<RadialEntry*>();
	this->indexChangeSound = Sound::create(SoundResources::Menus_ButtonRollover1);
	this->errorSound = Sound::create(SoundResources::Menus_Error1);
	this->currentIndex = 0;
	this->focused = true;
	this->isTimelineCinematicPaused = false;
	this->backCallback = nullptr;
	this->angleDelta = angleDelta;

	this->addChild(this->buttonsNode);
	this->addChild(this->arrow);
	this->addChild(this->indexChangeSound);
	this->addChild(this->errorSound);
}

RadialScrollMenu::~RadialScrollMenu()
{
}

void RadialScrollMenu::initializePositions()
{
	super::initializePositions();

	this->arrow->setPosition(Vec2(this->radius - 72.0f, 0.0f));
}

void RadialScrollMenu::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->isTimelineCinematicPaused = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->isTimelineCinematicPaused = false;
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused && !this->isTimelineCinematicPaused)
		{
			args->handle();
			this->scrollUp();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused && !this->isTimelineCinematicPaused)
		{
			args->handle();
			this->scrollDown();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE, EventKeyboard::KeyCode::KEY_BACKSPACE, EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused && !this->isTimelineCinematicPaused && this->backCallback != nullptr)
		{
			args->handle();
			this->goBack();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE, EventKeyboard::KeyCode::KEY_ENTER, EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		if (this->focused && !this->isTimelineCinematicPaused)
		{
			if (this->currentIndex >= 0 && this->currentIndex < int(this->buttons.size()))
			{
				args->handle();

				if (this->buttons[this->currentIndex]->canInteract())
				{
					this->buttons[this->currentIndex]->interact();
				}
				else
				{
					this->errorSound->play();
				}
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

int RadialScrollMenu::getIndex()
{
	return this->currentIndex;
}

void RadialScrollMenu::clearItems()
{
	this->buttons.clear();
	this->buttonsNode->removeAllChildren();
	this->currentIndex = 0;
}

RadialEntry* RadialScrollMenu::addEntry(LocalizedString* labelStr, LocalizedString* lowerLabelStr, std::string iconResource, std::string backgroundResource, std::function<void()> callback)
{
	LocalizedLabel* entryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, labelStr);
	LocalizedLabel* entryLabelSelected = entryLabel->clone();

	entryLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	entryLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
	entryLabel->enableOutline(Color4B::BLACK, 2);
	entryLabelSelected->enableOutline(Color4B::BLACK, 2);
	entryLabelSelected->setTextColor(Color4B::YELLOW);

	if (lowerLabelStr != nullptr)
	{
		LocalizedLabel* lowerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, lowerLabelStr);
		LocalizedLabel* lowerLabelSelected = lowerLabel->clone();

		lowerLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
		lowerLabelSelected->setAnchorPoint(Vec2(0.0f, 0.5f));
		lowerLabel->enableOutline(Color4B::BLACK, 2);
		lowerLabelSelected->enableOutline(Color4B::BLACK, 2);
		lowerLabelSelected->setTextColor(Color4B::YELLOW);

		lowerLabel->setPosition(Vec2(0.0f, -16.0f));
		lowerLabelSelected->setPosition(Vec2(0.0f, -16.0f));

		entryLabel->addChild(lowerLabel);
		entryLabelSelected->addChild(lowerLabelSelected);
	}

	RadialEntry* entry = RadialEntry::create(entryLabel, entryLabelSelected, Sprite::create(backgroundResource), Sprite::create(backgroundResource));

	entry->setTextOffset(Vec2(48.0f, 0.0f));
	entry->addIcon(iconResource);

	if (callback != nullptr)
	{
		entry->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			if (!this->isTimelineCinematicPaused)
			{
				callback();
			}
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

void RadialScrollMenu::toggleAll(bool disableInteraction, bool fadeOpacity, bool hideText)
{
	for (auto button : this->buttons)
	{
		if (disableInteraction)
		{
			button->disableInteraction(fadeOpacity ? 127 : 255);
		}
		else
		{
			button->enableInteraction(fadeOpacity ? 127 : 255);
		}

		button->setTextVisible(!hideText);
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

void RadialScrollMenu::focus()
{
	this->focused = true;
	this->arrow->setVisible(true);
}

void RadialScrollMenu::unfocus()
{
	this->focused = false;
	this->arrow->setVisible(false);
}

void RadialScrollMenu::scrollUp()
{
	if (!this->focused)
	{
		return;
	}
	
	int previousIndex = this->currentIndex;
	this->currentIndex = MathUtils::clamp(this->currentIndex - 1, 0, this->buttons.size() - 1);

	if (previousIndex != this->currentIndex)
	{
		this->indexChangeSound->play();
	}
	else
	{
		this->errorSound->play();
	}

	this->positionButtons();
}

void RadialScrollMenu::scrollDown()
{
	if (!this->focused)
	{
		return;
	}
	
	int previousIndex = this->currentIndex;
	this->currentIndex = MathUtils::clamp(this->currentIndex + 1, 0, this->buttons.size() - 1);

	if (previousIndex != this->currentIndex)
	{
		this->indexChangeSound->play();
	}
	else
	{
		this->errorSound->play();
	}

	this->positionButtons();
}

void RadialScrollMenu::scrollTo(int index)
{
	this->currentIndex = MathUtils::clamp(index, 0, this->buttons.size() - 1);
	this->positionButtons();
}

void RadialScrollMenu::positionButtons()
{
	int buttonIndex = 0;

	for (int buttonIndex = 0; buttonIndex < int(this->buttons.size()); buttonIndex++)
	{
		RadialEntry* button = this->buttons[buttonIndex];

		int effectiveIndex = buttonIndex - this->currentIndex;
		int distance = std::abs(effectiveIndex);
		float currentAngle = float(effectiveIndex) * this->angleDelta;

		button->setTextOffset(Vec2(48.0f, 0.0f));
		button->setPosition(Vec2(this->radius * std::cos(currentAngle), this->radius * -std::sin(currentAngle)));

		switch(distance)
		{
			case 0:
			{
				button->setTextVisible(true);
				button->setScale(1.0f);
				button->setOpacity(255);
				break;
			}
			case 1:
			{
				button->setTextVisible(true);
				button->setScale(0.85f);
				button->setOpacity(255);
				break;
			}
			case 2:
			{
				button->setTextVisible(false);
				button->setScale(0.75f);
				button->setOpacity(64);
				break;
			}
			default:
			{
				button->setTextVisible(false);
				button->setScale(1.0f);
				button->setOpacity(0);
				break;
			}
		}
	}
}
