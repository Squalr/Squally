#include "HexusPuzzlesMenu.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Hexus/Puzzles/HexusPuzzleItem.h"

#include "Resources/MapResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/HexusPuzzles.h"
#include "Strings/Generics/Empty.h"

using namespace cocos2d;

HexusPuzzlesMenu* HexusPuzzlesMenu::instance = nullptr;
const Color3B HexusPuzzlesMenu::TitleColor = Color3B(88, 188, 193);
const std::string HexusPuzzlesMenu::StringKeyHexusPuzzles = "Menu_Hexus_Puzzles";

void HexusPuzzlesMenu::registerGlobalScene()
{
	if (HexusPuzzlesMenu::instance == nullptr)
	{
		HexusPuzzlesMenu::instance = new HexusPuzzlesMenu();

		HexusPuzzlesMenu::instance->autorelease();
		HexusPuzzlesMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusPuzzlesMenu::instance);
}

HexusPuzzlesMenu::HexusPuzzlesMenu()
{
	this->hexusOpponentItems = std::vector<HexusPuzzleItem*>();

	this->currentPage = 0;

	this->tutorialWindow = Sprite::create(UIResources::Menus_TutorialMenu_TutorialSelect);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hexus_HexusPuzzles::create());
	this->descriptionBox = Sprite::create(UIResources::Menus_TutorialMenu_TutorialItem);
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Generics_Empty::create());
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);

	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);

	this->titleLabel->setColor(HexusPuzzlesMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->tutorialWindow);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->descriptionBox);
	this->addChild(this->description);

	this->loadLevels();

	this->closeButton->setClickCallback(CC_CALLBACK_1(HexusPuzzlesMenu::onCloseClick, this));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		this->addChild(*it);
	}
}

HexusPuzzlesMenu::~HexusPuzzlesMenu()
{
}

void HexusPuzzlesMenu::onEnter()
{
	GlobalScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->tutorialWindow, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->descriptionBox, delay, duration);
	GameUtils::fadeInObject(this->description, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void HexusPuzzlesMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->tutorialWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 248.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 308.0f, visibleSize.height / 2 + 222.0f));
	this->descriptionBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));
	this->description->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));

	for (std::vector<HexusPuzzleItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		(*it)->initializePositions();
	}
}

void HexusPuzzlesMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	HexusPuzzlesMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusPuzzles, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusPuzzlesMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusPuzzlesMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void HexusPuzzlesMenu::loadLevels()
{
	auto callback = CC_CALLBACK_1(HexusPuzzlesMenu::onMouseOver, this);
	int index = 0;

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Exact Value Scan I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Exact Value Scan II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Unknown Value Scan",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Data Types - Float",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Data Types - Double",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Godmode",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Position I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Position II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Blink Godmode I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(HexusPuzzleItem::create(
		"Blink Godmode II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));
}

void HexusPuzzlesMenu::onMouseOver(HexusPuzzleItem* tutorialItem)
{
	if (this->description->getString() != tutorialItem->tutorialDescription)
	{
		// this->description->setLocalizedString(tutorialItem->tutorialDescription);
	}
}

void HexusPuzzlesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void HexusPuzzlesMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
