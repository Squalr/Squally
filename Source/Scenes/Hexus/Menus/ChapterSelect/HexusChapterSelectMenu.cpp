#include "HexusChapterSelectMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Castle/HexusChapterPreviewCastle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Caverns/HexusChapterPreviewCaverns.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Forest/HexusChapterPreviewForest.h"
#include "Scenes/Hexus/Menus/ChapterSelect/IceCaps/HexusChapterPreviewIceCaps.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Jungle/HexusChapterPreviewJungle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Mech/HexusChapterPreviewMech.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Obelisk/HexusChapterPreviewObelisk.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Ruins/HexusChapterPreviewRuins.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectAChapter.h"
#include "Strings/Hexus/Shop.h"

using namespace cocos2d;

HexusChapterSelectMenu* HexusChapterSelectMenu::instance = nullptr;

void HexusChapterSelectMenu::registerGlobalScene()
{
	if (HexusChapterSelectMenu::instance == nullptr)
	{
		HexusChapterSelectMenu::instance = new HexusChapterSelectMenu();

		HexusChapterSelectMenu::instance->autorelease();
		HexusChapterSelectMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusChapterSelectMenu::instance);
}

HexusChapterSelectMenu::HexusChapterSelectMenu()
{
	this->chapters = std::vector<HexusChapterPreview*>();
	this->background = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->hexusChapterPreviewTraining = HexusChapterPreviewTraining::create();
	this->hexusChapterPreviewJungle = HexusChapterPreviewJungle::create();
	this->hexusChapterPreviewRuins = HexusChapterPreviewRuins::create();
	this->hexusChapterPreviewForest = HexusChapterPreviewForest::create();
	this->hexusChapterPreviewCaverns = HexusChapterPreviewCaverns::create();
	this->hexusChapterPreviewCastle = HexusChapterPreviewCastle::create();
	this->hexusChapterPreviewIceCaps = HexusChapterPreviewIceCaps::create();
	this->hexusChapterPreviewVolcano = HexusChapterPreviewVolcano::create();
	this->hexusChapterPreviewObelisk = HexusChapterPreviewObelisk::create();
	this->hexusChapterPreviewMech = HexusChapterPreviewMech::create();
	this->chapterSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hexus_SelectAChapter::create());

	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	LocalizedLabel* manageDeckLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_ManageCards::create());
	LocalizedLabel* manageDeckLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_ManageCards::create());
	
	manageDeckLabel->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelHover->enableOutline(Color4B::BLACK, 2);

	this->deckManagementButton = ClickableTextNode::create(
		manageDeckLabel,
		manageDeckLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	LocalizedLabel* shopLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Shop::create());
	LocalizedLabel* shopLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Shop::create());

	shopLabel->enableOutline(Color4B::BLACK, 2);
	shopLabelHover->enableOutline(Color4B::BLACK, 2);

	this->shopButton = ClickableTextNode::create(
		shopLabel,
		shopLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->chapterSelectLabel->enableOutline(Color4B::BLACK, 2);
	this->setCascadeOpacityEnabled(true);

	this->chapters.push_back(this->hexusChapterPreviewTraining);
	this->chapters.push_back(this->hexusChapterPreviewJungle);
	this->chapters.push_back(this->hexusChapterPreviewRuins);
	this->chapters.push_back(this->hexusChapterPreviewForest);
	this->chapters.push_back(this->hexusChapterPreviewCaverns);
	this->chapters.push_back(this->hexusChapterPreviewCastle);
	this->chapters.push_back(this->hexusChapterPreviewIceCaps);
	this->chapters.push_back(this->hexusChapterPreviewVolcano);
	this->chapters.push_back(this->hexusChapterPreviewObelisk);
	this->chapters.push_back(this->hexusChapterPreviewMech);

	this->addChild(this->background);

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		this->addChild(*it);
	}

	this->addChild(this->deckManagementButton);
	this->addChild(this->shopButton);
	this->addChild(this->chapterSelectLabel);
	this->addChild(this->backButton);
}

HexusChapterSelectMenu::~HexusChapterSelectMenu()
{
}

void HexusChapterSelectMenu::onEnter()
{
	super::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	//SoundManager::playMusicResource(MusicResources::Something_Blue);

	// Just assume linear dependencies for now
	this->dependencies.clear();
	std::vector<HexusChapterPreview*>::iterator prevIt;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); prevIt = it, it++)
	{
		if (*it == this->chapters.front())
		{
			this->dependencies[*it] = nullptr;
		}
		else
		{
			this->dependencies[*it] = *prevIt;
		}
	}

	for (auto it = this->chapters.begin(); it != this->chapters.end(); it++)
	{
		(*it)->disableInteraction();
	}

	this->loadProgress();
}

void HexusChapterSelectMenu::initializeListeners()
{
	super::initializeListeners();

	HexusChapterSelectMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusChapterSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusChapterSelectMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusChapterSelectMenu::onKeyPressed, this);
	this->hexusChapterPreviewTraining->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Training)); } );
	this->hexusChapterPreviewJungle->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Jungle)); } );
	this->hexusChapterPreviewRuins->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Ruins)); } );
	this->hexusChapterPreviewForest->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Forest)); } );
	this->hexusChapterPreviewCaverns->setClickCallback([]() {NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Caverns)); } );
	this->hexusChapterPreviewCastle->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Castle)); } );
	this->hexusChapterPreviewIceCaps->setClickCallback([]() {NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::IceCaps)); } );
	this->hexusChapterPreviewVolcano->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Volcano)); } );
	this->hexusChapterPreviewObelisk->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Void)); } );
	this->hexusChapterPreviewMech->setClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Mech)); } );
	this->deckManagementButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onDeckManagementClick, this));
	this->shopButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onShopClick, this));
	this->backButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void HexusChapterSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	int index = 0;

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		int x = index % 5;
		int y = index / 5;

		(*it)->setPosition(Vec2(visibleSize.width / 2.0f - 720.0f + 360.0f * x, visibleSize.height / 2.0f + 240.0f - 480.0f * y - 48.0f));

		index++;
	}

	this->deckManagementButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f, visibleSize.height - 64.0f));
	this->shopButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f - 256.0f, visibleSize.height - 64.0f));
	this->chapterSelectLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 64.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void HexusChapterSelectMenu::loadProgress()
{
	for (auto it = this->dependencies.begin(); it != this->dependencies.end(); it++)
	{
		HexusChapterPreview* chapter = (*it).first;
		HexusChapterPreview* dependsOn = (*it).second;

		if (dependsOn == nullptr)
		{
			chapter->enableInteraction();
			continue;
		}

		std::string dependencyKey = dependsOn->chapterSaveKey;

		bool unlocked = SaveManager::hasGlobalData(dependencyKey) ? SaveManager::getGlobalData(dependencyKey).asBool() : false;

		if (unlocked)
		{
			chapter->enableInteraction();
		}
	}

	// Prevent going passed the Forest level // TODO: Just for demo :)
	//this->hexusChapterPreviewForest->disableInteraction();
}

void HexusChapterSelectMenu::onMouseOver(HexusChapterPreview* HexusChapterPreview)
{
}

void HexusChapterSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HexusChapterSelectMenu::onBackClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusChapterSelectMenu::onDeckManagementClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateHexusDeckManagement();
}

void HexusChapterSelectMenu::onShopClick(ClickableNode* menuSprite)
{
	NavigationEvents::navigateHexusShop();
}
