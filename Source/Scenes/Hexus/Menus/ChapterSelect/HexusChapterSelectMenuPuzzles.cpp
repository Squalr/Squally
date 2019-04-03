#include "HexusChapterSelectMenuPuzzles.h"

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
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaksPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/CastleValgrind/HexusChapterPreviewCastleValgrindPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/DaemonsHallow/HexusChapterPreviewDaemonsHallowPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForestPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCryptsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/SeaSharpCaverns/HexusChapterPreviewSeaSharpCavernsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Training/HexusChapterPreviewTrainingPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/UnderflowRuins/HexusChapterPreviewUnderflowRuinsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStarPuzzle.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectAChapter.h"
#include "Strings/Hexus/Shop.h"

using namespace cocos2d;

HexusChapterSelectMenuPuzzles* HexusChapterSelectMenuPuzzles::instance = nullptr;

void HexusChapterSelectMenuPuzzles::registerGlobalScene()
{
	if (HexusChapterSelectMenuPuzzles::instance == nullptr)
	{
		HexusChapterSelectMenuPuzzles::instance = new HexusChapterSelectMenuPuzzles();

		HexusChapterSelectMenuPuzzles::instance->autorelease();
		HexusChapterSelectMenuPuzzles::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusChapterSelectMenuPuzzles::instance);
}

HexusChapterSelectMenuPuzzles::HexusChapterSelectMenuPuzzles()
{
	this->chapters = std::vector<HexusChapterPreview*>();
	this->background = Sprite::create(HexusResources::Menus_WoodBackground);

	this->hexusChapterPreviewTrainingPuzzle = HexusChapterPreviewTrainingPuzzle::create();
	this->hexusChapterPreviewBalmerPeaksPuzzle = HexusChapterPreviewBalmerPeaksPuzzle::create();
	this->hexusChapterPreviewCastleValgrindPuzzle = HexusChapterPreviewCastleValgrindPuzzle::create();
	this->hexusChapterPreviewDaemonsHallowPuzzle = HexusChapterPreviewDaemonsHallowPuzzle::create();
	this->hexusChapterPreviewEndianForestPuzzle = HexusChapterPreviewEndianForestPuzzle::create();
	this->hexusChapterPreviewLambdaCryptsPuzzle = HexusChapterPreviewLambdaCryptsPuzzle::create();
	this->hexusChapterPreviewSeaSharpCavernsPuzzle = HexusChapterPreviewSeaSharpCavernsPuzzle::create();
	this->hexusChapterPreviewUnderflowRuinsPuzzle = HexusChapterPreviewUnderflowRuinsPuzzle::create();
	this->hexusChapterPreviewVoidStarPuzzle = HexusChapterPreviewVoidStarPuzzle::create();
	this->hexusChapterPreviewTrainingPuzzle = HexusChapterPreviewTrainingPuzzle::create();

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

	this->chapters.push_back(this->hexusChapterPreviewTrainingPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewEndianForestPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewUnderflowRuinsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewSeaSharpCavernsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewCastleValgrindPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewBalmerPeaksPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewDaemonsHallowPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewLambdaCryptsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewVoidStarPuzzle);

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

HexusChapterSelectMenuPuzzles::~HexusChapterSelectMenuPuzzles()
{
}

void HexusChapterSelectMenuPuzzles::onEnter()
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

void HexusChapterSelectMenuPuzzles::initializeListeners()
{
	super::initializeListeners();

	HexusChapterSelectMenuPuzzles::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusPuzzlesChapterSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusChapterSelectMenuPuzzles::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusChapterSelectMenuPuzzles::onKeyPressed, this);

	this->hexusChapterPreviewTrainingPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleTraining)); } );
	this->hexusChapterPreviewBalmerPeaksPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleBalmerPeaks)); } );
	this->hexusChapterPreviewCastleValgrindPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleCastleValgrind)); } );
	this->hexusChapterPreviewDaemonsHallowPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleDaemonsHallow)); } );
	this->hexusChapterPreviewEndianForestPuzzle->setMouseClickCallback([]() {NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleEndianForest)); } );
	this->hexusChapterPreviewLambdaCryptsPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleLambdaCrypts)); } );
	this->hexusChapterPreviewSeaSharpCavernsPuzzle->setMouseClickCallback([]() {NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleSeaSharpCaverns)); } );
	this->hexusChapterPreviewUnderflowRuinsPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleUnderflowRuins)); } );
	this->hexusChapterPreviewVoidStarPuzzle->setMouseClickCallback([]() { NavigationEvents::navigateHexusOpponentSelect(NavigationEvents::NavigateHexusOpponentSelectArgs(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleVoidStar)); } );
	
	this->deckManagementButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenuPuzzles::onDeckManagementClick, this));
	this->shopButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenuPuzzles::onShopClick, this));
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenuPuzzles::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void HexusChapterSelectMenuPuzzles::initializePositions()
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

void HexusChapterSelectMenuPuzzles::loadProgress()
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

void HexusChapterSelectMenuPuzzles::onMouseOver(HexusChapterPreview* HexusChapterPreview)
{
}

void HexusChapterSelectMenuPuzzles::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HexusChapterSelectMenuPuzzles::onBackClick()
{
	NavigationEvents::navigateBack();
}

void HexusChapterSelectMenuPuzzles::onDeckManagementClick()
{
	NavigationEvents::navigateHexusDeckManagement();
}

void HexusChapterSelectMenuPuzzles::onShopClick()
{
	NavigationEvents::navigateHexusShop();
}
