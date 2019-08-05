#include "HexusChapterSelectMenu.h"

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
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaks.h"
#include "Scenes/Hexus/Menus/ChapterSelect/CastleValgrind/HexusChapterPreviewCastleValgrind.h"
#include "Scenes/Hexus/Menus/ChapterSelect/DaemonsHallow/HexusChapterPreviewDaemonsHallow.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForest.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCrypts.h"
#include "Scenes/Hexus/Menus/ChapterSelect/SeaSharpCaverns/HexusChapterPreviewSeaSharpCaverns.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Training/HexusChapterPreviewTraining.h"
#include "Scenes/Hexus/Menus/ChapterSelect/UnderflowRuins/HexusChapterPreviewUnderflowRuins.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStar.h"
#include "Scenes/Hexus/Menus/HexusDeckManagement.h"
#include "Scenes/Hexus/Menus/OpponentSelect/BalmerPeaks/HexusOpponentMenuBalmerPeaks.h"
#include "Scenes/Hexus/Menus/OpponentSelect/CastleValgrind/HexusOpponentMenuCastleValgrind.h"
#include "Scenes/Hexus/Menus/OpponentSelect/DaemonsHallow/HexusOpponentMenuDaemonsHallow.h"
#include "Scenes/Hexus/Menus/OpponentSelect/EndianForest/HexusOpponentMenuEndianForest.h"
#include "Scenes/Hexus/Menus/OpponentSelect/LambdaCrypts/HexusOpponentMenuLambdaCrypts.h"
#include "Scenes/Hexus/Menus/OpponentSelect/SeaSharpCaverns/HexusOpponentMenuSeaSharpCaverns.h"
#include "Scenes/Hexus/Menus/OpponentSelect/Training/HexusOpponentMenuTraining.h"
#include "Scenes/Hexus/Menus/OpponentSelect/UnderflowRuins/HexusOpponentMenuUnderflowRuins.h"
#include "Scenes/Hexus/Menus/OpponentSelect/VoidStar/HexusOpponentMenuVoidStar.h"
#include "Scenes/Hexus/Menus/Store/HexusStoreMenu.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Hexus/ManageCards.h"
#include "Strings/Hexus/SelectAChapter.h"
#include "Strings/Hexus/Shop.h"

using namespace cocos2d;

HexusChapterSelectMenu* HexusChapterSelectMenu::instance = nullptr;

HexusChapterSelectMenu* HexusChapterSelectMenu::getInstance()
{
	if (HexusChapterSelectMenu::instance == nullptr)
	{
		HexusChapterSelectMenu::instance = new HexusChapterSelectMenu();

		HexusChapterSelectMenu::instance->autorelease();
		HexusChapterSelectMenu::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(HexusChapterSelectMenu::instance);
	}

	return HexusChapterSelectMenu::instance;
}

HexusChapterSelectMenu::HexusChapterSelectMenu()
{
	this->chapters = std::vector<HexusChapterPreview*>();
	this->background = Sprite::create(HexusResources::Menus_WoodBackground);

	this->hexusChapterPreviewTraining = HexusChapterPreviewTraining::create();
	this->hexusChapterPreviewBalmerPeaks = HexusChapterPreviewBalmerPeaks::create();
	this->hexusChapterPreviewCastleValgrind = HexusChapterPreviewCastleValgrind::create();
	this->hexusChapterPreviewDaemonsHallow = HexusChapterPreviewDaemonsHallow::create();
	this->hexusChapterPreviewEndianForest = HexusChapterPreviewEndianForest::create();
	this->hexusChapterPreviewLambdaCrypts = HexusChapterPreviewLambdaCrypts::create();
	this->hexusChapterPreviewSeaSharpCaverns = HexusChapterPreviewSeaSharpCaverns::create();
	this->hexusChapterPreviewUnderflowRuins = HexusChapterPreviewUnderflowRuins::create();
	this->hexusChapterPreviewVoidStar = HexusChapterPreviewVoidStar::create();
	this->hexusChapterPreviewTraining = HexusChapterPreviewTraining::create();

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
	this->chapters.push_back(this->hexusChapterPreviewEndianForest);
	this->chapters.push_back(this->hexusChapterPreviewUnderflowRuins);
	this->chapters.push_back(this->hexusChapterPreviewSeaSharpCaverns);
	this->chapters.push_back(this->hexusChapterPreviewCastleValgrind);
	this->chapters.push_back(this->hexusChapterPreviewBalmerPeaks);
	this->chapters.push_back(this->hexusChapterPreviewDaemonsHallow);
	this->chapters.push_back(this->hexusChapterPreviewLambdaCrypts);
	this->chapters.push_back(this->hexusChapterPreviewVoidStar);

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
		/// (*it)->disableInteraction();
	}

	this->loadProgress();
}

void HexusChapterSelectMenu::initializeListeners()
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

	this->hexusChapterPreviewTraining->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuTraining::getInstance())); } );
	this->hexusChapterPreviewBalmerPeaks->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuBalmerPeaks::getInstance())); } );
	this->hexusChapterPreviewCastleValgrind->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuCastleValgrind::getInstance())); } );
	this->hexusChapterPreviewDaemonsHallow->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuDaemonsHallow::getInstance())); } );
	this->hexusChapterPreviewEndianForest->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuEndianForest::getInstance())); } );
	this->hexusChapterPreviewLambdaCrypts->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuLambdaCrypts::getInstance())); } );
	this->hexusChapterPreviewSeaSharpCaverns->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuSeaSharpCaverns::getInstance())); } );
	this->hexusChapterPreviewUnderflowRuins->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuUnderflowRuins::getInstance())); } );
	this->hexusChapterPreviewVoidStar->setMouseClickCallback([]() { NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(HexusOpponentMenuVoidStar::getInstance())); } );
	
	this->deckManagementButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenu::onDeckManagementClick, this));
	this->shopButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenu::onShopClick, this));
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(HexusChapterSelectMenu::onBackClick, this));
}

void HexusChapterSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	int index = 0;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); ++it)
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

void HexusChapterSelectMenu::onBackClick()
{
	NavigationEvents::NavigateBack();
}

void HexusChapterSelectMenu::onDeckManagementClick()
{
	NavigationEvents::LoadScene(HexusDeckManagement::getInstance());
}

void HexusChapterSelectMenu::onShopClick()
{
	NavigationEvents::LoadScene(HexusStoreMenu::getInstance());
}
