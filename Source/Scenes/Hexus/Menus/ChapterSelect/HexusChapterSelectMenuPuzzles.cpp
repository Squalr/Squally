#include "HexusChapterSelectMenuPuzzles.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaksPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/CastleValgrind/HexusChapterPreviewCastleValgrindPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/DaemonsHallow/HexusChapterPreviewDaemonsHallowPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForestPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCryptsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/SeaSharpCaverns/HexusChapterPreviewSeaSharpCavernsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/UnderflowRuins/HexusChapterPreviewUnderflowRuinsPuzzle.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStarPuzzle.h"
#include "Scenes/Hexus/Menus/HexusDeckManagement.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/BalmerPeaks/HexusOpponentMenuBalmerPeaksPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/CastleValgrind/HexusOpponentMenuCastleValgrindPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/DaemonsHallow/HexusOpponentMenuDaemonsHallowPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/EndianForest/HexusOpponentMenuEndianForestPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/LambdaCrypts/HexusOpponentMenuLambdaCryptsPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/SeaSharpCaverns/HexusOpponentMenuSeaSharpCavernsPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/UnderflowRuins/HexusOpponentMenuUnderflowRuinsPuzzle.h"
#include "Scenes/Hexus/Menus/PuzzleSelect/VoidStar/HexusOpponentMenuVoidStarPuzzle.h"
#include "Scenes/Hexus/Menus/Store/HexusStoreMenu.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectAChapter.h"
#include "Strings/Hexus/Shop.h"

using namespace cocos2d;

HexusChapterSelectMenuPuzzles* HexusChapterSelectMenuPuzzles::instance = nullptr;

HexusChapterSelectMenuPuzzles* HexusChapterSelectMenuPuzzles::getInstance()
{
	if (HexusChapterSelectMenuPuzzles::instance == nullptr)
	{
		HexusChapterSelectMenuPuzzles::instance = new HexusChapterSelectMenuPuzzles();

		HexusChapterSelectMenuPuzzles::instance->autorelease();
		HexusChapterSelectMenuPuzzles::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(HexusChapterSelectMenuPuzzles::instance);
	}

	return HexusChapterSelectMenuPuzzles::instance;
}

HexusChapterSelectMenuPuzzles::HexusChapterSelectMenuPuzzles()
{
	this->chapters = std::vector<HexusChapterPreview*>();
	this->backgroundNode = Node::create();

	this->hexusChapterPreviewBalmerPeaksPuzzle = HexusChapterPreviewBalmerPeaksPuzzle::create();
	this->hexusChapterPreviewCastleValgrindPuzzle = HexusChapterPreviewCastleValgrindPuzzle::create();
	this->hexusChapterPreviewDaemonsHallowPuzzle = HexusChapterPreviewDaemonsHallowPuzzle::create();
	this->hexusChapterPreviewEndianForestPuzzle = HexusChapterPreviewEndianForestPuzzle::create();
	this->hexusChapterPreviewLambdaCryptsPuzzle = HexusChapterPreviewLambdaCryptsPuzzle::create();
	this->hexusChapterPreviewSeaSharpCavernsPuzzle = HexusChapterPreviewSeaSharpCavernsPuzzle::create();
	this->hexusChapterPreviewUnderflowRuinsPuzzle = HexusChapterPreviewUnderflowRuinsPuzzle::create();
	this->hexusChapterPreviewVoidStarPuzzle = HexusChapterPreviewVoidStarPuzzle::create();

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

	this->chapterSelectLabel->enableOutline(Color4B::BLACK, 2);
	this->setCascadeOpacityEnabled(true);

	this->chapters.push_back(this->hexusChapterPreviewEndianForestPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewUnderflowRuinsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewSeaSharpCavernsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewCastleValgrindPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewBalmerPeaksPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewDaemonsHallowPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewLambdaCryptsPuzzle);
	this->chapters.push_back(this->hexusChapterPreviewVoidStarPuzzle);

	this->addChild(this->backgroundNode);

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		this->addChild(*it);
	}

	this->addChild(this->chapterSelectLabel);
	this->addChild(this->backButton);
}

HexusChapterSelectMenuPuzzles::~HexusChapterSelectMenuPuzzles()
{
}

void HexusChapterSelectMenuPuzzles::onEnter()
{
	super::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());

	float delay = 0.25f;
	float duration = 0.35f;

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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		NavigationEvents::NavigateBack();
	});

	this->hexusChapterPreviewBalmerPeaksPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuBalmerPeaksPuzzle::getInstance())); } );
	this->hexusChapterPreviewCastleValgrindPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuCastleValgrindPuzzle::getInstance())); } );
	this->hexusChapterPreviewDaemonsHallowPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuDaemonsHallowPuzzle::getInstance())); } );
	this->hexusChapterPreviewEndianForestPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuEndianForestPuzzle::getInstance())); } );
	this->hexusChapterPreviewLambdaCryptsPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuLambdaCryptsPuzzle::getInstance())); } );
	this->hexusChapterPreviewSeaSharpCavernsPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuSeaSharpCavernsPuzzle::getInstance())); } );
	this->hexusChapterPreviewUnderflowRuinsPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuUnderflowRuinsPuzzle::getInstance())); } );
	this->hexusChapterPreviewVoidStarPuzzle->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuVoidStarPuzzle::getInstance())); } );
	
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenuPuzzles::onBackClick, this));
}

void HexusChapterSelectMenuPuzzles::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
	{
		int x = index % 4;
		int y = index / 4;

		(*it)->setPosition(Vec2(visibleSize.width / 2.0f - 540.0f + 384.0f * x, visibleSize.height / 2.0f + 240.0f - 480.0f * y - 48.0f));

		index++;
	}

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

void HexusChapterSelectMenuPuzzles::onBackClick()
{
	NavigationEvents::NavigateBack();
}

void HexusChapterSelectMenuPuzzles::onDeckManagementClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusDeckManagement::getInstance()));
}

void HexusChapterSelectMenuPuzzles::onShopClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusStoreMenu::getInstance()));
}
