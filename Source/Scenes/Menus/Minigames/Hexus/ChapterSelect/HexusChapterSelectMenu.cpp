#include "HexusChapterSelectMenu.h"

HexusChapterSelectMenu * HexusChapterSelectMenu::create()
{
	HexusChapterSelectMenu* instance = new HexusChapterSelectMenu();

	instance->autorelease();

	return instance;
}

HexusChapterSelectMenu::HexusChapterSelectMenu()
{
	this->chapters = std::vector<HexusChapterPreview*>();
	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);
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
	this->chapterSelectLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	Label* backButtonLabel = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelClick = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		backButtonLabelClick,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick
	);

	Label* manageDeckLabel = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* manageDeckLabelHover = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* manageDeckLabelClick = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	
	manageDeckLabel->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelHover->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelClick->enableOutline(Color4B::BLACK, 2);

	this->deckManagementButton = TextMenuSprite::create(
		manageDeckLabel,
		manageDeckLabelHover,
		manageDeckLabelClick,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick
	);

	Label* shopLabel = Label::create("Shop", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* shopLabelHover = Label::create("Shop", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* shopLabelClick = Label::create("Shop", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	shopLabel->enableOutline(Color4B::BLACK, 2);
	shopLabelHover->enableOutline(Color4B::BLACK, 2);
	shopLabelClick->enableOutline(Color4B::BLACK, 2);

	this->shopButton = TextMenuSprite::create(
		shopLabel,
		shopLabelHover,
		shopLabelClick,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick
	);

	this->chapterSelectLabel->enableOutline(Color4B::BLACK, 2);
	this->setCascadeOpacityEnabled(true);

	auto callback = CC_CALLBACK_1(HexusChapterSelectMenu::onMouseOver, this);
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
	this->addChild(Mouse::create());
}

HexusChapterSelectMenu::~HexusChapterSelectMenu()
{
}

void HexusChapterSelectMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	// Just assume linear dependencies for now
	this->dependencies.clear();
	std::vector<HexusChapterPreview*>::iterator prevIt;

	for (auto it = this->chapters.begin(); it != this->chapters.end(); prevIt = it, it++)
	{
		if (*it == this->chapters.front())
		{
			this->dependencies.emplace((*it), nullptr);
		}
		else
		{
			this->dependencies.emplace((*it), (*prevIt));
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
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusChapterSelectMenu::onKeyPressed, this);
	this->hexusChapterPreviewTraining->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Training); } );
	this->hexusChapterPreviewJungle->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Jungle); } );
	this->hexusChapterPreviewRuins->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Ruins); } );
	this->hexusChapterPreviewForest->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Forest); } );
	this->hexusChapterPreviewCaverns->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Caverns); } );
	this->hexusChapterPreviewCastle->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Castle); } );
	this->hexusChapterPreviewIceCaps->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_IceCaps); } );
	this->hexusChapterPreviewVolcano->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Volcano); } );
	this->hexusChapterPreviewObelisk->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Obelisk); } );
	this->hexusChapterPreviewMech->setClickCallback([]() { NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Mech); } );
	this->deckManagementButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onDeckManagementClick, this));
	this->shopButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onShopClick, this));
	this->backButton->setClickCallback(CC_CALLBACK_1(HexusChapterSelectMenu::onBackClick, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusChapterSelectMenu::initializePositions()
{
	FadeScene::initializePositions();

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
	this->shopButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 64.0f));
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

		std::string dependencyKey = dependsOn->chapterNameKey;

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
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		default:
			break;
	}
}

void HexusChapterSelectMenu::onBackClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusChapterSelectMenu::onDeckManagementClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Deck_Management);
}

void HexusChapterSelectMenu::onShopClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames_Hexus_Shop);
}
