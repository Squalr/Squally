#include "HexusOpponentMenuBase.h"

HexusOpponentMenuBase::HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter, std::string chapterProgressSaveKey)
{
	this->chapter = chapter;
	this->chapterProgressSaveKey = chapterProgressSaveKey;
	this->opponents = std::vector<HexusOpponentPreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 840.0f), Color4B(0, 0, 0, 196));
	this->background = Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->opponentSelectLabel = Label::create("Select Opponent", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	Label* manageDeckLabel = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* manageDeckLabelHover = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* manageDeckLabelClick = Label::create("Manage Cards", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	manageDeckLabel->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelHover->enableOutline(Color4B::BLACK, 2);
	manageDeckLabelClick->enableOutline(Color4B::BLACK, 2);

	this->deckManagementButton = TextMenuSprite::create(
		manageDeckLabel,
		manageDeckLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
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
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	Label* backButtonLabel = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelClick = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->opponentSelectLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->scrollPane);
	this->addChild(this->opponentSelectLabel);
	this->addChild(this->deckManagementButton);
	this->addChild(this->shopButton);
	this->addChild(this->backButton);
	this->addChild(Mouse::create());
}

HexusOpponentMenuBase::~HexusOpponentMenuBase()
{
}

void HexusOpponentMenuBase::onEnter()
{
	GlobalScene::onEnter();

	// TODO: Check if chapter was just beat, if so, save that and navigate backwards
	/*
	

		if (gameState->opponentData == this->opponents.back()->hexusOpponentData)
		{
			if (!SaveManager::hasGlobalData(this->chapterProgressSaveKey) || !SaveManager::getGlobalData(this->chapterProgressSaveKey).asBool())
			{
				// Beat the last opponent -- save that we beat the chapter and navigate back to chapter select
				SaveManager::saveGlobalData(this->chapterProgressSaveKey, cocos2d::Value(true));
				backToChapterSelect = true;
			}
		}
		*/

	const float delay = 0.25f;
	const float duration = 0.35f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	// Just assume linear dependencies for now
	this->dependencies.clear();
	std::vector<HexusOpponentPreview*>::iterator prevIt;

	for (auto it = this->opponents.begin(); it != this->opponents.end(); prevIt = it, it++)
	{
		if (*it == this->opponents.front())
		{
			this->dependencies.emplace((*it), nullptr);
		}
		else
		{
			this->dependencies.emplace((*it), (*prevIt));
		}
	}

	for (auto it = this->opponents.begin(); it != this->opponents.end(); it++)
	{
		(*it)->disableInteraction();
	}

	this->loadProgress();
}

void HexusOpponentMenuBase::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 64.0f));

	Size scrollPaneSize = this->scrollPane->getPaneSize();

	int index = 0;

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		int x = index % 3;
		int y = (this->opponents.size() - 1 - index + (3 - this->opponents.size() % 3)) / 3 - (this->opponents.size() % 3 == 0 ? 1 : 0);

		(*it)->setPosition(Vec2(scrollPaneSize.width / 2.0f - 496.0f + 496.0f * x, y * 480.0f + 240.0f));

		index++;
	}

	this->scrollPane->fitSizeToContent();
	this->deckManagementButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f, visibleSize.height - 64.0f));
	this->shopButton->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f - 256.0f, visibleSize.height - 64.0f));
	this->opponentSelectLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 64.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void HexusOpponentMenuBase::initializeListeners()
{
	GlobalScene::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusOpponentSelect, [=](EventCustom* args)
	{
		NavigationEvents::NavigateHexusOpponentSelectArgs* navArgs = (NavigationEvents::NavigateHexusOpponentSelectArgs*)args->getUserData();

		if (navArgs->chapter == this->chapter)
		{
			GlobalDirector::loadScene(this);
		}
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusOpponentMenuBase::onKeyPressed, this);
	this->deckManagementButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onDeckManagementClick, this));
	this->shopButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onShopClick, this));
	this->backButton->setClickCallback(CC_CALLBACK_1(HexusOpponentMenuBase::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void HexusOpponentMenuBase::onMouseOver(HexusOpponentPreview* opponent)
{
}

void HexusOpponentMenuBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HexusOpponentMenuBase::onBackClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusOpponentMenuBase::onDeckManagementClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateHexusDeckManagement();
}

void HexusOpponentMenuBase::onShopClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateHexusShop();
}

void HexusOpponentMenuBase::loadProgress()
{
	for (auto it = this->dependencies.begin(); it != this->dependencies.end(); it++)
	{
		HexusOpponentPreview* opponent = (*it).first;
		HexusOpponentPreview* dependsOn = (*it).second;

		if (dependsOn == nullptr)
		{
			opponent->enableInteraction();
			continue;
		}

		std::string dependencyKey = HexusOpponentData::winsPrefix + dependsOn->hexusOpponentData->enemyNameKey;

		int wins = SaveManager::hasGlobalData(dependencyKey) ? SaveManager::getGlobalData(dependencyKey).asInt() : 0;

		if (wins > 0)
		{
			opponent->enableInteraction();
		}
	}
}
