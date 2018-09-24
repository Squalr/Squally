#include "HexusChapterSelectMenu.h"

HexusChapterSelectMenu * HexusChapterSelectMenu::create()
{
	HexusChapterSelectMenu* instance = new HexusChapterSelectMenu();

	instance->autorelease();

	return instance;
}

HexusChapterSelectMenu::HexusChapterSelectMenu()
{
	this->chapters = new std::vector<HexusChapterPreview*>();
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

	auto callback = CC_CALLBACK_1(HexusChapterSelectMenu::onMouseOver, this);
	this->chapters->push_back(this->hexusChapterPreviewTraining);
	this->chapters->push_back(this->hexusChapterPreviewJungle);
	this->chapters->push_back(this->hexusChapterPreviewRuins);
	this->chapters->push_back(this->hexusChapterPreviewForest);
	this->chapters->push_back(this->hexusChapterPreviewCaverns);
	this->chapters->push_back(this->hexusChapterPreviewCastle);
	this->chapters->push_back(this->hexusChapterPreviewIceCaps);
	this->chapters->push_back(this->hexusChapterPreviewVolcano);
	this->chapters->push_back(this->hexusChapterPreviewObelisk);
	this->chapters->push_back(this->hexusChapterPreviewMech);

	this->addChild(this->background);

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
	{
		this->addChild(*it);
	}

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

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}
}

void HexusChapterSelectMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	int index = 0;

	for (std::vector<HexusChapterPreview*>::iterator it = this->chapters->begin(); it != this->chapters->end(); ++it)
	{
		int x = index % 5;
		int y = index / 5;

		if (x == 0)
		{
			(*it)->setPositionX(visibleSize.width / 2.0f - 720.0f);
		}
		else if (x == 1)
		{
			(*it)->setPositionX(visibleSize.width / 2.0f - 360.0f);
		}
		else if (x == 2)
		{
			(*it)->setPositionX(visibleSize.width / 2.0f + 0.0f);
		}
		else if (x == 3)
		{
			(*it)->setPositionX(visibleSize.width / 2.0f + 360.0f);
		}
		else if (x == 4)
		{
			(*it)->setPositionX(visibleSize.width / 2.0f + 720.0f);
		}

		if (y == 0)
		{
			(*it)->setPositionY(visibleSize.height / 2.0f + 256.0f);
		}
		else
		{
			(*it)->setPositionY(visibleSize.height / 2.0f - 256.0f);
		}

		index++;
	}
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

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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

void HexusChapterSelectMenu::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
