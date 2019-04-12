#include "CipherSelectMenu.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/CipherMenu/CipherLevelItem.h"

#include "Resources/MapResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hexus/HexusPuzzles.h"
#include "Strings/Generics/Empty.h"

using namespace cocos2d;

CipherSelectMenu* CipherSelectMenu::instance = nullptr;
const Color3B CipherSelectMenu::TitleColor = Color3B(88, 188, 193);

void CipherSelectMenu::registerGlobalScene()
{
	if (CipherSelectMenu::instance == nullptr)
	{
		CipherSelectMenu::instance = new CipherSelectMenu();

		CipherSelectMenu::instance->autorelease();
		CipherSelectMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CipherSelectMenu::instance);
}

CipherSelectMenu::CipherSelectMenu()
{
	this->hexusOpponentItems = std::vector<CipherLevelItem*>();

	this->window = Sprite::create(UIResources::Menus_OptionsMenu_OptionsMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hexus_HexusPuzzles::create());
	this->descriptionBox = Sprite::create(UIResources::Menus_TutorialMenu_TutorialItem);
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Generics_Empty::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->tutorialsTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconLightbulb, Strings::Hexus_HexusPuzzles::create());
	this->easyTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconCogs, Strings::Hexus_HexusPuzzles::create());
	this->mediumTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconChatBubble, Strings::Hexus_HexusPuzzles::create());
	this->hardTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconWeapons, Strings::Hexus_HexusPuzzles::create());

	this->nether = ParticleSystemQuad::create(ParticleResources::BlueNether);
	this->swirl = ParticleSystemQuad::create(ParticleResources::BlueStarCircle);

	this->titleLabel->setColor(CipherSelectMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->addChild(this->nether);
	this->addChild(this->swirl);

	this->addChild(this->window);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->descriptionBox);
	this->addChild(this->description);

	this->loadLevels();

	this->closeButton->setMouseClickCallback(CC_CALLBACK_0(CipherSelectMenu::onCloseClick, this));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	for (std::vector<CipherLevelItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		this->addChild(*it);
	}
}

CipherSelectMenu::~CipherSelectMenu()
{
}

void CipherSelectMenu::onEnter()
{
	GlobalScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->window, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->descriptionBox, delay, duration);
	GameUtils::fadeInObject(this->description, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);

	for (std::vector<CipherLevelItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}

	// Initialize particles to an intermediate state
	GameUtils::accelerateParticles(this->swirl, 5.0f);
	GameUtils::accelerateParticles(this->nether, 1.0f);
}

void CipherSelectMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->nether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->swirl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->window->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 248.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 308.0f, visibleSize.height / 2 + 222.0f));
	this->descriptionBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));
	this->description->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));

	for (std::vector<CipherLevelItem*>::iterator it = this->hexusOpponentItems.begin(); it != this->hexusOpponentItems.end(); ++it)
	{
		(*it)->initializePositions();
	}
}

void CipherSelectMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	CipherSelectMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCipherPuzzleSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(CipherSelectMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(CipherSelectMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void CipherSelectMenu::loadLevels()
{
	auto callback = CC_CALLBACK_1(CipherSelectMenu::onMouseOver, this);
	int index = 0;

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Exact Value Scan I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Exact Value Scan II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Unknown Value Scan",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Data Types - Float",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Data Types - Double",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Godmode",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Position I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Position II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Blink Godmode I",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));

	this->hexusOpponentItems.push_back(CipherLevelItem::create(
		"Blink Godmode II",
		MapResources::EndianForest_Forest,
		index++,
		callback
	));
}

void CipherSelectMenu::onMouseOver(CipherLevelItem* tutorialItem)
{
	if (this->description->getString() != tutorialItem->tutorialDescription)
	{
		// this->description->setLocalizedString(tutorialItem->tutorialDescription);
	}
}

void CipherSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void CipherSelectMenu::onCloseClick()
{
	NavigationEvents::navigateBack();
}

ClickableTextNode* CipherSelectMenu::buildTabButton(std::string iconResource, LocalizedString* localizedString)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, localizedString);
	LocalizedLabel*	labelHover = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	button->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* icon = Sprite::create(iconResource);
	icon->setPosition(Vec2(-122.0f, 0.0f));

	button->addChild(icon);

	return button;
}
